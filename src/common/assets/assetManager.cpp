#include "assetManager.h"
#include <utility/serializedData.h>
#include "ecs/nativeTypes/meshRenderer.h"
#include "ecs/nativeTypes/assetComponents.h"
#include "ecs/core/component.h"
#include "systems/transforms.h"

AssetManager::AssetManager()
{

}

void AssetManager::updateAsset(Asset* asset)
{
	std::scoped_lock l(assetLock);
	if(!_assets.count(asset->id))
	{
		_assets.insert({asset->id, std::unique_ptr<Asset>(asset)});
		return;
	}

	*_assets[asset->id] = std::move(*asset);

}

void AssetManager::startAssetLoaderSystem()
{
	EntityManager& em = *Runtime::getModule<EntityManager>();
	Runtime::timeline().addTask("asset loader", [this, &em](){

		//Start loading all unloaded assemblies TODO change it so that the state is stored through components and not a bool, so we're not always iterating over literally everything
		em.forEach({EntityIDComponent::def()->id, AssemblyRoot::def()->id}, [&](byte** components){
			AssemblyRoot* ar = AssemblyRoot::fromVirtual(components[1]);
			if(!ar->loaded)
			{
				ar->loaded = true;
				EntityIDComponent* id = EntityIDComponent::fromVirtual(components[0]);
				loadAssembly(ar->id, id->id);
				std::cout << "loading assembly: " << id-id << std::endl;
			}
		});

		// Finish loading assets that we have gotten back from the asset manager or file manager
		for(auto a : _stagedAssemblies)
		{
			//Run preprocessors now, instead of right when we got the asset data
			std::cout << "Pre-processing: " << a.first->name << std::endl;
			for(auto& f : _assetPreprocessors[AssetType::assembly])
				f(a.first);
			std::cout << "Injecting: " << a.first->name << std::endl;
			a.first->inject(em, a.second);
		}
		_stagedAssemblies.clear();

	}, "asset management");
}

void AssetManager::loadAssembly(AssetID assembly, EntityID rootID)
{
	auto f = [this, rootID](Assembly* a){
		std::cout << "Loaded: " << a->name << " requesting dependencies" << std::endl;
		std::shared_ptr<size_t> unloaded = std::make_unique<size_t>();
		*unloaded = a->meshes.size();
		for(auto& mesh : a->meshes)
		{
			MeshAsset* m = getAsset<MeshAsset>(mesh);
			if(m)
			{
				std::cout << "Loaded: " << m->name << std::endl;
				--(*unloaded);
				continue;
			}

			fetchAsset<MeshAsset>(AssetID(mesh)).then([this, unloaded, a, rootID](MeshAsset* mesh)
            {
	            std::cout << "Loaded: " << mesh->name << std::endl;
                if(--(*unloaded) == 0)
                     _stagedAssemblies.push_back({a, rootID});
            });
		}
		if(*unloaded == 0)
			_stagedAssemblies.push_back({a, rootID});
	};
	Assembly* a = getAsset<Assembly>(assembly);
	if(a)
	{
		f(a);
	}
	fetchAsset<Assembly>(assembly).then([f](Assembly* assembly){
		f(assembly);
	});
}

void AssetManager::addAssetPreprocessor(AssetType::Type type, std::function<void(Asset*)> processor)
{
	_assetPreprocessors[type].push_back(processor);
}

void AssetManager::addAsset(Asset* asset)
{
	if(asset->type != AssetType::assembly)
		for(auto& f : _assetPreprocessors[asset->type.type()])
			f(asset);

	assetLock.lock();
	_assets.insert({asset->id, std::unique_ptr<Asset>(asset)});
	assetLock.unlock();
}

const char* AssetManager::name()
{
	return "assetManager";
}

void AssetManager::start()
{
	EntityManager& em = *Runtime::getModule<EntityManager>();
	addNativeComponent<EntityIDComponent>(em);
	addNativeComponent<Transform>(em);
	addNativeComponent<LocalTransform>(em);
	addNativeComponent<Children>(em);
	addNativeComponent<TRS>(em);
	addNativeComponent<MeshRendererComponent>(em);
	addNativeComponent<AssemblyRoot>(em);
	startAssetLoaderSystem();
}

void AssetManager::setFetchCallback(std::function<AsyncData<Asset*>(const AssetID& id, bool incremental)> callback)
{
	assert(callback);
	_fetchCallback = callback;
}

AsyncData<Asset*> AssetManager::fetchAsset(const AssetID& id, bool incremental)
{
	AsyncData<Asset*> asset;
	_fetchCallback(id, incremental).then([this, asset](Asset * a){
		addAsset(a);
		asset.setData(a);
	});
	return asset;
}





#include <iostream>
#include "assets/assetManager.h"
#include "graphics/graphics.h"
#include "client.h"

int main()
{

	Config::loadConfig();
	std::cout << "BraneSurfer starting up\n";

	Runtime rt;
	Timeline& tl = rt.timeline();
	tl.addBlock("asset management");
	tl.addBlock("networking");
	tl.addBlock("before main");
	tl.addBlock("main");
	tl.addBlock("draw");
	rt.addModule<FileManager>();
	rt.addModule<NetworkManager>();
	rt.addModule<AssetManager>();
	rt.addModule<EntityManager>();
	rt.addModule<graphics::VulkanRuntime>();
	rt.addModule<Client>();

	rt.run();
	return 0;
}
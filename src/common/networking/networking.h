#pragma once
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <asio/ssl.hpp>

#include <iostream>
#include <thread>
#include <utility>
#include <vector>
#include <memory>

#include <utility/serializedData.h>
#include "connection.h"
#include "config/config.h"
#include "networkError.h"
#include <shared_mutex>
#include "request.h"

class NetworkManager : public Module
{
	asio::io_context _context;

	std::shared_ptr<JobHandle> _threadHandle;
	asio::ssl::context _ssl_context;
	asio::ip::tcp::resolver _tcpResolver;

	std::shared_mutex _serverLock;
	std::unordered_map<std::string, std::unique_ptr<net::Connection>> _servers;

	std::shared_mutex _clientLock;
	std::vector<std::unique_ptr<net::Connection>> _clients;
	std::vector<std::function<void()>> _onClientDisconnect;

	std::vector<asio::ip::tcp::acceptor> _acceptors;

	std::atomic_bool _running;

	std::mutex _requestLock;
	std::unordered_map<std::string, std::function<void(net::RequestResponse&)>> _requestListeners;

	uint32_t _streamIDCounter = 1000;

	void connectToAssetServer(std::string ip, uint16_t port);

	template<typename socket_t>
	void async_acceptConnections(size_t acceptor, std::function<void (std::unique_ptr<net::Connection>& connection)> callback)
	{
		socket_t* socket;
		if constexpr(std::is_same<socket_t, net::tcp_socket>().value)
			socket = new net::tcp_socket(_context);
		if constexpr(std::is_same<socket_t, net::ssl_socket>().value)
			socket = new net::ssl_socket(_context, _ssl_context);
		_acceptors[acceptor].async_accept(socket->lowest_layer(), [this, acceptor, socket, callback](std::error_code ec) {
			if (!ec)
			{
				std::unique_ptr<net::Connection> connection = std::make_unique<net::ServerConnection<socket_t>>(std::move(*socket));
				callback(connection);
				_clientLock.lock();
				_clients.push_back(std::move(connection));
				_clientLock.unlock();

			}
			else
			{
				std::cout << "Connection Error: " << ec.message() << std::endl;
			}
			delete socket;
			async_acceptConnections<socket_t>(acceptor, callback);
		});
	}

	void startSystems();
	void ingestData(net::Connection* conneciton);
public:
	NetworkManager();
	~NetworkManager();
	void start() override;
	void stop() override;
	void configureServer();

	net::Connection* getServer(const std::string& address) const;

	template<typename socket_t>
	void openClientAcceptor(const uint32_t port, std::function<void (const std::unique_ptr<net::Connection>& connection)> callback)
	{
		_acceptors.emplace_back(_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));
		auto& acceptor = *(_acceptors.end() - 1);
		async_acceptConnections<socket_t>(_acceptors.size()-1, callback);
	}

	void async_connectToAssetServer(const std::string& address, uint16_t port, const std::function<void(bool)>& callback);
	AsyncData<Asset*> async_requestAsset(const AssetID& id);
	AsyncData<IncrementalAsset*> async_requestAssetIncremental(const AssetID& id);

	void addRequestListener(const std::string& name, std::function<void(net::RequestResponse&)> callback);

	static const char* name();
};
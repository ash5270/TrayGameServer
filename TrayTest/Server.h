#pragma once
#include<TrayCommon.h>
#include<TrayServer.h>
#include<Buffer.h>


enum class PacketID : uint16_t {
	message=0,
};

class Server :public tray::net::TrayServer {
public:
	Server(uint16_t port);
public:
	virtual void OnMessage( tray::net::BufferObject&& buffer);
	virtual void OnClientConnect(std::shared_ptr<tray::net::Session> session);
};

#pragma once
#include<map>
#include<TrayCommon.h>
#include<TrayServer.h>

#include<functional>

#include"MessagePacket.h"
#include"PacketIDSerializer.h"
#include"PacketIData.h"


typedef std::function<void(tray::net::BufferObject&&)> call_back_func;

class Server :public tray::net::TrayServer {
public:
	Server(uint16_t port);
public:
	virtual void OnMessage( tray::net::BufferObject&& buffer);
	virtual void OnClientConnect(std::shared_ptr<tray::net::Session> session);
	
public:
	PacketIDSerializer id_serializer;
	std::map<PacketID, call_back_func> packet_divide;
};

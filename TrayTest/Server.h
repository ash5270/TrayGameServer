#pragma once
#include<TrayCommon.h>
#include<TrayServer.h>
#include<Buffer.h>
#include"PacketIData.h"
#include"MessagePacket.h"
#include"PacketIDSerializer.h"

class Server :public tray::net::TrayServer {
public:
	Server(uint16_t port);
public:
	virtual void OnMessage( tray::net::BufferObject&& buffer);
	virtual void OnClientConnect(std::shared_ptr<tray::net::Session> session);

public:
	PacketIDSerializer id_serializer;

};

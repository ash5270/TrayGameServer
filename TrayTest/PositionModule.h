#pragma once

#include<TrayCommon.h>
#include<TrayServer.h>
#include"MessagePacket.h"
#include"PosPacket.h"
#include"Server.h"

class PositionModule
{
public:
	PositionModule(std::shared_ptr<Server> server);
private:
	std::shared_ptr<Server> current_server;
	PosPacket* pos_packet;
public:
	void GetPacketData(tray::net::BufferObject&& buffer);

};

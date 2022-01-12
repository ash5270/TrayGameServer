#pragma once

#include<TrayCommon.h>
#include<TrayServer.h>
#include"LoginPacket.h"
#include"Server.h"

class LoginModule
{
public:
	LoginModule(std::shared_ptr<Server> server);

private:
	std::shared_ptr<Server> current_server;
	LoginPacket* login_packet;
public:
	void GetPacketData(tray::net::BufferObject&& buffer);
};

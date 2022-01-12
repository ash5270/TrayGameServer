#include "LoginModule.h"

LoginModule::LoginModule(std::shared_ptr<Server> server)
{
	this->current_server = server;
	login_packet = new LoginPacket();
}

void LoginModule::GetPacketData(tray::net::BufferObject&& buffer)
{
	tray::Log::Print("login packet");

}



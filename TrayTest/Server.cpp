#include "Server.h"

#include "PingPacket.h"

Server::Server(uint16_t port) :tray::net::TrayServer(port)
{

}

void Server::OnMessage(tray::net::BufferObject&& buffer)
{
	const PacketID packet_id = id_serializer.GetID(buffer.buffer);
	//uint16_t size = id_serializer.GetSize(&buffer.buffer);

	//packet_divide[packet_id](std::move(buffer));
	const auto packet_func = packet_divide.find(packet_id);
	if(packet_func!=packet_divide.end())
	{
		packet_func->second(std::move(buffer));
	}else
	{
		tray::Log::Error("Not found packet id:: ", static_cast<uint16_t>(packet_id));
	}
}

void Server::OnClientConnect(std::shared_ptr<tray::net::Session> session)
{
	tray::net::Buffer buffer;
	int data = 1200;
	uint16_t size = sizeof(data);	
}

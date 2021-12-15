#include "Server.h"

Server::Server(uint16_t port) :tray::net::TrayServer(port)
{
}

void Server::OnMessage(tray::net::BufferObject&& buffer)
{
	tray::Log::Print("Read Data");
	//PacketID id;
	//uint16_t size;
	int data;
	size_t offset=0;
	uint16_t id = tray::net::BufferReader::ReadInt16(buffer.buffer,offset);
	uint16_t size = tray::net::BufferReader::ReadInt16(buffer.buffer, offset);
	uint16_t userSize = tray::net::BufferReader::ReadInt16(buffer.buffer, offset);
	std::string userName = tray::net::BufferReader::ReadString(buffer.buffer, offset, userSize);
	uint16_t msgSize = tray::net::BufferReader::ReadInt16(buffer.buffer, offset);
	std::string msg = tray::net::BufferReader::ReadString(buffer.buffer, offset, userSize);

	tray::Log::Print("id: ",id," size: ",size, "user:", userName, " msg: ",msg  , "\n");
	

	tray::net::Buffer buffer2;
	int data2 = 1200;
	uint16_t size2 = sizeof(data2);



	//if (id == PacketID::message) {
		buffer.remote->Send(std::move(buffer2));
	//}
}

void Server::OnClientConnect(std::shared_ptr<tray::net::Session> session)
{
	tray::net::Buffer buffer;
	int data = 1200;
	uint16_t size = sizeof(data);

	
	
	//SendMsg(session, std::move(buffer));
}

#include "Server.h"

#include "PingPacket.h"

Server::Server(uint16_t port) :tray::net::TrayServer(port)
{

}

void Server::OnMessage(tray::net::BufferObject&& buffer)
{
	const PacketID packet_id = id_serializer.GetID(&buffer.buffer);
	uint16_t size = id_serializer.GetSize(&buffer.buffer);

	if( packet_id == PacketID::Message)
	{
		MessagePacket message_packet;
		message_packet.SetBuffer(&buffer.buffer);
		tray::Log::Print("Read Data");
		auto msg_data = message_packet.GetData();

		tray::Log::Print(" id: ", msg_data.user_id, " msg_size:", msg_data.message);

		auto send_buffer = message_packet.Serialize(msg_data);
		buffer.remote->Send(std::move(send_buffer));
	}
	else if(packet_id==PacketID::Ping)
	{
		tray::Log::Print("Receive Ping");
		PingPacket ping_packet;
		PingData ping;
		auto send_buffer = ping_packet.Serialize(ping);
		buffer.remote->Send(std::move(send_buffer));
	}
}

void Server::OnClientConnect(std::shared_ptr<tray::net::Session> session)
{
	tray::net::Buffer buffer;
	int data = 1200;
	uint16_t size = sizeof(data);
}

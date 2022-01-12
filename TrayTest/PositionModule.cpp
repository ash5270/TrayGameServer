#include "PositionModule.h"

PositionModule::PositionModule(std::shared_ptr<Server> server)
{
	this->current_server = server;
	pos_packet = new PosPacket();
}

void PositionModule::GetPacketData(tray::net::BufferObject&& buffer)
{
	tray::Log::Print("position packet ");
	auto data= pos_packet->GetData(&buffer.buffer);

	tray::Log::Print("user Id:", data.user_id, data.posX, ", ", data.posY, ", ", data.posZ);

}
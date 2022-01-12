#include "PosPacket.h"

PosPacket::PosPacket()
{
}

void PosPacket::serialize(tray::net::Buffer* buffer, PosData pos_data)
{
	pos_serialize.Serialize(*buffer, pos_data);
}

PosData PosPacket::GetData(tray::net::Buffer* buffer)
{
	PosData pos_data;
	pos_serialize.DeSerialize(*buffer, pos_data);
	return pos_data;
}

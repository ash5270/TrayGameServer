#include "PacketIDSerializer.h"

PacketID PacketIDSerializer::GetID(const tray::net::Buffer& buffer)
{
	PacketID id;
	size_t offset = 0;
	auto result = DeSerialize(buffer, offset, id);

	return id;
}

uint16_t PacketIDSerializer::GetSize(const tray::net::Buffer& buffer)
{
	uint16_t size;
	size_t offset = 2;
	auto result = DeSerialize(buffer, offset, size);

	return size;
}

#pragma once
#include <Serializer.h>
#include<Buffer.h>
#include"PacketIData.h"

class PingPacket
{
public:
	class PingSerializer : public tray::net::Serializer
	{
	public:
		bool PingSerialize(tray::net::Buffer& buffer, const PingData& ping)
		{
			PacketID id = ping.packet_id;
			uint16_t size = ping.packet_size;
			bool result = Serialize(buffer, id);
			result = Serialize(buffer, size);

			return result;
		}
	};

public:
	PingPacket();
	~PingPacket();

private:
	PingData ping_data;
	PingSerializer ping_serializer;

public:

	tray::net::Buffer Serialize(PingData ping_data)
	{
		tray::net::Buffer buffer;
		ping_serializer.PingSerialize(buffer, ping_data);
		return buffer;
	}
};


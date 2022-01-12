#pragma once
#include <Serializer.h>
#include <Buffer.h>
#include "PacketIData.h"
#include "PacketIDSerializer.h"


class PosPacket
{
public:
	class PosSerialize : public tray::net::Serializer
	{
	private:
		PacketIDSerializer id_serializer;
	public:
		bool Serialize(tray::net::Buffer& buffer, PosData& pos_data)
		{
			PacketID id = PacketID::Position;
			bool result = tray::net::Serializer::Serialize(buffer, id);
			uint16_t packet_size = pos_data.GetSize();


			return true;
		}

		bool DeSerialize(tray::net::Buffer& buffer, PosData& pos_data)
		{
			auto id = id_serializer.GetID(buffer);
			auto size = id_serializer.GetSize(buffer);
			size_t offset = 4;
			bool result = tray::net::Serializer::DeSerialize(buffer, offset, pos_data.user_id);
			result = tray::net::Serializer::DeSerialize(buffer, offset, pos_data.posX);
			result = tray::net::Serializer::DeSerialize(buffer, offset, pos_data.posY);
			result = tray::net::Serializer::DeSerialize(buffer, offset, pos_data.posZ);

			result = tray::net::Serializer::DeSerialize(buffer, offset, pos_data.rotX);
			result = tray::net::Serializer::DeSerialize(buffer, offset, pos_data.rotY);
			result = tray::net::Serializer::DeSerialize(buffer, offset, pos_data.rotZ);

			return true;
		}
	};
public:
	PosPacket();
private:
	PosSerialize pos_serialize;
	tray::net::Buffer* buffer;
public:
	void serialize(tray::net::Buffer* buffer, PosData pos_data);
	PosData GetData(tray::net::Buffer* buffer);
};

#pragma once
#include<Serializer.h>
#include<Buffer.h>
#include"PacketIData.h"

class MessagePacket
{
public:
	class MessageSerializer: public tray::net::Serializer
	{
	public:
		bool  MsgSerialize(tray::net::Buffer& msg_buffer,MessageData& msg_packet)
		{
			
			PacketID id = PacketID::Message;
			bool result = Serialize(msg_buffer, id);
			uint16_t size = msg_packet.GetSize();
			result = Serialize(msg_buffer, size);
			result = Serialize(msg_buffer,msg_packet.user_id_length);
			result = Serialize(msg_buffer, msg_packet.user_id, msg_packet.user_id_length);
			result = Serialize(msg_buffer, msg_packet.message_length);
			result = Serialize(msg_buffer, msg_packet.message, msg_packet.message_length);

			return result;
		}

		bool MsgDeSerialize(tray::net::Buffer& msg_buffer, MessageData& msg_packet)
		{
			size_t offset = 4;
			bool result = DeSerialize(msg_buffer, offset, msg_packet.user_id_length);
			result= DeSerialize(msg_buffer, offset, msg_packet.user_id, msg_packet.user_id_length);
			result= DeSerialize(msg_buffer, offset, msg_packet.message_length);
			result= DeSerialize(msg_buffer, offset, msg_packet.message, msg_packet.message_length);

			return result;
		}	
	};

public:
	MessagePacket();
	MessagePacket(MessageData msg_data);
	~MessagePacket();

private:
	MessageData msg_data;
	tray::net::Buffer* buffer;
	MessageSerializer msg_serializer;

public:
	tray::net::Buffer Serialize(MessageData msgData)
	{
		tray::net::Buffer buffer;
		msg_serializer.MsgSerialize(buffer, msgData);
		return buffer;
	}

	MessageData GetData()
	{
		msg_serializer.MsgDeSerialize(*buffer, msg_data);
		return msg_data;
	}

	void ResetBuffer();
	void SetBuffer(tray::net::Buffer* buffer);
};	

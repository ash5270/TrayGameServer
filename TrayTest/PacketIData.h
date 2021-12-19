#pragma once
#include<string>

enum class PacketID : uint16_t
{
	Message=0,
	Ping = 2004,
};

struct PacketData
{
	PacketID packet_id;
	uint16_t packet_size;
	virtual uint16_t GetSize() = 0;
};	

struct MessageData :public PacketData
{
	MessageData()
	{
		packet_id = PacketID::Message;
		packet_size = 0;
	}

	std::string user_id;
	std::string message;
	uint16_t message_length;	
	uint16_t user_id_length;

	uint16_t GetSize() override
	{
		packet_size = sizeof(message_length) + sizeof(user_id_length) + message_length + user_id_length;
		return packet_size;
	}
};

struct PingData :public PacketData
{
	PingData()
	{
		packet_id = PacketID::Ping;
		packet_size = 0;
	}

	uint16_t GetSize() override
	{
		return packet_size;
	}
};


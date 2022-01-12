#pragma once
#include<string>

enum class PacketID : uint16_t
{
	Message=0,
	Position=100,
	Ping = 2004,
	Login=5000,
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

struct PosData : public PacketData
{
	PosData()
	{
		user_id = 0;
		packet_id = PacketID::Position;
		posX = posY = posZ = rotX = rotY = rotZ = 0.0f;
	}

	uint16_t user_id;

	float posX;
	float posY;
	float posZ;

	float rotX;
	float rotY;
	float rotZ;

	uint16_t GetSize() override
	{
		packet_size = sizeof(uint16_t) + sizeof(posX) + sizeof(posY) + sizeof(posZ) +
			sizeof(rotX) + sizeof(rotY) + sizeof(rotZ);
		return packet_size;
	}

};

struct LoginData: public  PacketData
{
	LoginData()
	{
		packet_id = PacketID::Login;
	}

	uint16_t GetSize() override
	{
		packet_size = sizeof(uint16_t) + sizeof(uint16_t) + user_id_length + pass_wd_length;
	}

	std::string user_id;
	std::string pass_wd;

	uint16_t user_id_length;
	uint16_t pass_wd_length;

};


#pragma once
#include <Serializer.h>
#include <Buffer.h>
#include "PacketIData.h"

class LoginPacket 
{
public:
	class LoginSerializer :public tray::net::Serializer
	{
	public:
		bool LoginSerialize(tray::net::Buffer& buffer, LoginData& login_data)
		{
			PacketID packet_id = PacketID::Login;
			bool result = Serialize(buffer, packet_id);
		}
		bool LoginDeSerialize(const tray::net::Buffer& buffer, LoginData& login_data)
		{
			size_t offset = 4;
			bool result = DeSerialize(buffer, offset, login_data.user_id_length);
			result = DeSerialize(buffer, offset, login_data.user_id);

			result = DeSerialize(buffer, offset, login_data.pass_wd_length);
			result = DeSerialize(buffer, offset, login_data.pass_wd);

			return result;
		}
	};

public:
	LoginPacket();
	tray::net::Buffer* buffer;
	LoginSerializer login_serializer;
public:
	tray::net::Buffer Serialize(LoginData login_data)
	{
		tray::net::Buffer buffer;
		login_serializer.LoginSerialize(buffer, login_data);
		return buffer;
	}

	LoginData GetData(tray::net::Buffer& buffer)
	{
		LoginData login_data;
		login_serializer.LoginDeSerialize(buffer, login_data);
		return login_data;
	}

};

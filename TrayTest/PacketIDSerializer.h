#pragma once
#include <iostream>
#include <Serializer.h>
#include <Buffer.h>
#include "PacketIData.h"

class PacketIDSerializer: public tray::net::Serializer
{
public:
	PacketID GetID(const tray::net::Buffer* buffer);
	uint16_t GetSize(const tray::net::Buffer* buffer);
};
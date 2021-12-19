#include "MessagePacket.h"

MessagePacket::MessagePacket()
{
	buffer = NULL;
}

MessagePacket::MessagePacket(MessageData msg_data)
{
	this->msg_data = msg_data;
}

MessagePacket::~MessagePacket()
{	
	
}

void MessagePacket::ResetBuffer()
{

}

void MessagePacket::SetBuffer(tray::net::Buffer* buffer)
{
	this->buffer = buffer;
}
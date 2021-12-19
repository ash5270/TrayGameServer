#pragma once
#include "Buffer.h"
namespace tray
{
	namespace net
	{
		class Serializer {
		public:
			bool Serialize(Buffer& buffer,const std::string& msg,const size_t& msgSize)
			{
				const uint16_t msg_size = static_cast<uint16_t>(msgSize);
				buffer.Write(&msg_size, sizeof(msg_size	));
				buffer.Write(&msg, msgSize);

				return  true;
			}

			/*template<typename T>
			bool Serialize(Buffer& buffer,T& data,const size_t& size)
			{
				buffer.Write(&data, size);
			}*/

			template<typename T>
			bool Serialize(Buffer& buffer, T& data)
			{
				buffer.Write(&data, sizeof(T));
				return true;
			}

			bool DeSerialize(const Buffer& buffer, size_t& offset, std::string& data, const uint16_t size)
			{
				constexpr uint8_t last_string= 1;
				char* msg = new char[size + last_string];
				memset(msg, 0, size + last_string);
				if(buffer.Capacity()>offset+size)
				{
					memcpy_s(msg, size, buffer.GetBuffer()+offset, size);
					offset += size;
					data = std::string(msg);
					return true;
				}else
				{
					return false;
				}
			}

			template<typename T>
			bool DeSerialize(const Buffer& buffer,size_t& offset, T& data)
			{
				const size_t data_size = sizeof(T);
				if(buffer.Capacity()>offset+data_size)
				{
					memcpy_s(&data, data_size, buffer.GetBuffer() + offset, data_size);
					offset += data_size;
					return true;
				}
				else
				{
					return false;
				}
			}
		};
	}
}
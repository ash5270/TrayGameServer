#pragma once
#include "Buffer.h"
namespace tray
{
	namespace net
	{
		class Serializer {
		public:
			//16bit int return
			uint16_t ReadInt16(Buffer& buffer, size_t& offset) {
				size_t size = sizeof(uint16_t);
				uint16_t data = 0;
				memcpy_s(&data, size, buffer.GetBuffer() + offset, size);
				offset += size;
				return data;
			}

			//string return
			std::string ReadString(Buffer& buffer, size_t& offset, const size_t& size) {
				char* data = new char[size + 1];
				memset(data, 0, size + 1);
				memcpy_s(data, size, buffer.GetBuffer() + offset, size);
				offset += size;
				std::string msg(std::move(data));

				return msg;
			}

			//32bit int return
			uint32_t ReadInt32(Buffer& buffer, size_t& offset) {
				size_t size = sizeof(uint32_t);
				uint32_t data = 0;
				memcpy_s(&data, size, buffer.GetBuffer() + offset, size);
				offset += size;
				return data;
			}

			//float return
			float ReadFloat(Buffer& buffer, size_t& offset) {
				size_t size = sizeof(float);
				float data = 0;
				memcpy_s(&data, size, buffer.GetBuffer() + offset, size);
				offset += size;
				return data;
			}

			//double return
			double ReadDouble(Buffer& buffer, size_t& offset) {
				size_t size = sizeof(double);
				double data = 0;
				memcpy_s(&data, size, buffer.GetBuffer() + offset, size);
				offset += size;
				return data;
			}
		public:

			template<typename T>
			bool Serialize(Buffer& buffer,T& data,const size_t& size)
			{
				
			}



		public:
			bool DeSerialize(Buffer& buffer, size_t& offset, std::string& data, const uint16_t& size)
			{
				char* msg = new char[size + 1];
				memset(msg, 0, size + 1);
				if(buffer.Size()>offset+size)
				{
					memcpy_s(msg, size, buffer.GetBuffer()+offset, size);
					offset += size;
					return true;
				}else
				{
					return false;
				}
			}

			template<typename T>
			bool DeSerialize(Buffer& buffer,size_t& offset,T& data)
			{
				size_t data_size = sizeof(T);
				if(buffer.Size()>offset+data_size)
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
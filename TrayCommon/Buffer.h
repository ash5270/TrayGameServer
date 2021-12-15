#pragma once
#include"TrayCommon.h"

namespace tray {
	namespace net {

		class Buffer {
		public:
			const static unsigned int BUFFER_SIZE = 1024;
		public:
			Buffer()
				:m_data(new uint8_t[BUFFER_SIZE]),
				m_capacity(BUFFER_SIZE),
				m_offset(0){
			}

			Buffer(size_t size) 
				:m_data(new uint8_t[size]),
				m_capacity(size),
				m_offset(0){}
			
			Buffer(const Buffer& buffer)
				:m_data(new uint8_t[buffer.m_capacity]),
				m_capacity(buffer.m_capacity),
				m_offset(buffer.m_offset)
			{
				memcpy_s(m_data, m_capacity, buffer.m_data, buffer.m_capacity);
			}

			Buffer(Buffer&& buffer) noexcept
				:m_data(buffer.m_data),
				m_capacity(buffer.m_capacity),
				m_offset(buffer.m_offset)
			{
				buffer.m_data = nullptr;
				buffer.m_capacity = 0;
				buffer.m_offset = 0;
			}

			~Buffer() {
				delete m_data;
				m_data = nullptr;
				m_capacity = 0;
					m_offset = 0;
			}
			
			
		public:
			 size_t Size() const { return m_offset; }
			 size_t Capacity() const { return m_capacity; }

			/*bool Write(const std::string& data) {

			}*/

			/*template<typename T>
			bool Write(const T& data) {
				uint8_t dataSize = sizeof(T);
				if (m_offset + dataSize > m_capacity) {
					return false;
				}

				size_t currentCap = m_capacity - m_offset;
				memcpy_s(m_data + m_offset, currentCap, &data, dataSize);
				m_offset += dataSize;
				return true;
			}*/

			bool Write(const uint8_t* data, size_t size) {
				if (m_offset + size > m_capacity) {
					return false;
				}
				
				size_t currentCap = m_capacity - m_offset;
				memcpy_s(m_data + m_offset, currentCap, data, size);
				m_offset += size;
				return true;
			}

			void Clear() {
				m_offset = 0;
				memset(m_data, 0, m_capacity);
			}

			Buffer& operator=(tray::net::Buffer&& buffer) noexcept {
				m_capacity = buffer.m_capacity;
				m_offset = buffer.m_offset;
				m_data = buffer.m_data;

				buffer.m_capacity = 0;
				buffer.m_offset = 0;
				buffer.m_data = nullptr;
				return *this;
			}

			Buffer& operator=(tray::net::Buffer& buffer) {
				m_capacity = buffer.m_capacity;
				m_offset = buffer.m_offset;
				
				memcpy_s(m_data, m_capacity, buffer.m_data, buffer.m_capacity);
				return *this;
			}

		public:
			uint8_t* GetBuffer() const {
				return m_data;
			}

			void SetOffset(size_t size) {
				m_offset = size;	
			}

			size_t GetOffset() const {
				return m_offset;
			}

		private:
			uint8_t* m_data;
			
			size_t m_capacity;
			size_t m_offset;

		};


		static class BufferReader {
		public:
			//16bit int return
			static uint16_t ReadInt16(Buffer& buffer,size_t& offset) {
				size_t size = sizeof(uint16_t);
				uint16_t data = 0;	
				memcpy_s(&data, size, buffer.GetBuffer() + offset, size);
				offset += size;
				return data;
			}

			//string return
			static std::string ReadString(Buffer& buffer, size_t& offset, const size_t& size) {
				char* data = new char[size+1];
				memset(data, 0, size + 1);
				memcpy_s(data, size, buffer.GetBuffer()+offset, size);
				offset += size;
				std::string msg(std::move(data));
				
				return msg;
			}

			//32bit int return
			static uint32_t ReadInt32(Buffer& buffer, size_t& offset) {
				size_t size = sizeof(uint32_t);
				uint32_t data = 0;
				memcpy_s(&data, size, buffer.GetBuffer() + offset, size);
				offset += size;
				return data;
			}

			//float return
			static float ReadFloat(Buffer& buffer, size_t& offset) {
				size_t size = sizeof(float);
				float data = 0;
				memcpy_s(&data, size, buffer.GetBuffer() + offset, size);

				offset += size;
				return data;
			}

			//double return
			static double ReadDouble(Buffer& buffer,  size_t& offset) {
				size_t size = sizeof(double);
				double data = 0;
				memcpy_s(&data, size, buffer.GetBuffer() + offset, size);
				offset += size;
				return data;
			}
		};
	}
}
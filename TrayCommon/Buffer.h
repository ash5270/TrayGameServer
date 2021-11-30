#pragma once
#include"TrayCommon.h"

namespace tray {
	namespace net {
		class Buffer {
		public:
			Buffer() :m_bufferSize(1024) {
				m_data.resize(m_bufferSize);
				m_offset = 0;
				m_readOffset = 0;
			}

			Buffer(size_t size) : m_bufferSize(size) {
				m_data.resize(m_bufferSize);
				m_offset = 0;
				m_readOffset = 0;
			}

		public:
			template<typename DataType>
			void WriteData(const DataType& data) {
				size_t i = m_offset;
				memcpy_s(m_data.data() + i, sizeof(DataType), &data, sizeof(DataType));
				m_offset += sizeof(DataType);
			}

			/*bool DataWrite(const std::string& data) {

				return true;
			}*/


			void ReadData(std::string& data) {
				uint16_t len;
				memcpy_s(&len, sizeof(uint16_t), m_data.data() + m_readOffset, sizeof(uint16_t));

				m_readOffset += sizeof(uint16_t);
				data.resize((size_t)len);

				memcpy_s(data.data(), (size_t)len, m_data.data()+ m_readOffset, (size_t)len);
				m_readOffset += len;
			}

			template<typename DataType>
			void ReadData(DataType& data) {
				size_t i = m_readOffset;
				memcpy(&data, m_data.data() + i, sizeof(DataType));
				m_readOffset += sizeof(DataType);

			}

			size_t GetOffset() {
				return m_offset;
			}

		public:
			void Clear() {
				memset(m_data.data(), 0, m_bufferSize);
				m_offset = 0;
				m_readOffset = 0;
			}

			size_t GetBufferSize() {
				return m_bufferSize;
			}
			std::vector<uint8_t> m_data;
		private:

			std::size_t m_offset;
			std::size_t m_readOffset;

			std::size_t m_bufferSize;
		};
	}
}
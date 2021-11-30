#pragma once
#include"TrayCommon.h"

namespace tray {
	namespace net{
		struct DataHeader {
			uint8_t id = {};
			size_t size;
		};

		class DataBuffer {
		public:
			DataBuffer() {
				body.resize(1024);
			}

		public:
			template<typename dataType>
			void WirteData(const dataType& data) {
				size_t i = body.size();
				body.resize(body.size() + sizeof(dataType));
				std::memcpy(body.data() + i, &data, sizeof(dataType));
				header.size = body.size();
			}

			void WirteData(const std::string& data) {
				uint16_t msg_size = data.length();
				size_t i = body.size();

				body.resize(body.size() + msg_size + sizeof(msg_size));
				std::memcpy(body.data() + i, &msg_size, sizeof(msg_size));

				i += sizeof(msg_size);
				std::memcpy(body.data() + i, data.data(), msg_size);
				header.size = body.size();
			}

	

		template<typename dataType>
			void ReadData(dataType& data) {
				size_t i = body.size() - sizeof(dataType);
				std::memcpy(&data, body.data() + i, sizeof(dataType));
				body.resize(i);
				header.size = body.size();
			}

			void ReadData(std::string& data) {
				uint16_t msg_size = 0;
				std::memcpy(&msg_size, body.data(), sizeof(uint16_t));
				
				body.erase(body.begin(), body.begin() + sizeof(uint16_t));
				std::string x(body.begin(), body.begin() + msg_size);
		
				body.erase(body.begin(), body.begin() + msg_size);
				data = x;
			}

		public:
			DataHeader header{};
			std::vector<uint8_t> body;
		};

		class Session;
		struct MSGQueue {
			std::shared_ptr<Session> remote = nullptr;
			DataBuffer data;

		};
	}
}
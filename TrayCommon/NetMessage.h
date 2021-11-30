#pragma once
#include "TrayCommon.h"

namespace tray {
	namespace net {
		template<typename T>
		struct message_header {
			T id{};
			uint32_t size = 0;
		};

		template<typename T>
		struct message {
			message_header<T> header{};
			std::vector<uint8_t> body;

			// body size return
			size_t size() const {
				return body.size();
			}	

			friend std::ostream& operator <<(std::ostream& os, const message<T>& msg) {
				os << "ID: " << int(msg.header.id) << " size:" << msg.header.size;
				return os;
			}

			template<typename DataType>
			void WirteMsg(const DataType& data) {
				size_t i = body.size();
				body.resize(body.size() + sizeof(DataType));
				std::memcpy(body.data() + i, &data, sizeof(DataType));
				header.size = size();
			}

			template<typename DataType>
			void ReadMsg(DataType& data) {
				size_t i = body.size() - sizeof(DataType);
				std::memcpy(&data, body.data() + i, sizeof(DataType));
				body.resize(i);
				header.size = size();
			}

			void WirteMsg(const std::string& data, size_t len) {
				size_t i = body.size();
				body.resize(body.size() + len);
				std::memcpy(body.data() + i, data.data(), len);
				header.size = size();
			}
		};
	}
}
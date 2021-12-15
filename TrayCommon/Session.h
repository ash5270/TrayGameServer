#pragma once
#include"TrayCommon.h"
#include"Buffer.h"
#include"BufferQueue.h"
using namespace boost;

namespace tray{ 
	namespace net {
		class Session : public std::enable_shared_from_this<Session> {
		public:
			enum class SessionType
			{
				Server,
				Client
			};
				
		public:
			Session(SessionType type, asio::io_context& asioContext,
				asio::ip::tcp::socket,TsQueue<BufferObject>* packets );
			bool ConnectToClient();
			bool ConnectToServer();

			void Disconnect();
			
			void ReadData();
			void ReadDataCallBack(system::error_code ec, size_t transferred);

			void SendData();
			void SendDataCallBack(system::error_code ec, size_t transferred);

			void Send(Buffer&& buffer);
	

			bool IsConnect() {
				return m_socket.is_open();
			}

		private:
			asio::io_context& m_context;
			asio::ip::tcp::socket m_socket;

			Buffer m_writeBuffer;
			Buffer m_readBuffer;

			//std::queue<DataBuffer> m_readBuffers;
			TsQueue<Buffer> m_writeBuffers;

			TsQueue<BufferObject>* m_packets;
			SessionType m_currentType;
		};
	}
}	
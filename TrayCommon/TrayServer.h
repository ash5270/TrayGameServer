#pragma once
#include"TrayCommon.h"
#include"Session.h"
#include"BufferQueue.h"

using namespace boost;

namespace tray{
	namespace net {
		class TrayServer 
		{
		public:
			TrayServer(uint16_t port);
		private:
			void WaitForClientConnection();
			
		public:
			bool Start();
			bool Stop(); 
			void Update();

			void DisconnectClient(std::shared_ptr<Session> session);

			void SendMsg(std::shared_ptr<Session> session,Buffer&& data);
			void AllSendMsg(Buffer&& data);

		public:
			virtual void OnClientConnect(std::shared_ptr<Session> session);
			virtual void OnMessage(BufferObject&& buffer);
		protected:
			asio::io_context m_asioContext;
			asio::ip::tcp::acceptor m_acceptor;

			uint32_t nIdCounter = 10000;
			std::thread m_threadContext;

			TsQueue<BufferObject>* m_packets;
			std::deque<std::shared_ptr<Session>> clients;
		};



	}
}


#include "TrayServer.h"
#include<chrono>

void tray::net::TrayServer::WaitForClientConnection()
{
	m_acceptor.async_accept([this](std::error_code ec,asio::ip::tcp::socket socket)
		{
			std::shared_ptr<Session> newSession =
				std::make_shared<Session>(Session::SessionType::Server, m_asioContext, std::move(socket), m_packets);

			if (newSession)
			{
				clients.push_back(std::move(newSession));
				clients.back()->ConnectToClient();
			}

			WaitForClientConnection();
		});
}


bool tray::net::TrayServer::Start()
{
	try {
		WaitForClientConnection();
		m_threadContext = std::thread([this]() {m_asioContext.run(); });
	}
	catch (std::exception& e) {
		Log::Error(e.what());
		return false;
	}

	Log::Print("Start Server");
	return true;
}

bool tray::net::TrayServer::Stop()
{
	m_asioContext.stop();
	if (m_threadContext.joinable())
		m_threadContext.join();
		
	Log::Print("Stop Server");
	return true;
}

void tray::net::TrayServer::Update()
{
	while (true)
	{
		if (!m_packets->IsEmpty()) {
			BufferObject data = m_packets->FrontData();
			OnMessage(data.remote, data.buffer);
		}
	}
}

void tray::net::TrayServer::AllSendMsg(Buffer& data)
{
	for (auto& client : clients) {
		client->Send(data);
	}	
}

void tray::net::TrayServer::OnMessage(std::shared_ptr<Session> session, Buffer& buffer)
{

}

tray::net::TrayServer::TrayServer(uint16_t port)
	:m_acceptor(m_asioContext,asio::ip::tcp::endpoint(asio::ip::tcp::v4(),port))
{
	m_packets = new TsQueue<BufferObject>();
}

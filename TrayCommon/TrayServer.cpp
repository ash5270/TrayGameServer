#include "TrayServer.h"
#include<algorithm>
#include<chrono>

void tray::net::TrayServer::WaitForClientConnection()
{
	m_acceptor.async_accept([this](std::error_code ec,asio::ip::tcp::socket socket)
		{
			std::shared_ptr<Session> newSession =
				std::make_shared<Session>(Session::SessionType::Server, m_asioContext, std::move(socket), m_packets);

			if (newSession)
			{
				OnClientConnect(newSession);
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
			OnMessage(std::move(data));
		}
		
	}
}

void tray::net::TrayServer::DisconnectClient(std::shared_ptr<Session> session)
{

}

void tray::net::TrayServer::SendMsg(std::shared_ptr<Session> session, Buffer&& data)
{
	if (session->IsConnect()) {
		session->Send(std::move(data));
	}
	else {
		Log::Print("Disconnect");
	}
}

void tray::net::TrayServer::AllSendMsg(Buffer&& data)
{
	if (clients.size() > 0) {
		for (auto& client : clients) {
			if (client && client->IsConnect()) {
				client->Send(std::move(data));
				
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}
			else {
				clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());
			}
			Log::Print("client size:: ", clients.size());
		}
	}
	
}

void tray::net::TrayServer::OnClientConnect(std::shared_ptr<Session> session)
{

}

void tray::net::TrayServer::OnMessage(BufferObject&& buffer)
{

}

tray::net::TrayServer::TrayServer(uint16_t port)
	:m_acceptor(m_asioContext,asio::ip::tcp::endpoint(asio::ip::tcp::v4(),port))
{
	m_packets = new TsQueue<BufferObject>();
}

#include "Session.h"



tray::net::Session::Session(SessionType type, asio::io_context& asioContext,
	asio::ip::tcp::socket socket, TsQueue<BufferObject>* packets)
	:m_context(asioContext), m_socket(std::move(socket)), m_currentType(type), m_writeBuffers(),m_readBuffer()
{
	Log::Print("Session Create");
	asio::ip::tcp::no_delay option(true);
	m_socket.set_option(option);
	m_packets = packets;
}

bool tray::net::Session::ConnectToClient()
{
	if (m_currentType == SessionType::Server) {
		if (m_socket.is_open()) {
			ReadData();
			return true;
		}
	}
	return false;
}

bool tray::net::Session::ConnectToServer()
{
	return false;
}

void tray::net::Session::Disconnect()
{
	Log::Print("Disconnect");
	if (m_socket.is_open()) {
		asio::post(m_context, [this]() {
			m_socket.shutdown(asio::ip::tcp::socket::shutdown_both);
			m_socket.close();
			});
	}

}

void tray::net::Session::ReadData()
{
	
	m_socket.async_read_some(asio::buffer(m_readBuffer.GetBuffer(),m_readBuffer.Capacity()), bind(&Session::ReadDataCallBack,
		shared_from_this(), asio::placeholders::error, asio::placeholders::bytes_transferred));
}

void tray::net::Session::ReadDataCallBack(system::error_code ec, size_t transferred)
{
	if (!ec) {
		if (transferred < sizeof(uint32_t))
		{
			Log::Error("Read Size Error:", transferred);
			ReadData();
		}
		else {
			BufferObject obj;
			obj.remote = this->shared_from_this();
			obj.buffer = m_readBuffer;
			m_packets->PushBack(std::move(obj));
			
			m_readBuffer.Clear();
			ReadData();
		}
	}
	else {
		Disconnect();
	}
}

void tray::net::Session::SendData()
{
	m_writeBuffers.Front(m_writeBuffer);
	m_socket.async_write_some(asio::buffer(m_writeBuffer.GetBuffer(),m_writeBuffer.Size()),
		bind(&Session::SendDataCallBack, shared_from_this(), asio::placeholders::error, asio::placeholders::bytes_transferred));
}

void tray::net::Session::SendDataCallBack(system::error_code ec, size_t transferred)
{
	if (!ec) {
		Log::Print("send success");
	}
}

void tray::net::Session::Send(Buffer&& buffer)
{
	//test
	//asio::post(m_context, bind(&Session::SendCallBack, shared_from_this(),std::move(buffer)));
	asio::post(m_context, [this, buffer] {
			Log::Print("Input data");
			m_writeBuffers.PushBack(std::move(buffer));
			SendData();
		});
}
	




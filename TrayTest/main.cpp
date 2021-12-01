#include<TrayCommon.h>
#include<NetMessage.h>
#include<NetBuffer.h>
#include<TrayServer.h>
#include<Buffer.h>
#include<Log.h>

using namespace tray::net;
enum class TestType
{
	test,
};

class Server:public TrayServer  {
public:
	Server(uint16_t port):TrayServer(port)	
	{

	}
public:
	virtual void OnMessage(std::shared_ptr<Session> session, Buffer& buffer) {
		tray::Log::Print("Data Read");
	}
};





int main(){
	tray::LogSystem::instance().Start();
	
	Server server(3000);
	server.Start();

	while (1)
	{
		server.Update();
		
	}

	server.Stop();

	return 0;
}
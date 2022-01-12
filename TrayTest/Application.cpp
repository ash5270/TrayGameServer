#include "Application.h"

Application::Application() 
{
	server = std::make_shared<Server>(3000);
}

Application::~Application()
{
}

void Application::Awake()
{
	tray::LogSystem::instance().Start();
}

void Application::Start()
{
	server->Start();

	position_module = new PositionModule(server);
	login_module = new LoginModule(server);

	server->packet_divide.insert(std::make_pair(PacketID::Position,
		[this](tray::net::BufferObject&& buffer) {position_module->GetPacketData(std::move(buffer)); }));
	server->packet_divide.insert(std::make_pair(PacketID::Login,
		[this](tray::net::BufferObject&& buffer) {login_module->GetPacketData(std::move(buffer)); }));

}

void Application::Update()
{
	while (true)
	{
		server->Update();
	}
}

void Application::End()
{
	server->Stop();
}

void Application::Exit()
{

}

void Application::Run()
{
	Awake();
	
	Start();

	Update();

	End();

	Exit();
}


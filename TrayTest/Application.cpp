#include "Application.h"

Application::Application() : server(3000)
{
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
	server.Start();
}

void Application::Update()
{
	while (1)
	{
		server.Update();
	}
}

void Application::End()
{
	server.Stop();
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


#pragma once

#include"Server.h"
#include"PositionModule.h"
#include"LoginModule.h"

class Application
{
public:
	Application();
	~Application();
private:
	void Awake();
	void Start();
	void Update();
	void End();
	void Exit();
public:
	void Run();

private:
	std::shared_ptr<Server> server;

	PositionModule* position_module;
	LoginModule* login_module;
	
};


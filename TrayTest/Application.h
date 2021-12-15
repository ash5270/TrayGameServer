#pragma once

#include"Server.h"

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
	Server server;

};


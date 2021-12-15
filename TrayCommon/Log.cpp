#include"Log.h"

tray::LogSystem* tray::LogSystem::m_instnace = NULL;
tray::LogSystem& tray::Log::m_logSystem = tray::LogSystem::instance();
tray::LogData tray::Log::m_logData;

tray::LogSystem::LogSystem()
{
	m_isQueueLoop = false;
}

tray::LogSystem::~LogSystem()
{
	Disable();
}

void tray::LogSystem::Start()
{
	m_isQueueLoop = true;
	m_logThread = std::thread(&LogSystem::Update, this);
	ResetColor();
}

void tray::LogSystem::Disable()
{
	m_isQueueLoop = false;
	if (m_logThread.joinable())
		m_logThread.join();
}

void tray::LogSystem::DataEmplace(const LogData& data)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_logData.emplace(data);
}

void tray::LogSystem::Update()
{
	while (m_isQueueLoop) {
		if (m_logData.size() > 0) {
			std::lock_guard<std::mutex> lock(m_mutex);
			auto data= DataDequeue();
			DataCheck(data);
		}else{
			
		}
	}
}

tray::LogData tray::LogSystem::DataDequeue()
{
	LogData data = m_logData.front();
	m_logData.pop();
	return data;
}

void tray::LogSystem::DataCheck(const LogData data) 
{
	switch (data.type)
	{
	case LogData::LogType::Error:
		SetColor(color::RED);
		std::cout<<"[ERROR] "<< data.m_msg << std::endl;
		ResetColor();
		break;

	case LogData::LogType::Log:
		std::cout<<"[LOG] " << data.m_msg << std::endl;
		break;

	case LogData::LogType::Waring:
		SetColor(color::YELLOW);
		std::cout<<"[WARING] " << data.m_msg << std::endl;
		ResetColor();
		break;
	}
}
#pragma once
#include<thread>
#include<iostream>
#include<string>
#include<queue>
#include<WinSock2.h>
#include<windows.h>
#include<mutex>

namespace tray{
	struct LogData{
		LogData() = default;

		LogData(const LogData& data) {
			m_msg = data.m_msg;
			type = data.type;
		}
	
		enum class LogType {
			Error,
			Log,
			Waring,

			Empty=10000
		};

		void clear() {
			type = LogType::Empty;
			m_msg = "";
		}

		LogType type;
		std::string m_msg;
		
	};

	
	//참조하는법 -> 알아보기
	class LogSystem {
	public:
		static LogSystem& instance() {
			if (m_instnace == NULL) {
				m_instnace = new LogSystem();
			}
			
			return *m_instnace;
		}

		LogSystem();
		~LogSystem();

	public:
		enum color : int {
			BLACK = 1,
			BLUE,
			GREEN,
			CYAN,
			RED = 12,
			MAGENTA = 13,
			YELLOW = 14,
			WHITE = 15
		};

	public:
		void Start();
		void Disable();
		void DataEmplace(const LogData& data);
	private:
		//log data dequeue
		LogData DataDequeue();
		//log data check
		void DataCheck(LogData data);
		//update loop
		void Update();
		//set color 
		void SetColor(int color) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		}

		void ResetColor() {
			SetColor(color::WHITE);
		}
		
	private:
		std::thread m_logThread;
		static LogSystem* m_instnace;
		std::queue<LogData> m_logData;
		bool m_isQueueLoop;

		std::mutex m_mutex;
	};

	 
	class Log {
	private:
		
	public:
		//print template
		template<typename T>
		static void Error(T arg) {
			m_logData.type = LogData::LogType::Error;
			MakeString(arg);
			m_logSystem.DataEmplace(m_logData);
			m_logData.clear();
		}

		template<typename T, typename ... Types> 
		static void Error(T arg, Types... args) {
			MakeString(arg);
			Error(args...);
		}

		template<typename T>
		static void Waring(T arg) {
			m_logData.type = LogData::LogType::Waring;
			MakeString(arg);
			m_logSystem.DataEmplace(m_logData);
			m_logData.clear();
		}

		template<typename T, typename ... Types>
		static void Waring(T arg, Types... args) {
			MakeString(arg);
			Waring(args...);
		}

		template<typename T>
		static void Print(T arg) {
			m_logData.type = LogData::LogType::Log;
			MakeString(arg);
			m_logSystem.DataEmplace(m_logData);
			m_logData.clear();
		}

		template<typename T, typename ... Types>
		static void Print(T arg, Types... args) {
			MakeString(arg);
			Print(args...);
		}


		template<typename T>
		static void Print(LogSystem::color color,T arg) {
			m_logData.type = LogData::LogType::Log;
			MakeString(arg);
			m_logSystem.DataEmplace(m_logData);
			m_logData.clear();
		}

		template<typename T, typename ... Types>
		static void Print(LogSystem::color color, T arg, Types... args) {
			MakeString(arg);
			Print(color,args...);
		}


	private:
		//make string 
		static void MakeString(const std::string data) {
			m_logData.m_msg += data.data();
		}

		static void MakeString(char* data) {
			m_logData.m_msg += std::string(data);
		}

		static void MakeString(float data)
		{
			m_logData.m_msg += std::to_string(data);
		}
		
		template<typename T,std::enable_if_t<std::is_integral<T>::value,int> = 0 >
		static void MakeString(const T  data) {
			m_logData.m_msg += std::to_string(data);
		}

		template<typename T, std::enable_if_t<std::is_floating_point<T>::value, float> = 0 >
		static void MakeString(const T  data) {
			m_logData.m_msg += std::to_string(data);
		}

	private:
		static LogSystem& m_logSystem;
		static LogData m_logData;
	};

}



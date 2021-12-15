#pragma once
#include"Buffer.h"
#include"Session.h"
#include<queue>
#include<mutex>


namespace tray {
	namespace net{
	
		template<typename T>
		class TsQueue {
		public:
			TsQueue() {}
		public:
			void PushBack(const T&& buffer) {
				std::lock_guard<std::mutex> lock(m_mutex);
				m_queue.push(std::move(buffer));
			}

			void Front(T& buffer) {
				std::lock_guard<std::mutex> lock(m_mutex);
				buffer = std::move(m_queue.front());
				m_queue.pop();
			}

			T FrontData() {
				std::lock_guard<std::mutex> lock(m_mutex);
				auto data= std::move(m_queue.front());
				m_queue.pop();
				return data;
			}

			size_t Size()
			{
				return m_queue.size();
			}

			bool IsEmpty() {
				return m_queue.empty();
			}
		private:

			std::mutex m_mutex;
			std::queue<T> m_queue;
		};
		
		class Session;

		class BufferObject {
		public:
			std::shared_ptr<Session> remote = nullptr;
			Buffer buffer;
			BufferObject():buffer(){
			}
		};
	}
	
}
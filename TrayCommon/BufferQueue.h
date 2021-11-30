#pragma once
#include"Buffer.h"
#include"Session.h"
#include<queue>
#include<mutex>


namespace tray {
	namespace net{
		class BufferQueue {
		public:
			BufferQueue() {}

			void PushBack(const Buffer& buffer) {
				std::lock_guard<std::mutex> lock2(m_mutex);
				m_queue.push(buffer);
			}

			void Front(Buffer& buffer) {
				std::lock_guard<std::mutex> lock2(m_mutex);
				buffer = m_queue.front();
				m_queue.pop();
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
			std::queue<Buffer> m_queue;

		};


		template<typename T>
		class TsQueue {
		public:
			TsQueue() {}
		public:
			void PushBack(const T& buffer) {
				std::lock_guard<std::mutex> lock(m_mutex);
				m_queue.push(buffer);
			}

			void Front(T& buffer) {
				std::lock_guard<std::mutex> lock(m_mutex);
				buffer = m_queue.front();
				m_queue.pop();
			}

			T FrontData() {
				std::lock_guard<std::mutex> lock(m_mutex);
				auto data= m_queue.front();
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
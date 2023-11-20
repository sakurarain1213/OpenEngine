#pragma once

#include <ctime>
#include <string>
#include <chrono>

#define OE_DATE (OpenEngine::Time::GetDateAsString())

namespace OpenEngine {
	class Time{
	public:
		/*
		* Get the date as string (yyyy-mm-dd hh:mm:ss)
		*/
		static std::string GetDateAsString();
		static float GetDeltaTime();
		static void Initialize();
		static void Update();
	private:
		static std::chrono::steady_clock::time_point m_start_time;
		static std::chrono::steady_clock::time_point m_current_time;
		static std::chrono::steady_clock::time_point m_last_time;
		static std::chrono::duration<float> m_elapsed;
		static float m_deltaTime;
	};
}
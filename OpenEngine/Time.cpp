#pragma once

#include "Time.h"

namespace OpenEngine {

	std::string Time::GetDateAsString() {
		std::string date;
		time_t now = time(NULL);
		tm localTime;
		localtime_s(&localTime, &now);
		std::string dateDivide[6] = {
			std::to_string(1900 + localTime.tm_year),
			std::to_string(1 + localTime.tm_mon),
			std::to_string(localTime.tm_mday),
			std::to_string(localTime.tm_hour),
			std::to_string(localTime.tm_min),
			std::to_string(localTime.tm_sec)
		};
		for (int i = 0;i < 6;++i) {
			if (dateDivide[i].length() < 2)
				dateDivide[i].insert(dateDivide[i].begin(), '0');
			date += dateDivide[i];
			if (i < 2) date += '-';
			if (i > 2 && i < 5) date += ':';
		}
		return date;
	}

	float Time::GetDeltaTime() {
		return m_deltaTime;
	}

	void Time::Initialize() {
		m_start_time = std::chrono::steady_clock::now();
		m_last_time = m_start_time;
		m_current_time = m_start_time;
		m_deltaTime = 0.0f;
	}

	void Time::Update() {
		m_last_time = m_current_time;
		m_current_time = std::chrono::steady_clock::now();
		m_elapsed = m_current_time - m_last_time;
		m_deltaTime = m_elapsed.count();
	}

	std::chrono::steady_clock::time_point Time::m_start_time;
	std::chrono::steady_clock::time_point Time::m_current_time;
	std::chrono::steady_clock::time_point Time::m_last_time;
	std::chrono::duration<float> Time::m_elapsed;
	float Time::m_deltaTime;
}
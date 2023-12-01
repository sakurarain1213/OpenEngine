#pragma once

#include "Logger.h"
#include "Time.h"
#include "ConsoleHandler.h"

namespace OpenEngine::Debug {

	void Logger::SetLogMode(LogMode mode) {
		m_mode = mode;
	}

	void Logger::Log(LogType type, std::string message) {
		LogData data;
		data.logType = type;
		data.message = message;
		data.date = OE_DATE;
		m_handler[m_mode]->Log(data);
	}

	LogMode Logger::m_mode = LOG_CONSOLE;

	std::unique_ptr<ILogHandler> Logger::m_handler[2] = { std::make_unique<ConsoleHandler>(), std::make_unique<ConsoleHandler>() };
}
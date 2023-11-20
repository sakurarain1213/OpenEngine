#pragma once

#include "ILogHandler.h"
#include "memory"

#define OE_ERROR(msg) (OpenEngine::Debug::Logger::Log(OpenEngine::Debug::LOG_ERROR, msg))
#define OE_WARNING(msg) (OpenEngine::Debug::Logger::Log(OpenEngine::Debug::LOG_WARNING, msg))
#define OE_SUCCESS(msg) (OpenEngine::Debug::Logger::Log(OpenEngine::Debug::LOG_SUCCESS, msg))
#define OE_INFO(msg) (OpenEngine::Debug::Logger::Log(OpenEngine::Debug::LOG_INFO, msg))
#define OE_LOG(msg) (OpenEngine::Debug::Logger::Log(OpenEngine::Debug::LOG_DEFAULT, msg))


namespace OpenEngine::Debug {

	enum LogMode
	{
		LOG_CONSOLE,
		LOG_FILE
	};
	class Logger {
	public:
		static void SetLogMode(LogMode mode);
		static void Log(LogType type, std::string message);
	private:
		Logger() {}
	private:
		static LogMode m_mode;
		static std::unique_ptr<ILogHandler> m_handler[2];
	};
}
#pragma once

#include <string>

namespace OpenEngine::Debug {

	enum LogType
	{
		LOG_ERROR,
		LOG_WARNING,
		LOG_SUCCESS,
		LOG_INFO,
		LOG_DEFAULT
	};

	const std::string error_header = "[ERROR] ";
	const std::string warning_header = "[WARNING] ";
	const std::string success_header = "[SUCCESS] ";
	const std::string info_header = "[INFO] ";
	const std::string default_header = "";

	struct LogData {
		LogType logType;
		std::string date;
		std::string message;
		std::string ToString() const {
			switch (logType)
			{
			case OpenEngine::Debug::LOG_ERROR:
				return error_header + "[" + date + "]: " + message;
				break;
			case OpenEngine::Debug::LOG_WARNING:
				return warning_header + "[" + date + "]: " + message;
				break;
			case OpenEngine::Debug::LOG_SUCCESS:
				return success_header + "[" + date + "]: " + message;
				break;
			case OpenEngine::Debug::LOG_INFO:
				return info_header + "[" + date + "]: " + message;
				break;
			case OpenEngine::Debug::LOG_DEFAULT:
				return default_header + "[" + date + "]: " + message;
				break;
			default:
				return "";
				break;
			}
		}
	};

	class ILogHandler {
		friend class Logger;
	private:
		virtual void Log(const LogData& log) = 0;
	};
}
#pragma once

#include "ILogHandler.h"
#include <windows.h>
#include <iostream>

namespace OpenEngine::Debug {
	class ConsoleHandler : public ILogHandler{
	private:
		void Log(const LogData& log) {
			switch (log.logType)
			{
			case OpenEngine::Debug::LOG_ERROR:
				std::cout << &red;
				break;
			case OpenEngine::Debug::LOG_WARNING:
				std::cout << &yellow;
				break;
			case OpenEngine::Debug::LOG_SUCCESS:
				std::cout << &green;
				break;
			case OpenEngine::Debug::LOG_INFO:
				std::cout << &grey;
				break;
			case OpenEngine::Debug::LOG_DEFAULT:
				std::cout << &white;
				break;
			default:
				break;
			}
			std::cout << log.ToString() << std::endl;
		}

		static inline std::ostream& blue(std::ostream& s)
		{
			HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hStdout,
				FOREGROUND_BLUE | FOREGROUND_GREEN |
				FOREGROUND_INTENSITY);
			return s;
		}

		static inline std::ostream& red(std::ostream& s)
		{
			HANDLE hStdout = GetStdHandle(STD_ERROR_HANDLE);
			SetConsoleTextAttribute(hStdout,
				FOREGROUND_RED | FOREGROUND_INTENSITY);
			return s;
		}

		static inline std::ostream& green(std::ostream& s)
		{
			HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hStdout,
				FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			return s;
		}

		static inline std::ostream& yellow(std::ostream& s)
		{
			HANDLE hStdout = GetStdHandle(STD_ERROR_HANDLE);
			SetConsoleTextAttribute(hStdout,
				FOREGROUND_GREEN | FOREGROUND_RED |
				FOREGROUND_INTENSITY);
			return s;
		}

		static inline std::ostream& white(std::ostream& s)
		{
			HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hStdout,
				FOREGROUND_RED | FOREGROUND_GREEN |
				FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			return s;
		}

		static inline std::ostream& grey(std::ostream& s)
		{
			HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hStdout,
				FOREGROUND_RED | FOREGROUND_GREEN |
				FOREGROUND_BLUE);
			return s;
		}
	};
}
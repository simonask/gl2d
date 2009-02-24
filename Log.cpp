#include "Log.h"

#include <iostream>

namespace Log
{
	static Level::LogLevel level = Level::DEBUG;
	
	std::string format(const char *fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		char* cstr;
		vasprintf(&cstr, fmt, args);
		va_end(args);
		return std::string(cstr);
	}
	
	void log(const char* message, Level::LogLevel severity)
	{
		if (severity <= level)
		{
			std::cerr << message << std::endl;
		}
	}
	
	void setLevel(Level::LogLevel _level) { level = _level; }
}

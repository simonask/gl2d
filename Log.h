#ifndef _LOG_H_
#define _LOG_H_

#include <string>

namespace Log {
	namespace Level {
		enum LogLevel {
			DEBUG,
			INFO,
			WARNING,
			ERROR
		};
	}
	
	std::string format(const char* fmt, ...);
	void log(const char* message, Level::LogLevel level = Level::DEBUG);
	void setLevel(Level::LogLevel);
}

#endif /* _LOG_H_ */

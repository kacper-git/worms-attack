#ifndef __LOG_LEVEL_H
#define __LOG_LEVEL_H

namespace LogLevel {

	typedef enum _LOG_LEVEL {
		TYPE_ERROR			= 0x01,						
		TYPE_WARNING		= 0x03,
		TYPE_INFO			= 0x07,
		TYPE_DEBUG			= 0x0F,
	} LOG_LEVEL;

	#define LOG_LEVEL_NAME_ERROR		"error"
	#define LOG_LEVEL_NAME_WARNING		"warning"
	#define LOG_LEVEL_NAME_INFO			"info"
	#define LOG_LEVEL_NAME_DEBUG		"debug"

};

#endif // __LOG_LEVEL_H


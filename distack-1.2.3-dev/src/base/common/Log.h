#ifndef __LOG_H
#define __LOG_H

#include <iostream>
#include <string>
#include <map>
#include <iomanip> 
#include <cassert>
#include <ostream>
#include <sstream>
#include <list>
#include <algorithm>
#include <boost/thread/mutex.hpp>
#include "base/common/DistackInfo.h"
#include "base/common/Helper.h"
#include "base/common/LogLevel.h"
#include "base/common/LogOutputter.h"

#define logging_error(x)  Log::error(distackInfo,x)
#define logging_warn(x)   Log::warning(distackInfo,x)
#define logging_info(x)   Log::info(distackInfo,x)
#define logging_debug(x)  Log::debug(distackInfo,x)

using std::find;
using std::list;
using std::setfill;
using std::setw;
using std::cout;
using std::string;
using std::map;
using std::ostream;
using std::ostringstream;

class Outputter;

class Log {
public:
	Log();
	~Log();

	static void init( DistackInfo* info );
	static void reference( Log* factory );
	static Log* instance( DistackInfo* info );
	static void cleanup( DistackInfo* info );

	static void debug( DistackInfo* info, string dbg );
	static void info( DistackInfo* info, string inf );
	static void warning( DistackInfo* info, string warn );
	static void error( DistackInfo* info, string err );

	void setLogLevel( LogLevel::LOG_LEVEL level );
	LogLevel::LOG_LEVEL getLogLevel();
	void addLogOutput( LogOutputter* outputter );
	void removeLogOutput( LogOutputter* outputter );

private:
	static map<int, Log*> instances;
	static bool deleteobject;

	typedef list<LogOutputter*> OUTPUTTER_LIST;
	typedef OUTPUTTER_LIST::iterator OUTPUTTER_LIST_ITERATOR;
	OUTPUTTER_LIST m_outputters;

	LogLevel::LOG_LEVEL m_logLevel;
	boost::mutex m_outputmutex;
	
	void output( string str, LogLevel::LOG_LEVEL type );
};

#endif // __LOG_H

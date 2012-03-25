#include "Log.h"

#include "base/configuration/Configuration.h"

map<int, Log*> Log::instances;
bool Log::deleteobject = true;

void Log::init (DistackInfo* info)
{
	if(instances.find(info->distackId) == instances.end()) {
		Log* object = new Log();
		instances[info->distackId] = object;
	}
}
	
Log* Log::instance (DistackInfo* info)
{
	Log *object = instances[info->distackId];
	return object;
}

void Log::cleanup (DistackInfo* info)
{
	Log* object = instances[info->distackId];
	if( deleteobject ) delete object;
}

Log::Log() 
{
}

Log::~Log()
{
}

void Log::reference(Log* factory)
{
#ifdef WIN32
	object = factory;
	deleteobject = false;
#endif
}

void Log::error(DistackInfo* info, string err)
{
	Log::instance(info)->output (err, LogLevel::TYPE_ERROR);
}

void Log::warning(DistackInfo* info, string warn)
{
	Log::instance(info)->output (warn, LogLevel::TYPE_WARNING);
}

void Log::info(DistackInfo* info, string inf)
{
	Log::instance(info)->output (inf, LogLevel::TYPE_INFO);
}

void Log::debug(DistackInfo* info, string dbg)
{
	Log::instance(info)->output (dbg, LogLevel::TYPE_DEBUG);
}

void Log::output(string str, LogLevel::LOG_LEVEL type)
{
	boost::mutex::scoped_lock scopedLock (m_outputmutex);

	// no output active?
	if (m_outputters.size () <= 0)
		return;

	// check if output is desired with the current log level
	if ((m_logLevel & type) != type) 
		return;

	LogOutputter::OUTPUT_OBJ outobj;

	// get the current date-time
	outobj.date	= Helper::getDate ();
	outobj.time	= Helper::getTime ();

	outobj.type	= type;
	outobj.text	= Helper::trim (str);

	OUTPUTTER_LIST::iterator begin	= m_outputters.begin	();
	OUTPUTTER_LIST::iterator end	= m_outputters.end		();

	//
	// finally output the item in the registered LogOutputter's
	//

	for ( ; begin != end; begin++)
		(*begin)->output (&outobj);
}

void Log::setLogLevel(LogLevel::LOG_LEVEL level)
{
	m_logLevel = level;
}

LogLevel::LOG_LEVEL Log::getLogLevel ()
{
	return m_logLevel;
}

void Log::addLogOutput (LogOutputter* out)
{
	boost::mutex::scoped_lock scopedLock (m_outputmutex);
	m_outputters.push_back (out);
}

void Log::removeLogOutput (LogOutputter* outputter)
{
	boost::mutex::scoped_lock scopedLock (m_outputmutex);
	
	
	OUTPUTTER_LIST_ITERATOR item = find (m_outputters.begin(), m_outputters.end(), outputter);
	if (item != m_outputters.end())
		m_outputters.erase (item);
}

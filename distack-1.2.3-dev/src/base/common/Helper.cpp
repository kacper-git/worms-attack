#include "Helper.h"

string Helper::ultos(unsigned long val)
{
	char buf[16];

#ifdef WIN32
	_ultoa_s (val, buf, 16, 10);
#else
	sprintf (buf, "%lu", val);
#endif

	return buf;
}

string Helper::ltos(long val)
{
	char buf[16];

#ifdef WIN32
	_ltoa_s (val, buf, 16, 10);
#else
	sprintf (buf, "%li", val);
#endif

	return buf;
}

string	Helper::ultohexs (unsigned long val, bool hexdelimiter)
{
	char buf[16];

#ifdef WIN32
	_ultoa_s (val, buf, 16, 16);
#else
	sprintf (buf, "%lx", val);
#endif

	string ret = buf;

	if (hexdelimiter)
		ret.insert (0, "0x");

	return ret;
}

string Helper::ltohexs (long val, bool hexdelimiter)
{
	char buf[16];

#ifdef WIN32
	_ltoa_s (val, buf, 16, 16);
#else
	sprintf (buf, "%lx", val);
#endif

	string ret = buf;

	if (hexdelimiter)
		ret.insert (0, "0x");

	return ret;
}

string Helper::trim (string str)
{
	string ret = str;

	ret.erase (0, ret.find_first_not_of( " \n\r\t" ));
	ret.erase (ret.find_last_not_of( " \n\r\t") + 1 );

	return ret;
}

long Helper::stol (string str)
{
	return strtol (str.c_str (), NULL, 10);
}

int	Helper::stoi (string str)
{
	return (int) stol (str);
}

unsigned int Helper::hstoui (string str)
{
	return (unsigned int) strtol (str.c_str (), NULL, 16);
}

Helper::STRING_LIST	Helper::split (string str, string delimiter)
{
	STRING_LIST			ret;
	string::size_type	offset		= 0;
	string::size_type	delimIndex	= 0;
	string				helpstring	= "";

	if (str.length () <= 0) return ret;

    while ((delimIndex = str.find (delimiter, offset)) != string::npos) {

		helpstring = trim (str.substr (offset, delimIndex - offset));
		if (helpstring.length () > 0) ret.push_back	(helpstring);

		offset			= delimIndex + delimiter.length();
        delimIndex		= str.find (delimiter, offset);

    } // while ((delimIndex = str.find (delimiter, offset)) != string::npos)

	if (offset < str.length ()) {
		helpstring = trim (str.substr (offset));
		if (helpstring.length () > 0) ret.push_back (helpstring);
	}

	return ret;
}

string Helper::replace (string str, string find, string repl)
{
	string ret = str;
	boost::algorithm::replace_all (ret, find, repl);
	return ret;
}

string Helper::getTime (time_t timeval)
{
	time_t		rawtime;
	struct tm*	timeinfo;

	if (timeval == 0)
		time (&rawtime);
	else
		rawtime = timeval;

#ifdef WIN32
	timeinfo = new struct tm ();
	localtime_s (timeinfo, &rawtime);
#else
	timeinfo = localtime (&rawtime);
#endif

	ostringstream				m_formatter;

	m_formatter.str			("");
	m_formatter				<< setw(2) << setfill('0') << timeinfo->tm_hour			<< ":"
							<< setw(2) << setfill('0') << timeinfo->tm_min			<< ":"
							<< setw(2) << setfill('0') << timeinfo->tm_sec			;
	assert					(m_formatter.good ());

#ifdef WIN32
	delete timeinfo;
#endif
	return m_formatter.str ();
}

string Helper::getDate (time_t timeval)
{
	time_t		rawtime;
	struct tm*	timeinfo;

	if (timeval == 0)
		time (&rawtime);
	else
		rawtime = timeval;

#ifdef WIN32
	timeinfo = new struct tm ();
	localtime_s (timeinfo, &rawtime);
#else
	timeinfo = localtime (&rawtime);
#endif

	//
	// cache the date because it changes with very low frequency
	// and formatting using ostringstream or sprintf is more expensive
	//

	static struct tm datecache = {0};
	static string datecachestr = "";

	if (datecachestr.length() != 0 && (	datecache.tm_mday == timeinfo->tm_mday &&
										datecache.tm_mon  == timeinfo->tm_mon  &&
										datecache.tm_year == timeinfo->tm_year )) {
		#ifdef WIN32
			delete timeinfo;
		#endif
		return datecachestr;
	}

	//
	// format the date for international use
	//

	char buffer [32];

	setlocale (LC_ALL, "");
	strftime (buffer, sizeof (buffer), "%x", timeinfo);

	datecachestr = buffer;
	datecache	 = *timeinfo;

#ifdef WIN32
	delete timeinfo;
#endif

	return datecachestr;
}

unsigned long Helper::getElapsedMillis ()
{
	struct timeb tp;
	ftime( &tp );
	return ( tp.time*1000 + tp.millitm );
}

string Helper::dtos	(double	val)
{
	string ret = boost::lexical_cast<string> (val);
	return ret;
}

double Helper::stod (string str)
{
	if (str.length() <= 0)	return 0.0;
	else					return boost::lexical_cast<double> (str);
}

#ifndef __HELPER_H
#define __HELPER_H

#include <string>
#include <list>
#include <cassert>
#include <ctime>
#include <ostream>
#include <iomanip>
#include <cassert>
#include <ostream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#else
	#include <unistd.h>
	#include <stdlib.h>
#endif

using std::list;
using std::string;
using std::setfill;
using std::setw;
using std::cout;
using std::string;
using std::ostream;
using std::ostringstream;

namespace Helper {

	//
	// string conversion functions
	//

	/// unsigned long to string
	string						ultos				(unsigned long		val);

	/// pointer to string-address
	template <class T>
	string						ptos				(T					pnt)
	{
		std::ostringstream oss;
		oss << "0x" << std::hex << pnt;
		return oss.str ();
	}

	/// long to string
	string						ltos				(long				val);

	/// unsigned long to hex string
	string						ultohexs			(unsigned long		val, bool hexdelimiter = true);

	/// long to hex string
	string						ltohexs				(long				val, bool hexdelimiter = true);

	/// string to long
	long						stol				(string				str);

	/// string to int
	int							stoi				(string				str);

	/// string to double
	double						stod				(string				str);

	/// hex string to unsigned int
	unsigned int				hstoui				(string				str);

	/// double to string
	string						dtos				(double				val);

	//
	// string manipulation functions
	//

	/// trim string
	string						trim				(string				str);

	/// split a string into substrings. The single strings trimmed from whitespace
	/// only strings that have a resulting length > 0 after the trim are in the list
	typedef list<string>			STRING_LIST;
	typedef STRING_LIST::iterator	STRING_LIST_ITERATOR;
	STRING_LIST						split			(string				str, string delimiter);

	/// replace all occurences of find in the string str with repl
	string						replace				(string				str, string find, string repl);

	//
	// time functions
	//

	string						getTime				(time_t timeval = 0);
	string						getDate				(time_t timeval = 0);
	unsigned long				getElapsedMillis	();
	void						sleep				(unsigned int millis);

	//
	// constants
	//

#ifdef WIN32
	const string				LINE_BREAK = "\r\n";
#else
	const string				LINE_BREAK = "\n";
#endif

};

inline void Helper::sleep (unsigned int millis)
{
#ifdef WIN32
	Sleep (millis);
#else

	unsigned long secondsSleep = millis / 1000;
	unsigned long millisSleep  = millis % 1000;

	//
	// sleep the seconds part of the time
	// (usleep can not sleep more than 999999 microseconds
	//  which is a little bit too less for a second)
	//

	if (secondsSleep > 0)
		sleep (secondsSleep);

	//
	// sleep the microsecond part of the time
	//

	if (millisSleep > 0) {
		assert (millisSleep < 1000);
		usleep (millisSleep * 1000);
	}
#endif
}

#endif // __HELPER_H

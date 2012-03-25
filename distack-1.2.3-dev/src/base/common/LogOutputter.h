#ifndef __LOG_OUTPUTTER_H
#define __LOG_OUTPUTTER_H

#include "base/common/LogLevel.h"
#include <string>

using std::string;

/** @class LogOutputter
  * base class for all log outputters, functions for these are only called by a Log instance
  */
class LogOutputter {
public:

	typedef struct _OUTPUT_OBJ {
		string					date;			// output date
		string					time;			// output time
		LogLevel::LOG_LEVEL		type;			// type of the output
		string					text;			// main text of the output
	} OUTPUT_OBJ, *POUTPUT_OBJ;

	virtual void				output			(OUTPUT_OBJ* outobj) = 0;
};

#endif // __LOG_OUTPUTTER_H

#ifndef __STDOUT_LOG_OUTPUTTER_H
#define __STDOUT_LOG_OUTPUTTER_H

#include "base/common/LogOutputter.h"
#include <fstream>
#include <cassert>
#include <iostream>

using std::cout;

/** @class StdOutLogOutputter
  * a specific outputter, that writes all incoming data to stdout
  */
class StdOutLogOutputter : public LogOutputter
{
public:
						StdOutLogOutputter		();
						~StdOutLogOutputter		();

	void				output					(OUTPUT_OBJ* outobj);

};

#endif // __STDOUT_LOG_OUTPUTTER_H


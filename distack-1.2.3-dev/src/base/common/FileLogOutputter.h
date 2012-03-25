#ifndef __FILE_LOG_OUTPUTTER_H
#define __FILE_LOG_OUTPUTTER_H

#include "base/common/LogOutputter.h"
#include <fstream>
#include <cassert>

using std::ofstream;
using std::ios_base;

/** @class FileLogOutputter
  * a specific outputter, that writes all incoming data to a file specified on construction
  */
class FileLogOutputter : public LogOutputter
{
public:
						FileLogOutputter		(string fname);
						~FileLogOutputter		();

	void				output					(OUTPUT_OBJ* outobj);
	string				getFilename				();	

private:

	ofstream			outstream;
	string				filename;

};

#endif // __FILE_LOG_OUTPUTTER_H


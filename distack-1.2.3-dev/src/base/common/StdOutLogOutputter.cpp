#include "StdOutLogOutputter.h"

StdOutLogOutputter::StdOutLogOutputter ()
{
}

StdOutLogOutputter::~StdOutLogOutputter ()
{
}

void StdOutLogOutputter::output (OUTPUT_OBJ* outobj)
{
	static const string del = " - ";
	if (outobj == NULL) return;

	switch (outobj->type) {
		case LogLevel::TYPE_DEBUG:		cout << "debug";	break;
		case LogLevel::TYPE_INFO:		cout << "info";		break;
		case LogLevel::TYPE_WARNING:	cout << "warning";	break;
		case LogLevel::TYPE_ERROR:		// fall through
		default:						cout << "error";	break;
	};

	cout	<< del
			<< outobj->date.c_str () << del
			<< outobj->time.c_str () << del
			<< outobj->text.c_str () << "\n";						
}

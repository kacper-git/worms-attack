#include "FileLogOutputter.h"

FileLogOutputter::FileLogOutputter (string fname)
: filename	(fname)
{
	outstream.open	(fname.c_str (), ios_base::out | ios_base::trunc ),
	assert			(outstream.is_open ());
}

FileLogOutputter::~FileLogOutputter ()
{
	outstream.close ();
}

void FileLogOutputter::output (OUTPUT_OBJ* outobj)
{
	const string del = " - ";
	if (outobj == NULL) return;

	switch (outobj->type) {
		case LogLevel::TYPE_DEBUG:		outstream << "debug";	break;
		case LogLevel::TYPE_INFO:		outstream << "info";	break;
		case LogLevel::TYPE_WARNING:	outstream << "warning";	break;
		case LogLevel::TYPE_ERROR:		// fall through
		default:						outstream << "error";	break;
	};

	outstream	<< del
				<< outobj->date.c_str () << del
				<< outobj->time.c_str () << del
				<< outobj->text.c_str () << "\n";						

	outstream.flush ();
}

string FileLogOutputter::getFilename ()
{
	return filename;
}


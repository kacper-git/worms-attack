#include "ModuleOutputterPlotter.h"

#ifdef OMNET_SIMULATION
	#include "Distack.h"
#endif

MODULE_INTERFACE(ModuleOutputterPlotter)

const string ModuleOutputterPlotter::PARAM_OutFilename = "OutFilename";

ModuleOutputterPlotter::ModuleOutputterPlotter ()
{
	m_bytes = 0;
	m_timestamp = 0;
}

ModuleOutputterPlotter::~ModuleOutputterPlotter ()
{
	if (m_outputfile.is_open ())
		m_outputfile.close ();

	if (m_gnuPlot != NULL) {
#ifdef WIN32	
		_pclose (m_gnuPlot);
#else
		pclose (m_gnuPlot);
#endif
	}
}

void ModuleOutputterPlotter::registerMessages ()
{
}

bool ModuleOutputterPlotter::configure (ModuleConfiguration& configList)
{
	bool good = true;

	good &= configList.has (PARAM_OutFilename);

	if (good) {
		m_param_OutFilename = configList.get (PARAM_OutFilename);
		m_outputfile.open (m_param_OutFilename.c_str());
		good &= m_outputfile.is_open ();
	}

	//
	// put some initial values into the plotfile so
	// gnuplot has something to show
	//

	m_outputfile 	<< Helper::ultos(0) 	<< "\t"
			<< Helper::ultos(0) 	<< "\n";
	m_outputfile.flush();

	//
	// start gnuplot
	//

#ifdef WIN32
	// under Windows there are wgnuplot (gui version)
	// and pgnuplot (pipe version), here we use pgnuplot
	m_gnuPlot = _popen ("pgnuplot", "w"); 
#else
	m_gnuPlot = popen ("gnuplot", "w");
#endif

	if (m_gnuPlot == NULL) return false;
	Helper::sleep (1000); // wait to let the gnuplot start up

	ostringstream cmdStream;

	cmdStream.str ("");
#ifdef WIN32
	cmdStream << "set term windows";
#else
	cmdStream << "set term x11";
#endif
	gnuPlotCommand (cmdStream.str());

	cmdStream.str ("");
	cmdStream << "set title\"" << "Distack ModuleOutputterPlotter" << "\"";
	gnuPlotCommand (cmdStream.str());

	string normalizedOutFilename = m_param_OutFilename;

#ifdef WIN32
	normalizedOutFilename = Helper::replace (normalizedOutFilename, "\\", "\\\\");
#endif

	cmdStream.str ("");
	cmdStream	<< "plot "
			<< "\"" + normalizedOutFilename + "\" using 1:2 title \"packets per second\" with linespoints";

	m_plotCommand = cmdStream.str ();
	gnuPlotCommand (m_plotCommand);

	//
	// start the timer
	//

	Timer::setInterval (1000);
	Timer::start ();

	return good;
}

bool ModuleOutputterPlotter::frameCall (Frame& frame)
{	
	boost::mutex::scoped_lock lock (m_bytesMutex);
	m_bytes += 1;//frame.getSize ();
	
	return true;
}

void ModuleOutputterPlotter::eventFunction ()
{	
	m_timestamp++;
	
	{
		boost::mutex::scoped_lock lock (m_bytesMutex);
		m_outputfile 	<< Helper::ultos(m_timestamp) 	<< "\t"
				<< Helper::ultos(m_bytes) 	<< "\n";
		m_outputfile.flush();
		m_bytes = 0;
	}

	gnuPlotCommand (m_plotCommand);
}

void ModuleOutputterPlotter::receiveMessage (Message* msg)
{
}

void ModuleOutputterPlotter::gnuPlotCommand (const string& cmd)
{
	ostringstream cmdStream;
	cmdStream << cmd << std::endl;

	fprintf (m_gnuPlot, "%s", cmdStream.str().c_str());
	fflush  (m_gnuPlot);
}

#ifndef __MODULE_OUTPUTTER_PLOTTER_H
#define __MODULE_OUTPUTTER_PLOTTER_H

#include "base/module/DistackModuleInterface.h"
#include "base/common/Helper.h"
#include <boost/thread/mutex.hpp>
#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>

using std::cout;
using std::ofstream;
using std::ostringstream;

class ModuleOutputterPlotter : public DistackModuleInterface {
public: 
						ModuleOutputterPlotter		();
						~ModuleOutputterPlotter	();

	bool					frameCall			(Frame& frame);
	bool					configure			(ModuleConfiguration& configList);
	void					receiveMessage			(Message* msg);
	void					registerMessages		();
	void					eventFunction			();

private:

	void					gnuPlotCommand			(const string& cmd);

	static const string			PARAM_OutFilename;
	string					m_param_OutFilename;

	FILE*					m_gnuPlot;
	ofstream				m_outputfile;
	string					m_plotCommand;

	boost::mutex				m_bytesMutex;
	unsigned long				m_bytes;

	unsigned int				m_timestamp;

};

#endif // __MODULE_OUTPUTTER_PLOTTER_H

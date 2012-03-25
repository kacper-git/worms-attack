#ifndef __MODULE_SAMPLING_SYSTEMATIC_TIME_BASED_H
#define __MODULE_SAMPLING_SYSTEMATIC_TIME_BASED_H

#include "base/module/DistackModuleInterface.h"
#include <vector>
#include <ctime>

#ifdef WIN32
	#include <windows.h>
#else
	#include <sys/times.h>
#endif

using std::vector;

class ModuleSamplingSystematicTimeBased : public DistackModuleInterface {
public: 
									ModuleSamplingSystematicTimeBased		();
									~ModuleSamplingSystematicTimeBased		();

	bool							configure					(ModuleConfiguration& configList);
	bool							frameCall					(Frame& frame);

private:

	unsigned long					getCurrentMillis			();

	unsigned long					m_param_SelectionDuration;
	unsigned long					m_param_SamplingDuration;

	unsigned long					m_intervalStart;

	static const string				PARAM_SelectionDuration;
	static const string				PARAM_SamplingDuration;
	
};

#endif // __MODULE_SAMPLING_SYSTEMATIC_TIME_BASED_H

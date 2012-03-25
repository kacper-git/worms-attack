#ifndef __MODULE_SAMPLING_SYSTEMATIC_COUNT_BASED_H
#define __MODULE_SAMPLING_SYSTEMATIC_COUNT_BASED_H

#include "base/module/DistackModuleInterface.h"
#include <vector>

using std::vector;

class ModuleSamplingSystematicCountBased : public DistackModuleInterface {
public: 
									ModuleSamplingSystematicCountBased		();
									~ModuleSamplingSystematicCountBased		();

	bool							configure					(ModuleConfiguration& configList);
	bool							frameCall					(Frame& frame);

private:
	
	unsigned long					m_param_SamplingCount;
	unsigned long					m_param_SelectionCount;

	unsigned long					m_current_FrameCount;

	static const string				PARAM_SamplingCount;
	static const string				PARAM_SelectionCount;

};

#endif // __MODULE_SAMPLING_SYSTEMATIC_COUNT_BASED_H

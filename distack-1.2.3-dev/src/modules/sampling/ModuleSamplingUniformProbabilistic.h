#ifndef __MODULE_SAMPLING_UNIFORM_PROBABILISTIC_H
#define __MODULE_SAMPLING_UNIFORM_PROBABILISTIC_H

#include "base/module/DistackModuleInterface.h"
#include <boost/random.hpp>
#include <vector>

using std::vector;

class ModuleSamplingUniformProbabilistic : public DistackModuleInterface {
public: 
									ModuleSamplingUniformProbabilistic		();
									~ModuleSamplingUniformProbabilistic		();

	bool							configure					(ModuleConfiguration& configList);
	bool							frameCall					(Frame& frame);

private:

	double							m_param_Probability;

	static const string				PARAM_Probability;

	boost::mt19937 							m_randomGenerator;
	boost::uniform_01<boost::mt19937>		m_uniform;
};

#endif // __MODULE_SAMPLING_UNIFORM_PROBABILISTIC_H

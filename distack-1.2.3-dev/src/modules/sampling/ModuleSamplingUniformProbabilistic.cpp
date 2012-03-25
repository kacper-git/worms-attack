#include "ModuleSamplingUniformProbabilistic.h"

MODULE_INTERFACE(ModuleSamplingUniformProbabilistic);

const string ModuleSamplingUniformProbabilistic::PARAM_Probability = "Probability";

ModuleSamplingUniformProbabilistic::ModuleSamplingUniformProbabilistic ()
:	m_uniform (m_randomGenerator)
{
}

ModuleSamplingUniformProbabilistic::~ModuleSamplingUniformProbabilistic ()
{
}

bool ModuleSamplingUniformProbabilistic::configure (ModuleConfiguration& configList)
{
	bool good = true;

	good &= configList.has (PARAM_Probability);	

	if (good) {
		m_param_Probability = ((double) configList.getLong (PARAM_Probability)) / 100.0;
	}

	return good;
}

bool ModuleSamplingUniformProbabilistic::frameCall(Frame& frame)
{
	double rand = m_uniform();
	return (rand < m_param_Probability);
}

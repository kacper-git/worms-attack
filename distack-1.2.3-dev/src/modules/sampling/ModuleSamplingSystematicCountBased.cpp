#include "ModuleSamplingSystematicCountBased.h"

MODULE_INTERFACE(ModuleSamplingSystematicCountBased);

const string ModuleSamplingSystematicCountBased::PARAM_SamplingCount  = "SamplingCount";
const string ModuleSamplingSystematicCountBased::PARAM_SelectionCount = "SelectionCount";

ModuleSamplingSystematicCountBased::ModuleSamplingSystematicCountBased ()
:	m_current_FrameCount		(0),
	m_param_SamplingCount		(0),
	m_param_SelectionCount		(0)
{
}

ModuleSamplingSystematicCountBased::~ModuleSamplingSystematicCountBased ()
{
}

bool ModuleSamplingSystematicCountBased::configure (ModuleConfiguration& configList)
{
	bool good = true;

	good &= configList.has (PARAM_SamplingCount);	
	good &= configList.has (PARAM_SelectionCount);

	if (good) {
		m_param_SamplingCount  = configList.getLong (PARAM_SamplingCount );
		m_param_SelectionCount = configList.getLong (PARAM_SelectionCount);

		good &= (m_param_SamplingCount >= m_param_SelectionCount);
	}

	return good;
}

bool ModuleSamplingSystematicCountBased::frameCall(Frame& frame)
{
	if (m_current_FrameCount < m_param_SelectionCount) {
		return true;
	}

	if (m_current_FrameCount+1 < m_param_SamplingCount) {
		m_current_FrameCount++;
	} else {
		m_current_FrameCount  = 0;
	}

	return false;
}

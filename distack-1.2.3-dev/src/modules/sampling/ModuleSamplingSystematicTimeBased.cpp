#include "ModuleSamplingSystematicTimeBased.h"

MODULE_INTERFACE(ModuleSamplingSystematicTimeBased);

const string ModuleSamplingSystematicTimeBased::PARAM_SelectionDuration = "SelectionDuration";
const string ModuleSamplingSystematicTimeBased::PARAM_SamplingDuration  = "SamplingDuration";

ModuleSamplingSystematicTimeBased::ModuleSamplingSystematicTimeBased ()
:	m_param_SelectionDuration	(0),
	m_param_SamplingDuration	(0),
	m_intervalStart				(0)
{
}

ModuleSamplingSystematicTimeBased::~ModuleSamplingSystematicTimeBased ()
{
}

bool ModuleSamplingSystematicTimeBased::configure (ModuleConfiguration& configList)
{
	bool good = true;

	good &= configList.has (PARAM_SelectionDuration);	
	good &= configList.has (PARAM_SamplingDuration);

	if (good) {
		m_param_SelectionDuration = configList.getLong (PARAM_SelectionDuration);
		m_param_SamplingDuration  = configList.getLong (PARAM_SamplingDuration );

		m_intervalStart = getCurrentMillis ();

		good &= (m_param_SamplingDuration >= m_param_SelectionDuration);
	}

	return good;
}

bool ModuleSamplingSystematicTimeBased::frameCall(Frame& frame)
{
	// what is the now-time? (could use the timestamp from the frame but this is not always monotonically increasing http://www.tcpdump.org/lists/workers/2005/05/msg00052.html)
	unsigned long now		= getCurrentMillis ();
	// how much time has elapsed since the start of the first interval? (can be several intervals)
	unsigned long nowDiff	= now - m_intervalStart;
	// where are we now in the current interval? (offset in the current sampling interval)
	unsigned long offset	= (nowDiff > m_param_SamplingDuration ? nowDiff % m_param_SamplingDuration : nowDiff);

	assert (offset <= m_param_SamplingDuration);

	//
	// if the current offset is smaller than the selection interval we select
	//

	return (offset <= m_param_SelectionDuration);
}

unsigned long ModuleSamplingSystematicTimeBased::getCurrentMillis ()
{
#ifdef WIN32
	return GetTickCount ();
#else
	struct tms tm;
    return times(&tm);
#endif
}

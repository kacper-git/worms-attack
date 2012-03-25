#ifndef __MODULE_UTILITY_TIMER_H
#define __MODULE_UTILITY_TIMER_H

#include "base/common/Timer.h"
#include "base/module/DistackModuleInterface.h"
#include "messages/utility/MessageTimer.h"

class ModuleUtilityTimer : public DistackModuleInterface {
public:
					ModuleUtilityTimer		();
					 ~ModuleUtilityTimer		();

	bool				configure			(ModuleConfiguration& configList);

	void				eventFunction			();
	void				registerMessages		();

private:

	static const string		PARAM_Interval;
	unsigned int			m_param_Interval;

	string				m_timerName;
	unsigned long			m_eventNo;

};

#endif // __MODULE_UTILITY_TIMER_H

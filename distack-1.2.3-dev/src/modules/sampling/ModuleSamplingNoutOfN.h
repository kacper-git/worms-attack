#ifndef __MODULE_SAMPLING_N_OUT_OF_N_H
#define __MODULE_SAMPLING_N_OUT_OF_N_H 

#include "base/module/DistackModuleInterface.h"
#include <boost/random.hpp>
#include <boost/dynamic_bitset.hpp>
#include <vector>

using std::vector;

class ModuleSamplingNoutOfN : public DistackModuleInterface {
public: 
									ModuleSamplingNoutOfN		();
									~ModuleSamplingNoutOfN		();

	bool							configure					(ModuleConfiguration& configList);
	bool							frameCall					(Frame& frame);

private:

	unsigned long					m_param_n;
	unsigned long					m_param_N;

	static const string				PARAM_n;
	static const string				PARAM_N;

	unsigned long					m_availableRands;
	unsigned long					m_assertionCounter;
	typedef boost::dynamic_bitset<>	SELECTION_VECTOR;
	SELECTION_VECTOR				m_selectionVector;

	boost::uniform_int<>*			m_uniform;
	boost::mt19937					m_randomGenerator;
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> >*		m_variateGenerator;
	
};

#endif // __MODULE_SAMPLING_N_OUT_OF_N_H

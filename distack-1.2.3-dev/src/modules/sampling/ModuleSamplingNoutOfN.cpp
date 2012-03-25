#include "ModuleSamplingNoutOfN.h"

MODULE_INTERFACE(ModuleSamplingNoutOfN);

const string ModuleSamplingNoutOfN::PARAM_n = "n";
const string ModuleSamplingNoutOfN::PARAM_N = "N";

ModuleSamplingNoutOfN::ModuleSamplingNoutOfN ()
:	m_param_n			(0),
	m_param_N			(0),
	m_availableRands	(0),
	m_assertionCounter	(0),
	m_uniform			(NULL),
	m_variateGenerator	(NULL)
{
}

ModuleSamplingNoutOfN::~ModuleSamplingNoutOfN ()
{
	delete m_variateGenerator;
	delete m_uniform;
}

bool ModuleSamplingNoutOfN::configure (ModuleConfiguration& configList)
{
	bool good = true;

	good &= configList.has (PARAM_n);	
	good &= configList.has (PARAM_N);

	if (good) {
		m_param_n = configList.getLong (PARAM_n);
		m_param_N = configList.getLong (PARAM_N);
	
		//
		// use the Mersenne twister (boost::mt19937) to generate
		// random numbers. boost::uniform_int defines the range for
		// the numbers and the boost::variate_generator is the final
		// generator which will be called using the ()-operator
		//

		m_uniform			= new boost::uniform_int<> (0, m_param_N-1);
		m_variateGenerator  = new boost::variate_generator<boost::mt19937&, boost::uniform_int<> > (m_randomGenerator, *m_uniform); 

		m_selectionVector.resize (m_param_N, false);
		m_availableRands = 0;
	}

	return good;
}

bool ModuleSamplingNoutOfN::frameCall(Frame& frame)
{
	//
	// initizialization: generate numbers for n out of N
	//

	if (m_availableRands == 0) {

		assert (m_assertionCounter == 0 || m_assertionCounter == m_param_n);

		m_selectionVector.reset ();

		for (unsigned long i=0; i<m_param_n; i++) {
			int rand = (*m_variateGenerator)();

			// ensure that n unique random numbers are generated
			if (m_selectionVector [rand] == true)
				i--;
			else
				m_selectionVector [rand] = true;
		}
		
		m_availableRands	= m_param_N;
		m_assertionCounter	= 0;
	}

	//
	// check if the frame matches one n out of the N randoms
	//

	m_availableRands--;
	assert (m_availableRands < m_selectionVector.size()); 
	bool ret = (m_selectionVector.test (m_param_N - 1 - m_availableRands));
	
	if (ret) m_assertionCounter++;
	assert (m_assertionCounter >= 0 && m_assertionCounter <= m_param_n);

	return ret;
}

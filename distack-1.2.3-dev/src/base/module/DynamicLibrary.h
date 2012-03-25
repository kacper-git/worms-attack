#ifndef __DYNAMIC_LIBRARY_H
#define __DYNAMIC_LIBRARY_H

#include <string>
#include "base/common/Log.h"
#include <vector>

#ifdef WIN32	
	#define WIN32_LEAN_AND_MEAN
	#include "Windows.h"
#else
	#include <ltdl.h>
#endif

using std::vector;
using std::string;

class DynamicLibrary {
public:
	typedef list<string> SEARCH_PATHES;

	DynamicLibrary( string name, DistackInfo* info, SEARCH_PATHES pathes=SEARCH_PATHES() );
	~DynamicLibrary();

	template<class R, class P>
	R functionCall( string functionName, P param )
	{
		logging_debug( "calling function " + functionName + " in library " + m_name + " ..." );

		R ret = R ();
		typedef R(*FUNCCALL)(P); 

		FUNCCALL func = NULL;

	#ifdef WIN32
 		func = (FUNCCALL) GetProcAddress (m_module, functionName.c_str());
	#else
		func = (FUNCCALL) lt_dlsym (m_module, functionName.c_str());
	#endif

		m_state = (func != NULL);
		if (func != NULL) ret = func (param);

		logging_debug( "function call " + functionName + " in library " + 
			m_name + " " + (m_state ? "succeeded" : "failed") );
		return ret;
	}

	bool good();

protected:
	DistackInfo* distackInfo;

private:
	string m_name;
	bool m_state;

#ifdef WIN32
	HMODULE m_module;
#else
	lt_dlhandle m_module;
#endif

};

#endif // __DYNAMIC_LIBRARY_H

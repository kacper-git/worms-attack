#include "DynamicLibrary.h"

DynamicLibrary::DynamicLibrary (string name, DistackInfo* info, SEARCH_PATHES pathes)
:	m_module	(NULL),
	m_name		(name),
	m_state		(true),
	distackInfo	(info)
{
	logging_debug( "loading dynamic library " + m_name + " ...");
	m_state = false;
	
	lt_dlinit();

	SEARCH_PATHES::iterator i    = pathes.begin();
	SEARCH_PATHES::iterator iend = pathes.end  ();

	for ( ; i!=iend && !m_state; i++) {  

		string fullmodule = *i;
		fullmodule += "lib";
#ifdef WIN32
		// windows automatically attaches the ".dll" suffix to the name
		// and searches different variants for the name of the dll
		fullmodule += m_name;
		m_module = LoadLibrary (fullmodule.c_str ());
#else
		fullmodule += m_name + ".la";
		m_module = lt_dlopen (fullmodule.c_str ());
#endif

		m_state = (m_module != NULL);
	}


	logging_debug( "loading dynamic library " + m_name + " " + (m_state ? "succeeded" : "failed"));

	if (m_state == false) {
		string err = "";
#ifdef WIN32
		err = Helper::ultos (GetLastError ());
#else
		err = lt_dlerror ();
#endif
		logging_error( "loading dynamic library " + m_name + " failed with " + err);
	}
}

DynamicLibrary::~DynamicLibrary ()
{
	logging_debug( "unloading dynamic library " + m_name + " ...");

	if (m_module != NULL) {
#ifdef WIN32
		FreeLibrary (m_module);
#else	
		lt_dlclose	(m_module);
#endif
	}

	lt_dlexit();
	m_module = NULL;
}

bool DynamicLibrary::good ()
{
	return m_state;
}

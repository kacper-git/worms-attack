#ifndef __PROTOCOL_NAME_RESOLVER_H
#define __PROTOCOL_NAME_RESOLVER_H

#include <map>
#include <string>
#include <stdlib.h>

using std::map;
using std::string;
using std::pair;

class ProtocolNameResolver {
public:

	static ProtocolNameResolver*	instance				();

	string							getName					(int id);
	int								getId					(string name);

private:
									ProtocolNameResolver	();
									~ProtocolNameResolver	();

	class Guard {
		public: ~Guard() {
			if (ProtocolNameResolver::object != NULL)
				delete ProtocolNameResolver::object;
			}
	};

	friend class					Guard;
	static ProtocolNameResolver*	object;

	typedef pair<int, string>			PROTOCOL_NAME_PAIR;
	typedef map <int, string>			PROTOCOL_NAME_MAP;
	typedef PROTOCOL_NAME_MAP::iterator PROTOCOL_NAME_MAP_ITERATOR;
	PROTOCOL_NAME_MAP					protocolNameMap;
};

#endif // __PROTOCOL_NAME_RESOLVER_H

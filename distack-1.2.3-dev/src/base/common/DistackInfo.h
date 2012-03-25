#ifndef __DISTACKINFO_H
#define __DISTACKINFO_H

#include <string>

using std::string;

/** @class DistackInfo
  * used to store setup parameters about a Distack instance
  */
class DistackInfo {
public:
	DistackInfo( int id, string conf, string path );
	~DistackInfo();

	/// a string to separate Distack instances using the same configfile
	int distackId;

	/// the filename of the xml to use for configuration
	string configId;

	/// the full module path of the DistackOmnetModule as reported by Omnet++
	string modulePath;
};

#endif // __DISTACKINFO_H

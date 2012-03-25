//
// Generated file, do not edit! Created by opp_msgc 4.1 from networklayer/ipv4/IPDatagram_hacked.msg.
//

#ifndef _IPDATAGRAM_HACKED_M_H_
#define _IPDATAGRAM_HACKED_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0401
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// dll export symbol
#ifndef REASE_API 
#  if defined(REASE_EXPORT)
#    define REASE_API  OPP_DLLEXPORT
#  elif defined(REASE_IMPORT)
#    define REASE_API  OPP_DLLIMPORT
#  else
#    define REASE_API 
#  endif
#endif

// cplusplus {{
#include "IPDatagram.h"
#include "ReaSEDefs.h"
// }}



/**
 * Class generated from <tt>networklayer/ipv4/IPDatagram_hacked.msg</tt> by opp_msgc.
 * <pre>
 * packet IPDatagram_hacked extends IPDatagram
 * {
 * 	
 * 	short attackTag = 0;
 * }
 * </pre>
 */
class REASE_API IPDatagram_hacked : public ::IPDatagram
{
  protected:
    short attackTag_var;

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const IPDatagram_hacked&);

  public:
    IPDatagram_hacked(const char *name=NULL, int kind=0);
    IPDatagram_hacked(const IPDatagram_hacked& other);
    virtual ~IPDatagram_hacked();
    IPDatagram_hacked& operator=(const IPDatagram_hacked& other);
    virtual IPDatagram_hacked *dup() const {return new IPDatagram_hacked(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual short getAttackTag() const;
    virtual void setAttackTag(short attackTag_var);
};

inline void doPacking(cCommBuffer *b, IPDatagram_hacked& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, IPDatagram_hacked& obj) {obj.parsimUnpack(b);}


#endif // _IPDATAGRAM_HACKED_M_H_
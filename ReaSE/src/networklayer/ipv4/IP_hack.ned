package rease.networklayer.ipv4;

import inet.networklayer.ipv4.IP;

//
// An extension of inet.networklayer.ipv4.IP 
// This module additionally allows for address spoofing,
// packet tracing, packet copying to attack detection instances, 
// and router alert option.
//

simple IP_hack extends IP
{
    parameters:
        @class(IP_hack);
        bool tracingOn; 
        double tracingInterval @unit(s);
        double traceStartTime @unit(s); 
        bool copyFlag; // copy the first fragment of a packet to distack
        bool raoOn; // activate handling of packets with Router Alert Option
        bool spoofingOn; // allow IP-Address Spoofing
    gates:
        input distackIn;  // currently unused
        input distackSigIn; // for attack detection signaling 
        input raoIn; // for IP-Router-Alert Option
        output distackOut; // used for copied datagrams (see copyFlag)
        output distackSigOut; // for attack detection signaling
        output raoOut; // for IP-Router-Alert Option
}


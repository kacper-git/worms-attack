/**
 * @file LinkMonitor.cc
 * @brief An implementation of the Link Monitor Managed Object.
 * @author Tina Yu (tinayu@it.usyd.edu.au)
 * @date 22/09/10
 * */

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.

#include "LinkMonitor.h"
#include <sstream>
#include "EventPublisher.h"
#include "MechanismExporter.h"
#include <string>
#include "IPDatagram_m.h"

Register_Class(LinkMonitor);

bool triggered;

LinkMonitor::LinkMonitor(const char *name) : cDatarateChannel(name)
{
    batchSize = 10;
    maxInterval = 0.1;
    threshold = 100;   
    intvlTime = 100;
    cnt = 0;
    value = 0;
    triggered_count = 0;
    numPackets = 0;
    numBits = 0;
    triggered = false;

    intvlStartTime = intvlLastPkTime = 0;
    intvlNumPackets = benignNumPackets = maliciousNumPackets = intvlNumBits = 0;
}

LinkMonitor::~LinkMonitor()
{
	delete out_vectors["N"]; 
	delete out_vectors["V"]; 
	delete out_vectors["p"]; 
	delete out_vectors["b"]; 
	delete out_vectors["m"];
	delete out_vectors["b"];
	delete out_vectors["P"];
	delete out_vectors["B"];
	delete out_vectors["T"];
}

bool LinkMonitor::initializeChannel(int stage) {

	cDatarateChannel::initializeChannel(stage);

	const char *fmt = this->par("format");
	char buf[200];
	char *p = buf;
	std::stringstream n;
	for (const char *fp = fmt; *fp && buf+200-p>20; fp++)
	{
		 n.str("");
		 switch (*fp)
		 {
			 case 'N': // number of packets
				 n << "Number of Packets from " << this->getSourceGate()->getOwnerModule()->getFullPath();
				 this->out_vectors.insert(std::make_pair<const char*,cOutVector*> ("N",new cOutVector(n.str().c_str())));

				 break;
			 case 'V': // volume (in bytes)
				 n << "Volume from " << this->getSourceGate()->getOwnerModule()->getFullPath();
				 this->out_vectors.insert(std::make_pair<const char*,cOutVector*> ("V",new cOutVector(n.str().c_str())));
				 break;
			 case 'p': // current packet/sec
				 n << "current overall packet/sec from " << this->getSourceGate()->getOwnerModule()->getFullPath();
				 this->out_vectors.insert(std::make_pair<const char*,cOutVector*> ("p",new cOutVector(n.str().c_str())));
				 n.str("");
				 n << "current malicious packet/sec from " << this->getSourceGate()->getOwnerModule()->getFullPath();
				this->out_vectors.insert(std::make_pair<const char*,cOutVector*> ("m",new cOutVector(n.str().c_str())));
				n.str("");
				n << "current benign packet/sec from " << this->getSourceGate()->getOwnerModule()->getFullPath();
				this->out_vectors.insert(std::make_pair<const char*,cOutVector*> ("b",new cOutVector(n.str().c_str())));
				 break;
			 case 'b': // current bandwidth
				 n << "CurrentBandwidth from " << this->getSourceGate()->getOwnerModule()->getFullPath();
				 this->out_vectors.insert(std::make_pair<const char*,cOutVector*> ("b",new cOutVector(n.str().c_str())));
				 break;
			 case 'P': // average packet/sec on [0,now)
				 n << "average packet/sec from " << this->getSourceGate()->getOwnerModule()->getFullPath();
				 this->out_vectors.insert(std::make_pair<const char*,cOutVector*> ("P",new cOutVector(n.str().c_str())));
				 break;
			 case 'B': // average bandwidth on [0,now)
				 n << "AverageBandwidth from " << this->getSourceGate()->getOwnerModule()->getFullPath();
				 this->out_vectors.insert(std::make_pair<const char*,cOutVector*> ("B",new cOutVector(n.str().c_str())));
				 break;
			case 'T': // threashold checking 
				 n << "Value from" << this->getSourceGate()->getOwnerModule()->getFullPath();
				 this->out_vectors.insert(std::make_pair<const char*,cOutVector*> ("T",new cOutVector(n.str().c_str())));
				 break;
			 default:
				 *p++ = *fp;
		 }
	}

	return false;
}
#if OMNETPP_VERSION>0x0400
void LinkMonitor::processMessage(cMessage *msg, simtime_t t, result_t& result)
{
    cDatarateChannel::processMessage(msg, t,result);
    if (dynamic_cast<cPacket*>(msg)) {

		// count packets and bits
		numPackets++;
		numBits += ((cPacket*)msg)->getBitLength();

		if (intvlNumPackets >= batchSize || t-intvlStartTime >= maxInterval)
			beginNewInterval(t);

		intvlNumPackets++;
		string name = msg->getName();
		if ((name.compare("udp_flood") == 0) || (name.compare("SYN-Flood") == 0) || (name.compare("ping_flood") == 0)) {
			maliciousNumPackets++;
		} else {
			benignNumPackets++;
			//cerr << name << endl;
		}
		intvlNumBits += ((cPacket*)msg)->getBitLength();
		intvlLastPkTime = t;

		updateDisplay();
    }
}
#else
bool LinkMonitor::deliver(cMessage *msg, simtime_t t)
{
    bool ret = cDatarateChannel::deliver(msg, t);

    if (dynamic_cast<cPacket*>(msg)) {

		numPackets++;
		numBits += ((cPacket*)msg)->getBitLength();

		if (intvlNumPackets >= batchSize || t-intvlStartTime >= maxInterval)
			beginNewInterval(t);

		intvlNumPackets++;
		intvlNumBits += ((cPacket*)msg)->getBitLength();
		intvlLastPkTime = t;

		// update display  
		updateDisplay();
    }
    return ret;
}
#endif

void LinkMonitor::beginNewInterval(simtime_t now) {
    simtime_t duration = now - intvlStartTime;

    currentBitPerSec = intvlNumBits/duration;
    currentPkPerSec = intvlNumPackets/duration;
    maliciousPkPerSec = maliciousNumPackets/duration;
    benignPkPerSec = benignNumPackets/duration;

    intvlStartTime = now;
    intvlNumPackets = maliciousNumPackets = benignNumPackets = intvlNumBits = 0;
}

void LinkMonitor::updateDisplay()
{
    const char *fmt = this->par("format");

    char buf[200];
    char *p = buf;
    simtime_t tt = getTransmissionFinishTime();
    if (tt==0) tt = simTime();
    double bps = (tt==0) ? 0 : numBits/tt;
    double bytes;
    for (const char *fp = fmt; *fp && buf+200-p>20; fp++)
    {
        switch (*fp)
        {
            case 'N': // number of packets
                p += sprintf(p, "N: %ld", numPackets);
                this->out_vectors["N"]->record(numPackets);
                EV << "NUMBER OF PACKETS " << numPackets << "\n";  
                break;
            case 'V': // volume (in bytes)
                bytes = floor(numBits/8);
                this->out_vectors["V"]->record(bytes);
                if (bytes<1024) {
                    p += sprintf(p, "V: %gB", bytes);
                    EV << "VOLUME " << bytes << "B\n";  
                } else if (bytes<1024*1024) {
                    p += sprintf(p, "V: %.3gKB", bytes/1024);
                    EV << "VOLUME " << bytes/1024 << "KB\n";  
                } else {
                    p += sprintf(p, "V: %.3gMB", bytes/1024/1024);
                    EV << "VOLUME " << bytes/1024/1024 << "MB\n";  
                }
                break;

            case 'p': // current packet/sec
            	p += sprintf(p, "p: %.3gpps", currentPkPerSec);
            	if (currentPkPerSec >= 0 ) {
            		this->out_vectors["p"]->record(currentPkPerSec);this->out_vectors["p"]->record(currentPkPerSec);
            		this->out_vectors["b"]->record(benignPkPerSec);this->out_vectors["b"]->record(benignPkPerSec);
            		this->out_vectors["m"]->record(maliciousPkPerSec);this->out_vectors["m"]->record(maliciousPkPerSec);}

            	EV << "CURRENT " << currentPkPerSec << "packet/sec \n";
				if ((currentPkPerSec>=3000) && triggered == false) {
					triggered_count++;
					if (triggered_count == 100) {
						triggered = true;
						vector<string> values;
						values.push_back(this->getFullPath());
						std::string s;
						std::stringstream out;
						out << this->getSourceGate()->getNextGate()->getIndex();
						s = out.str();
						values.push_back(s);
						EventPublisher publisher;
						publisher.publish("load",values);
					}
				}
			break;

            case 'b': // current bandwidth
            	this->out_vectors["b"]->record(currentBitPerSec);

                if (currentBitPerSec<1000000){
                    p += sprintf(p, "b: %.3gk", currentBitPerSec/1000);
                    EV << "CURRENT BW " << currentBitPerSec/1000 << "k\n";
                }
                else{
                    p += sprintf(p, "b: %.3gM", currentBitPerSec/1000000);
                    EV << "CURRENT BW " << currentBitPerSec/1000000 << "M\n";
                }
                break;

            case 'P': // average packet/sec on [0,now)
                p += sprintf(p, "Avg P: %.3gpps", tt==0 ? 0 : numPackets/tt);
                this->out_vectors["P"]->record(tt==0 ? 0 : numPackets/tt);
                EV << "AVERAGE " << numPackets/tt<< "packet/sec \n";  

                break;

            case 'T': // check threshold
            	p += sprintf(p, "T: %d", value);
            	this->out_vectors["T"]->record(value);
            	if (currentPkPerSec > threshold){
            		cnt += 1;
            		if (cnt == intvlTime)
            			value = 1;
            	} 
            	else {
            		cnt=0;
            		value = 0;
            	}

                EV << "VALUE " << value << " \n"; 
                break;

            case 'B': // average bandwidth on [0,now)
            	this->out_vectors["B"]->record(bps);
            	bubble("this is B");
                if (bps<1000000){
                    p += sprintf(p, "Avg B: %.3gk", bps/1000);
		    EV << "AVERAGE BW " << bps/1000 << "k\n";  
                }
                else{
                    p += sprintf(p, "Avg B: %.3gM", bps/1000000);
                    EV << "AVERAGE BW " << bps/1000000 << "M\n";  
                }
                break;

            default:
                *p++ = *fp;
        }
    }
    *p = '\0';

    getSourceGate()->getDisplayString().setTagArg("t", 0, buf);

}


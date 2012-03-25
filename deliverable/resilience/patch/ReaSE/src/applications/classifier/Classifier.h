/**
 * @file Classifier.h
 * @brief Header file to support the implementation of the Classifier Managed Object.
 * @author Matthew Broadbent (m.broadbent@lancs.ac.uk)
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

#ifndef CLASSIFIER_H_
#define CLASSIFIER_H_

#include "INETDefs.h"

class INET_API Classifier : public cSimpleModule
{
protected:
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
	virtual void finish();
    long packetCount;
    int false_positive;
    int false_negative;
};

#endif /* CLASSIFIER_H_ */

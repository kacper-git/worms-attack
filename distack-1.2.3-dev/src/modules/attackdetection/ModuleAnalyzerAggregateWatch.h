#ifndef __MODULE_ANALYZER_AGGREGATE_WATCH_H
#define __MODULE_ANALYZER_AGGREGATE_WATCH_H

#include "base/common/Log.h"
#include "base/common/Helper.h"
#include "base/module/DistackModuleInterface.h"
#include "messages/attackdetection/MessageAggregateWatchValues.h"
#include "messages/attackdetection/MessageLastSuspiciousAggregate.h"
#include "messages/utility/MessageAlert.h"
#include "messages/utility/MessageTimer.h"
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/thread/mutex.hpp>

using std::pair;
using std::map;
using std::vector;
using std::max;

class ModuleAnalyzerAggregateWatch : public DistackModuleInterface {
public: 
									ModuleAnalyzerAggregateWatch	();
									~ModuleAnalyzerAggregateWatch	();

	bool							configure						(ModuleConfiguration& configList);
	bool							frameCall						(Frame& frame);

	void							registerMessages				();
	void							receiveMessage					(Message* msg);

private:

	void							handleTimerMsg					();
	void							handleSuspiciousAggregateMsg	(Message* msg);

	string							m_param_TimerModule;
	
	static const string				PARAM_AlphaAvg;
	static const string				PARAM_AlphaDev;
	static const string				PARAM_AlphaLearn;
	static const string				PARAM_AlphaRed;
	static const string				PARAM_Beta;
	static const string				PARAM_ExceedThreshold;
	static const string				PARAM_FrameSizeBorders;
	static const string				PARAM_TimerModule;
	static const string				PARAM_LearningIntervals;

	boost::mutex					m_counterMutex;

	//
	// here follow all aggregate counters
	//

	typedef struct _AGGREGATE_WATCH_PARAMS {
		double			alphaAvg;
		double			alphaDev;
		double			alphaRed;
		double			alphaLearn;
		double			beta;
		unsigned int		exceedThreshold;
		unsigned int		learningIntervals;
		
		_AGGREGATE_WATCH_PARAMS (double aAvg = 0, double aDev = 0, 
						double aRed = 0, double aLearn = 0, 
						double b = 0, unsigned int eThresh = 0, 
						unsigned int lInt = 0) {
			alphaAvg = aAvg;
			alphaDev = aDev;
			alphaRed = aRed;
			alphaLearn = aLearn;
			beta = b;
			exceedThreshold = eThresh;
			learningIntervals = lInt;
		}
	} AGGREGATE_WATCH_PARAMS;

	AGGREGATE_WATCH_PARAMS			params;

	typedef struct _AGGREGATE_WATCH_ITEM {
//modified 1 line added
		AGGREGATE_WATCH_PARAMS parameters;

		typedef enum _AGGREGATE_TYPE {
			AGGREGATE_TYPE_PROTOCOL,	// the aggregate watches the number of protocols
			AGGREGATE_TYPE_SIZE,		// the aggregate watches frame sizes
		} AGGREGATE_TYPE;

		typedef enum _AGGREGATE_RESULT {
			AGGREGATE_RESULT_NOTHING	= 0x0,
			AGGREGATE_RESULT_LOWERALERT	= 0x1,
			AGGREGATE_RESULT_RAISEALERT  	= 0x2,
		} AGGREGATE_RESULT;

		typedef enum _EWMA_VALUE_GROUP {
			EWMA_VALUE_GROUP_AVG,
			EWMA_VALUE_GROUP_DEV,
			EWMA_VALUE_GROUP_RED,
			EWMA_VALUE_GROUP_LEARN,
		} EWMA_VALUE_GROUP;

		double			deviation;
		double			deviationThreshold;
		double			deviationThresholdLow;
		double			threshold;
		double			thresholdLow;
		unsigned long		counter;
		double			average;
		unsigned long		intervalNo;
		unsigned short		exceedCounter;
		bool			saveMode;

		bool			n_1_Exceeded;

		AGGREGATE_TYPE		aggregateType;	// the type of aggregate we are watching
		string			description;	// a description for the aggregate we are watching
		Packet::PROTOCOL	protocol;	// the protocol number if we are watching protocols

		_AGGREGATE_WATCH_ITEM (AGGREGATE_TYPE type, string descr, AGGREGATE_WATCH_PARAMS param) {
			parameters = param;
			
			counter = intervalNo = exceedCounter = 0;
			average = deviation = threshold	 = thresholdLow = 0.0;
			deviationThreshold = deviationThresholdLow = 0.0;
			
			saveMode	= false;
			aggregateType	= type;
			description	= descr;
			protocol	= Packet::PROTO_NONE;

			n_1_Exceeded	= false;

		} // _AGGREGATE_WATCH_ITEM (AGGREGATE_TYPE type, string descr)

		void updateParameters (EWMA_VALUE_GROUP groupDeviation, EWMA_VALUE_GROUP groupAverage) {

			{
				double val = 0.0;
				
				switch (groupDeviation) {
					case EWMA_VALUE_GROUP_DEV:		val = parameters.alphaDev;		break;
					case EWMA_VALUE_GROUP_RED:		val = parameters.alphaRed;		break;
					case EWMA_VALUE_GROUP_LEARN:	val = parameters.alphaLearn;	break;
					default:						assert (false);		break;
				}
				
				if (groupDeviation == EWMA_VALUE_GROUP_RED) {
					if (deviationThresholdLow < counter && counter < deviationThreshold)
					deviation = (1.0 - parameters.alphaDev) * (double)deviation + parameters.alphaDev * fabs (double((double)counter - average));
				} else {
					deviation = (1.0 - val) * (double)deviation + val * fabs (double((double)counter - average));
				}

			}
	
			{
				double val = 0.0;
				
				switch (groupAverage) {
					case EWMA_VALUE_GROUP_AVG:		val = parameters.alphaAvg;		break;
					case EWMA_VALUE_GROUP_RED:		val = parameters.alphaRed;		break;
					case EWMA_VALUE_GROUP_LEARN:	val = parameters.alphaLearn;	break;
					default:						assert (false);		break;
				}
				
				average = (1.0 - val) * (double)average   + val * (double)counter;

			}
			threshold	 			= average + parameters.beta * deviation;
			thresholdLow 			= max (average - parameters.beta * deviation, 0.0);
			deviationThreshold	  	= average + 2 * parameters.beta * deviation;
			deviationThresholdLow 	= max (average - 2 * parameters.beta * deviation, 0.0);

		} // void updateParameters (EWMA_VALUE_GROUP groupDeviation, EWMA_VALUE_GROUP groupAverage)

		AGGREGATE_RESULT exceeded () {
		
			intervalNo++;

			//
			// are we in the learning phase?
			//

			if (intervalNo <= parameters.learningIntervals) {
				updateParameters (EWMA_VALUE_GROUP_LEARN, EWMA_VALUE_GROUP_LEARN);
				counter = 0;
				return AGGREGATE_RESULT_NOTHING;
			}

			//
			// no learning phase
			//

			//
			// counter under lower threshold
			//

			// 
			// one normal interval (without exceeding) may occur between two suspicious intervals
			//
			if (counter < thresholdLow) {
		
				AGGREGATE_RESULT ret = AGGREGATE_RESULT_NOTHING;
						
				if (n_1_Exceeded == false) {

					//
					// saveMode will be set back only in case of two subsequent intervals with normal values
					//

					if (saveMode) {
						ret		 = AGGREGATE_RESULT_LOWERALERT;
						saveMode = false;
					}
					exceedCounter = 0;
				}

				updateParameters (EWMA_VALUE_GROUP_RED, EWMA_VALUE_GROUP_RED);
					
				n_1_Exceeded = false;

				counter = 0;
				return ret;
			}

			//
			// counter in normal range (between lower and upper threshold)
			//

			if (thresholdLow <= counter && counter <= threshold) {

				AGGREGATE_RESULT ret = AGGREGATE_RESULT_NOTHING;

				if (n_1_Exceeded == false) {

					//
					// saveMode will be set back only in case of two subsequent intervals with normal values
					//

					if (saveMode) {
						ret		 = AGGREGATE_RESULT_LOWERALERT;
						saveMode = false;
					} 
					exceedCounter = 0;
				}

				updateParameters (EWMA_VALUE_GROUP_DEV, EWMA_VALUE_GROUP_AVG);
			
				n_1_Exceeded = false;

				counter = 0;
				return ret;
			}

			//
			// threshold exceeded
			//

			if (counter > threshold) {

				AGGREGATE_RESULT ret = AGGREGATE_RESULT_NOTHING;

				exceedCounter++;

				if (exceedCounter > parameters.exceedThreshold) {

					// CHANGE THOMAS: Alert-Message wird nur noch einmalig gesendet
					if (saveMode == false) {
						saveMode = true;
						ret = AGGREGATE_RESULT_RAISEALERT;
					}

				} else {

					if (saveMode == false) 
						updateParameters (EWMA_VALUE_GROUP_RED, EWMA_VALUE_GROUP_RED);

				} // if (exceedCounter >= exceedThreshold)

				n_1_Exceeded = true;

				counter = 0;
				return ret;

			} // if (counter > threshold)

			assert (false);
			counter = 0;
			return AGGREGATE_RESULT_NOTHING;

		} // bool exceeded ()
			
	} AGGREGATE_WATCH_ITEM, *PVALUE_WATCHING;

	//
	// count protocol occurences
	//

	typedef pair<Packet::PROTOCOL,AGGREGATE_WATCH_ITEM>	PROTOCOL_COUNT_PAIR;
	typedef map <Packet::PROTOCOL,AGGREGATE_WATCH_ITEM>	PROTOCOL_COUNT_MAP;
	typedef PROTOCOL_COUNT_MAP::iterator			PROTOCOL_COUNT_MAP_ITERATOR;
	PROTOCOL_COUNT_MAP					m_protocolCountMap;

	//
	// count frame size distributions
	//

	typedef pair<unsigned int, unsigned int>		SIZE_RANGE;
	typedef pair<SIZE_RANGE, AGGREGATE_WATCH_ITEM>		SIZE_COUNT_PAIR;
	typedef map<SIZE_RANGE, AGGREGATE_WATCH_ITEM>		SIZE_COUNT_MAP;
	typedef SIZE_COUNT_MAP::iterator			SIZE_COUNT_MAP_ITERATOR;
	SIZE_COUNT_MAP						m_sizeCountMap;

	//
	// the stage we are sitting on. only important 
	// for sending out alert messages
	//

	unsigned short m_stage;

	//
	// the last aggregate that was found to be suspicious
	//

	PVALUE_WATCHING m_lastSuspicious;
			
};

#endif // __MODULE_ANALYZER_AGGREGATE_WATCH_H

#ifndef __FRAME_DISTRIBUTION_H
#define __FRAME_DISTRIBUTION_H

#include "base/network/FrameBuffer.h"
#include "base/module/ChannelManager.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>

class FrameDistribution {
public:
							FrameDistribution		(DistackInfo* info);
							~FrameDistribution		();
	
	void					setChannelManager		(ChannelManager* channelmanager);
	void					setFrameBuffer			(FrameBuffer* framebuffer);

	bool					startDistribution		();
	bool					stopDistribution		();

	void					manualFrameInjection	(Frame* frame);

private:
	DistackInfo*			distackInfo;

	static void				distribThreadFunction	(FrameDistribution* obj);
	boost::thread*			m_distributionThread;
	volatile bool			m_threadRunning;

	boost::mutex			m_distributionMutex;
	ChannelManager*			m_channelManager;
	FrameBuffer*			m_frameBuffer;

	unsigned long			m_frameCount;

};

#endif // __FRAME_DISTRIBUTION_H

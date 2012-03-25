#ifndef __FRAME_BUFFER_H
#define __FRAME_BUFFER_H

#include <queue>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include "base/network/NetworkInterface.h"
#include "base/configuration/Configuration.h"

using std::queue;

class FrameBuffer {
public:
	FrameBuffer( NetworkInterface& networkInterface, DistackInfo* info );
	~FrameBuffer();
	
	void startup();
	void prepareshutdown();
	void shutdown();
	Frame* next();
	void clear();
	unsigned int count();

	void setMaxFrames( unsigned int frames );
	void setMaxBytes( unsigned int bytes );

	unsigned int getFrameDrops();
	unsigned int getByteDrops();

	NetworkInterface& getNetworkInterface();

private:
	DistackInfo* distackInfo;

	static void readThreadFunction( FrameBuffer* obj );
	boost::thread* m_readThread;
	volatile bool m_threadRunning;

	NetworkInterface& m_networkInterface;

	boost::mutex m_counterMutex;
	unsigned int m_maxFrames;
	unsigned int m_maxBytes;
	unsigned int m_currentFrames;
	unsigned int m_currentBytes;
	unsigned int m_droppedFrames;
	unsigned int m_droppedBytes;

	typedef queue<Frame*> FRAME_QUEUE;
	FRAME_QUEUE m_frameQueue;
	boost::mutex m_frameQueueMutex;

	bool m_onlineCapture;
};

#endif // __FRAME_BUFFER_H

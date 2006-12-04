/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * ifthreadtest.cpp               Test for IFThread
 * =========================================================================
 * 
 * This file is part of Ionflux Object Base System.
 * 
 * Ionflux Object Base System is free software; you can redistribute it 
 * and/or modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation; either version 2 of the 
 * License, or (at your option) any later version.
 * 
 * Ionflux Object Base System is distributed in the hope that it will be 
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Ionflux Object Base System; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

 * ========================================================================== */

#include <iostream>
#include <sstream>
#include "ifobject/IFThread.hpp"
#include "ifobject/IFGuard.hpp"
#include "ifobject/IFLogMessage.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;

/// Class information for class TestThread.
class TestThreadClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		TestThreadClassInfo();
		/// Destructor.
		virtual ~TestThreadClassInfo() { };
};

TestThreadClassInfo::TestThreadClassInfo()
{
	name = "TestThread";
	desc = "Test thread";
	baseClassInfo.push_back(IFThread::CLASS_INFO);
}

// Subclass of IFThread which is used for testing.
class TestThread
: public IFThread
{
	public:
		// Class information instance.
		static const TestThreadClassInfo testThreadClassInfo;
		// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		// Maximum number of iterations.
		static const unsigned int MAX_ITERATIONS;
		
		// Thread action interval (sec).
		unsigned int interval;
		
		// Constructor.
		TestThread();
		// Constructor.
		TestThread(unsigned int initInterval);
		// Destructor.
		virtual ~TestThread();
		
		// Override the run() method to implement custom behavior.
		virtual void* run();
};

const TestThreadClassInfo TestThread::testThreadClassInfo;
const Ionflux::ObjectBase::IFClassInfo* TestThread::CLASS_INFO = &TestThread::testThreadClassInfo;
const unsigned int TestThread::MAX_ITERATIONS = 20;

TestThread::TestThread()
: interval(1)
{
	theClass = CLASS_INFO;
}

TestThread::TestThread(unsigned int initInterval)
: interval(initInterval)
{
	theClass = CLASS_INFO;
}

TestThread::~TestThread()
{ }

void* TestThread::run()
{
	ostringstream message;
	unsigned int i = 0;
	while (runFlag
		&& (i < MAX_ITERATIONS))
	{
		sleep(interval);
		message.str("");
		message << "Thread #" << idNum << ": Doing stuff (" << i << ").";
		log(IFLogMessage(message.str(), VL_INFO, 
			this, "run"));
		i++;
	}
	return 0;
}

// A simple logging class with guarded output.
class TestLogger
: public IFObject
{
	public:
		// Constructor.
		TestLogger();
		// Destructor.
		virtual ~TestLogger();
		
		// Logging function.
		virtual void log(const Ionflux::ObjectBase::IFObject& logObject) const;
		// Logging function for text messages.
		virtual void log(const std::string& msg) const;
};

TestLogger::TestLogger()
{
	setGuardEnabled(true);
}

TestLogger::~TestLogger()
{ }

void TestLogger::log(const Ionflux::ObjectBase::IFObject& logObject) const
{
	IFGuard guard(guardMutex);
	IFObject::log(logObject);
}

void TestLogger::log(const std::string& msg) const
{
	IFGuard guard(guardMutex);
	std::cout << msg;
}

int main(int argc, char* argv[])
{
	TestLogger logger;
	ostringstream msg;
	msg << "Test for IFThread" << endl;
	logger.log(msg.str());
	const unsigned int NUM_THREADS = 10;
	const unsigned int NUM_INTERVALS = 10;
	const unsigned int INTERVALS[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	msg.str("");
	msg << "Creating threads... ";
	logger.log(msg.str());
	std::vector<TestThread*> threads;
	for (unsigned int i = 0; i < NUM_THREADS; i++)
	{
		TestThread* currentThread = new TestThread(
			INTERVALS[i % NUM_INTERVALS]);
		currentThread->setIDNum(i + 1);
		currentThread->setLogTarget(&logger);
		threads.push_back(currentThread);
	}
	msg.str("");
	msg << "done." << endl;
	logger.log(msg.str());
	msg.str("");
	msg << "Starting threads... ";
	logger.log(msg.str());
	for (unsigned int i = 0; i < NUM_THREADS; i++)
		threads[i]->start();
	msg.str("");
	msg << "done." << endl;
	logger.log(msg.str());
	msg.str("");
	msg << "Waiting for threads to finish..." << endl;
	logger.log(msg.str());
	for (unsigned int i = 0; i < NUM_THREADS; i++)
		threads[i]->join();
	msg.str("");
	msg << "Done." << endl;
	logger.log(msg.str());
	msg.str("");
	msg << "All tests finished." << endl;
	logger.log(msg.str());
	return 0;
}

/** \file ifthreadtest.cpp
 * \brief Test for IFThread
 */

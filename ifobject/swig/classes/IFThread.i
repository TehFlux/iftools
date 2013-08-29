/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006-2011 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFThread.i                      Thread (interface).
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
 * 
 * ========================================================================== */
%{
#include "ifobject/IFThread.hpp"
%}

// forward declarations for types from the Ionflux Object Base System
namespace Ionflux
{

namespace ObjectBase
{

class IFSignal;

}

}

namespace Ionflux
{

namespace ObjectBase
{

// events used by IFThread
class IFThreadEvent;

typedef void* (*IFThreadFunction)(void*);
typedef sigc::signal<bool, const Ionflux::ObjectBase::IFThreadEvent&> 
IFThreadSignal;

struct IFThreadSignalConnections
{
    sigc::connection signalStartConnection;
    sigc::connection signalRunConnection;
    sigc::connection signalStopConnection;
};

class IFThreadClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IFThreadClassInfo();
        virtual ~IFThreadClassInfo();
};

class IFThread
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const IFAtomic SHUTDOWN_DISABLED;
		static const IFAtomic SHUTDOWN_ENABLED;
        static const Ionflux::ObjectBase::IFSignalType SIGNAL_TYPE_THREAD;
        static const std::string SIGNAL_NAME_START;
        static const std::string SIGNAL_NAME_RUN;
        static const std::string SIGNAL_NAME_STOP;
        
        IFThread();
        virtual ~IFThread();        
        IFThreadEvent* createThreadEvent();
        virtual bool start();
        virtual void* run();
        virtual void* join();
        virtual void stop();
        virtual bool isRunning() const;
        static void* startImpl(void* threadArgs);
        static Ionflux::ObjectBase::IFObject* 
        create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual Ionflux::ObjectBase::IFObject* copy() const;
        virtual std::string getString() const;
        static void sleep(unsigned int sleepSecs);
        static void nanoSleep(unsigned int sleepSecs, unsigned int 
        sleepNanoSecs);
        virtual void 
        setThreadFunction(Ionflux::ObjectBase::IFThreadFunction 
        newThreadFunction);
        virtual Ionflux::ObjectBase::IFThreadFunction getThreadFunction() 
        const;
        virtual void setContext(Ionflux::ObjectBase::IFObject* newContext);
        virtual Ionflux::ObjectBase::IFObject* getContext() const;
        virtual IFThreadSignal& getSignalStart();
        virtual Ionflux::ObjectBase::IFSignal* getSignalStartWrapper();
        virtual IFThreadSignal& getSignalRun();
        virtual Ionflux::ObjectBase::IFSignal* getSignalRunWrapper();
        virtual IFThreadSignal& getSignalStop();
        virtual Ionflux::ObjectBase::IFSignal* getSignalStopWrapper();
};

}

}

/* ==========================================================================
 * Ionflux Object Base System
 * Copyright © 2006 Joern P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * IFExampleClass.i                Example class (interface).
 * =========================================================================

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
#include "ifobject/IFExampleClass.hpp"
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

// events used by IFExampleClass
class IFExampleEvent;

typedef std::map<int, int> FooMap;
typedef sigc::signal<void, const Ionflux::Example::IFExampleEvent&> 
IFExampleSignal;
 
struct Blupp
{
    int foo;
    int bar;
};
 
struct Blah
{
    double baz;
    double baf;
    static const int SOME_FLAG;
};

struct IFExampleSignalConnections
{
    sigc::connection signalFirstConnection;
    sigc::connection signalSecondConnection;
};

class IFExampleClassClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        IFExampleClassClassInfo();
        virtual ~IFExampleClassClassInfo();
};

class IFExampleClass
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const std::string MODULE_NAME;
		static const unsigned int MODULE_VERSION;
        static const Ionflux::ObjectBase::IFSignalType SIGNAL_TYPE_EXAMPLE;
        static const std::string SIGNAL_NAME_FIRST;
        static const std::string SIGNAL_NAME_SECOND;
        
        IFExampleClass();
        IFExampleClass(double initMiep);
        virtual ~IFExampleClass();        
        IFExampleEvent* createExampleEvent();
        virtual void doNothing() const;
        virtual bool serialize(std::string& target) const;
        virtual int deserialize(const std::string& source, int offset = 0);
        virtual void setSomeValue(int newSomeValue);
        virtual int getSomeValue() const;
        virtual void setSomeText(const std::string& newSomeText);
        virtual std::string getSomeText() const;
        virtual double getRoProp() const;
        virtual void setSpecialBlah(Blah* newSpecialBlah);
        virtual Blah* getSpecialBlah() const;        
        virtual unsigned int getNumBlupps() const;
        virtual Blupp* getBlupp(unsigned int elementIndex = 0) const;
		virtual int findBlupp(Blupp* needle, unsigned int occurence = 1) const;
        virtual std::vector<Blupp*>& getBlupps();
        virtual void addBlupp(Blupp* addElement);        
        virtual void removeBlupp(Blupp* removeElement);
		virtual void removeBluppIndex(unsigned int removeIndex);
        virtual void clearBlupps();
        virtual unsigned int getNumBlahs() const;
        virtual Blah* getBlahs(const std::string& elementKey) const;

        virtual std::map<std::string, Blah*>& getBlahs();
        virtual void addBlah(const std::string& elementKey, Blah* 
        addElement);        
        virtual void removeBlah(const std::string& elementKey);        
        virtual void clearBlahs();
        virtual IFExampleSignal& getSignalFirst();
        virtual Ionflux::ObjectBase::IFSignal* getSignalFirstWrapper();
        virtual IFExampleSignal& getSignalSecond();
        virtual Ionflux::ObjectBase::IFSignal* getSignalSecondWrapper();
};

}

}

# Ionflux Object Base System
Copyright © 2006-2024 • Jörn Meier <webmaster@ionflux.org>

## Specification

The Ionflux Object Base System shall provide at least the following features:

+ An IFObject base type from which other types can be derived.

+ Verbose run-time type information, including information on inheritance, as 
  far as types derived from IFObject are concerned. Run-time type information 
  will support multiple inheritance. Type information is provided by a static 
  instance of IFClassInfo.
  
+ Reference-count based semi-automatic memory management.

+ Object instance identifiers: Each instance of an IFObject based type may 
  have a string identifier and a numerical identifier (which is an integer of 
  at least 64 bits).

+ A global MT randomizer instance which provides random numbers and 
  identifiers.

+ Member functions for creating, destroying and copying IFObject based types.

+ Hooks to create and destroy IFObject based types from C code.

+ Functions for creating a string representation of the object. The string 
  representation should identify the type and the instance ID for complex 
  types. It is a literal representation for simple types (Bool, Int, BigInt, 
  Real, String).

+ Object-level locking, if threads are used. This can be enabled on demand or 
  by using IFGuardedObject as base class.

+ Bloat will be avoided where possible.

### Logging

Any IFObject based type can be handled by the log functions.
IFLogMessage is provided for logging of messages. IFObject based types 
support redirection to a log target, which may be any IFObject based type. 
Several message levels are supported by the standard implementation.

### Signals

IFObject and derived types can emit signals if an interesting event 
occurs (such as an ID change). Event types are derived from IFObjectEvent, 
which provides information on the source of the event and the event type.
A wrapper class (IFSignal) is provided to pass references to signals around 
to code which does not understand details of the implementation of the signal 
system. A signal proxy class (IFObjectSignalProxy) is provided to allow
implementation of signal handlers whithout knowledge of the implementation 
of the signal system. A function is provided to create and initialize an 
event of a specific type (the event can be destroyed using removeLocalRef()).

### Serialization

IFObject and derived types may provide an implementation for 
a serialize() function to obtain the data in the object and a deserialize() 
function to initialize the object from a serialized representation. A 
literal for any complex (i.e. not simple) IFObject based type may be 
obtained by concatenating the string representation followed by a prefix 
and the serialzed representation. The serialized representation may be 
encoded as a base64 string. This is indicated by the prefix.

### Threading

IFThread and IFMutex types are provided for basic support of 
multi-threaded applications.

### Operations

Operations may be performed on an IFObject derived type using 
other IFObject derived types as parameters and returning an arbitrary 
number of objects as result. A single doOp() function is provided as an 
interface for invoking any operation. Implementation of operations is 
supported using the class templates. Information about supported operations 
can be obtained from the IFClassInfo instance.

#ifndef __MESSAGE_H
#define __MESSAGE_H

#include <cassert>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/wrapper.hpp>

#ifdef REMOTE_XML
  #include <boost/serialization/nvp.hpp>
#endif //REMOTE_XML

//
// when you get BOOST_STATIC_ASSERT compile time errors
// consult: http://www.boost.org/libs/serialization/doc/rationale.html#trap
//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define REMOTE_MESSAGING_BEGIN_BASE(x)	friend class boost::serialization::access; \
					template<class Archive> \
					void serialize(Archive& x, const unsigned int version) \
					{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define REMOTE_MESSAGING_BEGIN(x,y)	friend class boost::serialization::access; \
					template<class Archive> \
					void serialize(Archive& y, const unsigned int version) \
					{ \
						y & boost::serialization::base_object<Message>(*this);

// #define REMOTE_MESSAGING_BEGIN(x,y)	friend class boost::serialization::access; \
// 					template<class Archive> \
// 					void serialize(Archive& y, const unsigned int version) \
// 					{ \
// 						boost::serialization::base_object<Message>(*this); \
// 						boost::serialization::void_cast_register<x, Message> ();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define REMOTE_MESSAGING_END		}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Message {
	friend class RemoteMessagingSystem;
public:

	Message(){
		m_kind = MESSAGE_KIND_REPLY; // reply message is the standard
		m_fromRemote = false;
	}

	virtual ~Message(){
	}

	typedef enum _MESSAGE_TYPE {
		MESSAGE_TYPE_INVALID_FIRST,

		MESSAGE_TYPE_ALERT,
		MESSAGE_TYPE_ADDRESS_DISTRIBUTION,
		MESSAGE_TYPE_AGGREGATE_WATCH_VALUES,
		MESSAGE_TYPE_TIMER,
		MESSAGE_TYPE_AGGREGATE_LAST_SUSPICIOUS,
		MESSAGE_TYPE_AGGREGATE_INTERVAL_VALUES,
		MESSAGE_TYPE_ANOMALY_TYPE,

		MESSAGE_TYPE_INVALID_LAST,
	} MESSAGE_TYPE;

	//
	// this virtual function is highly required for the remote messaging to work!
	// boost::serialization only serializes inherited classes through a base-class pointer
	// if the class is polymorphic! See Boost::Serialization reference
	// Reference -> Serialization Conecpt -> Pointers -> Pointers to Objects of Derived Classes
	// 
	// "The relevant section in the docs states the following:
	//  It turns out that the kind of object serialized depends upon 
	//  whether the base class (base in this case) is polymophic or 
	//  not. If base is not polymorphic, that is if it has no virtual 
	//  functions, then an object of the type base will be serialized. 
	//  Information in any derived classes will be lost. If this is 
	//  what is desired (it usually isn't) then no other effort is required."
	// 

	virtual MESSAGE_TYPE getType () = 0;

	typedef enum _MESSAGE_KIND {
		MESSAGE_KIND_REQUEST,
		MESSAGE_KIND_REPLY,
	} MESSAGE_KIND;

	MESSAGE_KIND getKind(){
		return m_kind;
	}

	void setKind( MESSAGE_KIND kind ){
		m_kind = kind;
	}

	bool isRequest(){
		return ( m_kind == MESSAGE_KIND_REQUEST );
	}

	bool isReply(){
		return ( m_kind == MESSAGE_KIND_REPLY );
	}

	bool isFromRemote() {
		return m_fromRemote;
	}

private:

	MESSAGE_KIND m_kind; // request or reply message
	bool m_fromRemote; // does the message originate from a remote system?

	REMOTE_MESSAGING_BEGIN_BASE(remote)
		MESSAGE_TYPE type = getType ();
#ifdef REMOTE_XML
		remote & boost::serialization::make_nvp("Nachrichtentyp", type);
		remote & boost::serialization::make_nvp("Nachrichtenart", m_kind);
		remote & boost::serialization::make_nvp("Sender", m_fromRemote);
#else
		remote & type;
		remote & m_kind;
		remote & m_fromRemote;
#endif //REMOTE_XML
	REMOTE_MESSAGING_END

};

#ifdef REMOTE_XML
	BOOST_CLASS_IS_WRAPPER(const Message);
	BOOST_CLASS_IS_WRAPPER(Message*);
	BOOST_CLASS_IS_WRAPPER(Message* const);
	BOOST_CLASS_IS_WRAPPER(Message);
#endif

#endif // __MESSAGE_H

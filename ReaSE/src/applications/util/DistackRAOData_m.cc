//
// Generated file, do not edit! Created by opp_msgc 4.1 from applications/util/DistackRAOData.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "DistackRAOData_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(DistackRAOData);

DistackRAOData::DistackRAOData(const char *name, int kind) : cPacket(name,kind)
{
    this->requesterPort_var = 0;
    this->id_var = 0;
}

DistackRAOData::DistackRAOData(const DistackRAOData& other) : cPacket()
{
    setName(other.getName());
    operator=(other);
}

DistackRAOData::~DistackRAOData()
{
}

DistackRAOData& DistackRAOData::operator=(const DistackRAOData& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    this->requester_var = other.requester_var;
    this->target_var = other.target_var;
    this->requesterPort_var = other.requesterPort_var;
    this->id_var = other.id_var;
    return *this;
}

void DistackRAOData::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->requester_var);
    doPacking(b,this->target_var);
    doPacking(b,this->requesterPort_var);
    doPacking(b,this->id_var);
}

void DistackRAOData::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->requester_var);
    doUnpacking(b,this->target_var);
    doUnpacking(b,this->requesterPort_var);
    doUnpacking(b,this->id_var);
}

IPvXAddress& DistackRAOData::getRequester()
{
    return requester_var;
}

void DistackRAOData::setRequester(const IPvXAddress& requester_var)
{
    this->requester_var = requester_var;
}

IPvXAddress& DistackRAOData::getTarget()
{
    return target_var;
}

void DistackRAOData::setTarget(const IPvXAddress& target_var)
{
    this->target_var = target_var;
}

int DistackRAOData::getRequesterPort() const
{
    return requesterPort_var;
}

void DistackRAOData::setRequesterPort(int requesterPort_var)
{
    this->requesterPort_var = requesterPort_var;
}

int DistackRAOData::getId() const
{
    return id_var;
}

void DistackRAOData::setId(int id_var)
{
    this->id_var = id_var;
}

class DistackRAODataDescriptor : public cClassDescriptor
{
  public:
    DistackRAODataDescriptor();
    virtual ~DistackRAODataDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(DistackRAODataDescriptor);

DistackRAODataDescriptor::DistackRAODataDescriptor() : cClassDescriptor("DistackRAOData", "cPacket")
{
}

DistackRAODataDescriptor::~DistackRAODataDescriptor()
{
}

bool DistackRAODataDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DistackRAOData *>(obj)!=NULL;
}

const char *DistackRAODataDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DistackRAODataDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int DistackRAODataDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *DistackRAODataDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "requester",
        "target",
        "requesterPort",
        "id",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int DistackRAODataDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "requester")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "target")==0) return base+1;
    if (fieldName[0]=='r' && strcmp(fieldName, "requesterPort")==0) return base+2;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DistackRAODataDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "IPvXAddress",
        "IPvXAddress",
        "int",
        "int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *DistackRAODataDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int DistackRAODataDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DistackRAOData *pp = (DistackRAOData *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DistackRAODataDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DistackRAOData *pp = (DistackRAOData *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getRequester(); return out.str();}
        case 1: {std::stringstream out; out << pp->getTarget(); return out.str();}
        case 2: return long2string(pp->getRequesterPort());
        case 3: return long2string(pp->getId());
        default: return "";
    }
}

bool DistackRAODataDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DistackRAOData *pp = (DistackRAOData *)object; (void)pp;
    switch (field) {
        case 2: pp->setRequesterPort(string2long(value)); return true;
        case 3: pp->setId(string2long(value)); return true;
        default: return false;
    }
}

const char *DistackRAODataDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "IPvXAddress",
        "IPvXAddress",
        NULL,
        NULL,
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
}

void *DistackRAODataDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DistackRAOData *pp = (DistackRAOData *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getRequester()); break;
        case 1: return (void *)(&pp->getTarget()); break;
        default: return NULL;
    }
}



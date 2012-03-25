//
// Generated file, do not edit! Created by opp_msgc 4.1 from applications/util/DistackRemoteTCPPayload.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "DistackRemoteTCPPayload_m.h"

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




Register_Class(DistackRemoteTCPPayload);

DistackRemoteTCPPayload::DistackRemoteTCPPayload(const char *name, int kind) : cPacket(name,kind)
{
    header_arraysize = 0;
    this->header_var = 0;
    data_arraysize = 0;
    this->data_var = 0;
    this->xml_var = 0;
}

DistackRemoteTCPPayload::DistackRemoteTCPPayload(const DistackRemoteTCPPayload& other) : cPacket()
{
    setName(other.getName());
    header_arraysize = 0;
    this->header_var = 0;
    data_arraysize = 0;
    this->data_var = 0;
    operator=(other);
}

DistackRemoteTCPPayload::~DistackRemoteTCPPayload()
{
    delete [] header_var;
    delete [] data_var;
}

DistackRemoteTCPPayload& DistackRemoteTCPPayload::operator=(const DistackRemoteTCPPayload& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    delete [] this->header_var;
    this->header_var = (other.header_arraysize==0) ? NULL : new char[other.header_arraysize];
    header_arraysize = other.header_arraysize;
    for (unsigned int i=0; i<header_arraysize; i++)
        this->header_var[i] = other.header_var[i];
    delete [] this->data_var;
    this->data_var = (other.data_arraysize==0) ? NULL : new char[other.data_arraysize];
    data_arraysize = other.data_arraysize;
    for (unsigned int i=0; i<data_arraysize; i++)
        this->data_var[i] = other.data_var[i];
    this->xml_var = other.xml_var;
    return *this;
}

void DistackRemoteTCPPayload::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    b->pack(header_arraysize);
    doPacking(b,this->header_var,header_arraysize);
    b->pack(data_arraysize);
    doPacking(b,this->data_var,data_arraysize);
    doPacking(b,this->xml_var);
}

void DistackRemoteTCPPayload::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    delete [] this->header_var;
    b->unpack(header_arraysize);
    if (header_arraysize==0) {
        this->header_var = 0;
    } else {
        this->header_var = new char[header_arraysize];
        doUnpacking(b,this->header_var,header_arraysize);
    }
    delete [] this->data_var;
    b->unpack(data_arraysize);
    if (data_arraysize==0) {
        this->data_var = 0;
    } else {
        this->data_var = new char[data_arraysize];
        doUnpacking(b,this->data_var,data_arraysize);
    }
    doUnpacking(b,this->xml_var);
}

void DistackRemoteTCPPayload::setHeaderArraySize(unsigned int size)
{
    char *header_var2 = (size==0) ? NULL : new char[size];
    unsigned int sz = header_arraysize < size ? header_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        header_var2[i] = this->header_var[i];
    for (unsigned int i=sz; i<size; i++)
        header_var2[i] = 0;
    header_arraysize = size;
    delete [] this->header_var;
    this->header_var = header_var2;
}

unsigned int DistackRemoteTCPPayload::getHeaderArraySize() const
{
    return header_arraysize;
}

char DistackRemoteTCPPayload::getHeader(unsigned int k) const
{
    if (k>=header_arraysize) throw cRuntimeError("Array of size %d indexed by %d", header_arraysize, k);
    return header_var[k];
}

void DistackRemoteTCPPayload::setHeader(unsigned int k, char header_var)
{
    if (k>=header_arraysize) throw cRuntimeError("Array of size %d indexed by %d", header_arraysize, k);
    this->header_var[k]=header_var;
}

void DistackRemoteTCPPayload::setDataArraySize(unsigned int size)
{
    char *data_var2 = (size==0) ? NULL : new char[size];
    unsigned int sz = data_arraysize < size ? data_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        data_var2[i] = this->data_var[i];
    for (unsigned int i=sz; i<size; i++)
        data_var2[i] = 0;
    data_arraysize = size;
    delete [] this->data_var;
    this->data_var = data_var2;
}

unsigned int DistackRemoteTCPPayload::getDataArraySize() const
{
    return data_arraysize;
}

char DistackRemoteTCPPayload::getData(unsigned int k) const
{
    if (k>=data_arraysize) throw cRuntimeError("Array of size %d indexed by %d", data_arraysize, k);
    return data_var[k];
}

void DistackRemoteTCPPayload::setData(unsigned int k, char data_var)
{
    if (k>=data_arraysize) throw cRuntimeError("Array of size %d indexed by %d", data_arraysize, k);
    this->data_var[k]=data_var;
}

bool DistackRemoteTCPPayload::getXml() const
{
    return xml_var;
}

void DistackRemoteTCPPayload::setXml(bool xml_var)
{
    this->xml_var = xml_var;
}

class DistackRemoteTCPPayloadDescriptor : public cClassDescriptor
{
  public:
    DistackRemoteTCPPayloadDescriptor();
    virtual ~DistackRemoteTCPPayloadDescriptor();

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

Register_ClassDescriptor(DistackRemoteTCPPayloadDescriptor);

DistackRemoteTCPPayloadDescriptor::DistackRemoteTCPPayloadDescriptor() : cClassDescriptor("DistackRemoteTCPPayload", "cPacket")
{
}

DistackRemoteTCPPayloadDescriptor::~DistackRemoteTCPPayloadDescriptor()
{
}

bool DistackRemoteTCPPayloadDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DistackRemoteTCPPayload *>(obj)!=NULL;
}

const char *DistackRemoteTCPPayloadDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DistackRemoteTCPPayloadDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int DistackRemoteTCPPayloadDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *DistackRemoteTCPPayloadDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "header",
        "data",
        "xml",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int DistackRemoteTCPPayloadDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "header")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "data")==0) return base+1;
    if (fieldName[0]=='x' && strcmp(fieldName, "xml")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DistackRemoteTCPPayloadDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "char",
        "char",
        "bool",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *DistackRemoteTCPPayloadDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int DistackRemoteTCPPayloadDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DistackRemoteTCPPayload *pp = (DistackRemoteTCPPayload *)object; (void)pp;
    switch (field) {
        case 0: return pp->getHeaderArraySize();
        case 1: return pp->getDataArraySize();
        default: return 0;
    }
}

std::string DistackRemoteTCPPayloadDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DistackRemoteTCPPayload *pp = (DistackRemoteTCPPayload *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getHeader(i));
        case 1: return long2string(pp->getData(i));
        case 2: return bool2string(pp->getXml());
        default: return "";
    }
}

bool DistackRemoteTCPPayloadDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DistackRemoteTCPPayload *pp = (DistackRemoteTCPPayload *)object; (void)pp;
    switch (field) {
        case 0: pp->setHeader(i,string2long(value)); return true;
        case 1: pp->setData(i,string2long(value)); return true;
        case 2: pp->setXml(string2bool(value)); return true;
        default: return false;
    }
}

const char *DistackRemoteTCPPayloadDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *DistackRemoteTCPPayloadDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DistackRemoteTCPPayload *pp = (DistackRemoteTCPPayload *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}



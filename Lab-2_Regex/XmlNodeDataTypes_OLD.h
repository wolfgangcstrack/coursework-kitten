/*
Lab 2 - Regular Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the XmlNodeDataTypes. These structs are
wrappers that inherit from a parent class XmlDataType in order to emulate
dynamic typing in the XmlNode and XmlNodeData classes.
*/

#ifndef XML_NODE_DATA_TYPES_H_
#define XML_NODE_DATA_TYPES_H_

#include <string>

/*
Note: the operator overloads for the operator* are used in practice to
"unwrap" the wrapper class, returning the actual data type.
*/

struct XmlNodeDataType {};

struct Boolean : public XmlNodeDataType
{
	bool data;
	Boolean(bool pData) { data = pData; }
	bool operator*() { return data; }
};

struct XS_Short : public XmlNodeDataType
{
	short data;
	XS_Short(short pData) { data = pData; }
	short operator*() { return data; }
};

struct UnsignedShort : public XmlNodeDataType
{
	unsigned short data;
	UnsignedShort(unsigned short pData) { data = pData; }
	unsigned short operator*() { return data; }
};

struct XS_Long : public XmlNodeDataType
{
	long data;
	XS_Long(long pData) { data = pData; }
	long operator*() { return data; }
};

struct UnsignedLong : public XmlNodeDataType
{
	unsigned long data;
	UnsignedLong(unsigned long pData) { data = pData; }
	unsigned long operator*() { return data; }
};

struct XS_Float : public XmlNodeDataType
{
	float data;
	XS_Float(float pData) { data = pData; }
	float operator*() { return data; }
};

struct String : public XmlNodeDataType
{
	std::string data;
	String(const std::string &pData) { data = pData; }
	std::string & operator*() { return data; }
};

#endif // XML_NODE_DATA_TYPES_H_
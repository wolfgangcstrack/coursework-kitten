/*
Lab 2 - Regular Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file has the class definitions for the XML nodes arbitrarily
chosen for this lab.
*/

#ifndef _XML_NODE_H
#define _XML_NODE_H

#include <string>
#include <vector>
using namespace std;

typedef unsigned short ushort;
typedef unsigned long ulong;

class XmlNode
{
protected:
	string xmlTags;
public:
	// constructors and destructor
	XmlNode() {}
	XmlNode(const string &tags) { xmlTags = tags; }
	virtual ~XmlNode() {}
	// getter
	const string & getXMLTags() const { return xmlTags; }
	// setter
	void setXMLTags(const string &newTags) { xmlTags = newTags; }
	// other methods
	virtual void readData(const string &unParsedData) = 0;
};

class PaperSize : public XmlNode
{
private:
	ushort paperSpecification;
	string standardName;
	string orientation;
	ulong width;
	ulong height;
public:
	// constructors and destructor
	PaperSize() { paperSpecification = width = height = 0; } // assign default values to primitive types
	PaperSize(ushort pSpec, string sName, string orient, ulong w, ulong h)
	{
		paperSpecification = pSpec;
		standardName = sName;
		orientation = orient;
		width = w;
		height = h;
	}
	~PaperSize() {}
	// getters
	ushort getPaperSpecification() { return paperSpecification; }
	const string & getStandardName() { return standardName; }
	const string & getOrientation() { return orientation; }
	ulong getWidth() { return width; }
	ulong getHeight() { return height; }
	// setters
	void setPaperSpecification(ushort pSpec) { paperSpecification = pSpec; }
	void setStandardName(const string &sName) { standardName = sName; }
	void setOrientation(const string &orient) { orientation = orient; }
	void setWidth(ulong w) { width = w; }
	void setHeight(ulong h) { height = h; }
};

class DetectObject : public XmlNode
{
private:
	ushort separationPaper;
	ushort patchCodePaper;
	ushort patchCodeDirection;
	ushort deviceOperation;
public:
	// constructors and destructor
	DetectObject() { separationPaper = patchCodePaper = patchCodeDirection = deviceOperation = 0; }
	DetectObject(ushort sPaper, ushort pCP, ushort pCD, ushort devOp)
	{
		separationPaper = sPaper;
		patchCodePaper = pCP;
		patchCodeDirection = pCD;
		deviceOperation = devOp;
	}
	~DetectObject() {}
	// getters
	ushort getSeparationPaper() { return separationPaper; }
	ushort getPatchCodePaper() { return patchCodePaper; }
	ushort getPatchCodeDirection() { return patchCodeDirection; }
	ushort getDeviceOperation() { return deviceOperation; }
	// setters
	void setSeparationPaper(ushort sPaper) { separationPaper = sPaper; }
	void setPatchCodePaper(ushort pCP) { patchCodePaper = pCP; }
	void setPatchCodeDirection(ushort pCD) { patchCodeDirection = pCD; }
	void setDeviceOperation(ushort devOp) { deviceOperation = devOp; }
};

class PatchCodeNotification : public XmlNode
{
private:
	bool enable;
	ushort type;
	ushort direction;
	bool checkDigit;
public:
	// constructors and destructor
	PatchCodeNotification() { enable = type = direction = checkDigit = 0; }
	PatchCodeNotification(bool e, ushort t, ushort dir, bool cDig)
	{
		enable = e;
		type = t;
		direction = dir;
		checkDigit = cDig;
	}
	~PatchCodeNotification() {}
	// getters
	bool getEnable() { return enable; }
	ushort getType() { return type; }
	ushort getDirection() { return direction; }
	bool getCheckDigit() { return checkDigit; }
};

#endif // _XML_NODE_H
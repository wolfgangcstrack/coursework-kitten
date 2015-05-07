/*
Lab 2 - Regular Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This header file has the class definitions for the XML nodes arbitrarily
chosen for this lab.
*/

#ifndef _XML_NODE_H
#define _XML_NODE_H

#include <regex>
#include <string>
#include <vector>
using namespace std;

typedef unsigned short ushort;
typedef unsigned long ulong;

class XmlNode
{
protected:
	string xmlTags;

	long get_ulong(const string &data, regex rx)
	{
		auto match = sregex_iterator(data.begin(), data.end(), regex("<UpperLeftX>[0-9]*"));
		string temp = match->str();
		return stol((sregex_iterator(temp.begin(), temp.end(), regex("[0-9]+"))->str()));
	}

	string getString(const string &data, regex rx)
	{
		auto match = sregex_iterator(data.begin(), data.end(), rx);
		string temp = match->str();
		string pTemp = "";
		for (int i = temp.find('>'); i < temp.length(); i++)
		{
			if (temp[i] == '<')
				break;
			pTemp += temp[i];
		}

		return pTemp;
	}

	bool getBoolean(const string &data, regex rx)
	{
		auto match = sregex_iterator(data.begin(), data.end(), rx);
		string temp = match->str();
		return (temp.find("true") > -1 ? true : false);
	}
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
	virtual void readData(const string &data) = 0;
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
	ushort getPaperSpecification() const { return paperSpecification; }
	const string & getStandardName() const { return standardName; }
	const string & getOrientation() const { return orientation; }
	ulong getWidth() const { return width; }
	ulong getHeight() const { return height; }
	// setters
	void setPaperSpecification(ushort pSpec) { paperSpecification = pSpec; }
	void setStandardName(const string &sName) { standardName = sName; }
	void setOrientation(const string &orient) { orientation = orient; }
	void setWidth(ulong w) { width = w; }
	void setHeight(ulong h) { height = h; }
	// other methods
	void readData(const string &data);
};

void PaperSize::readData(const string &data)
{
	setPaperSpecification(get_ulong(data, regex("<PaperSpecification>[0-9]*")));
	setStandardName(getString(data, regex("<StandardName>.*?</StandardName>")));
	setOrientation(getString(data, regex("<Orientation>.*?</Orientation>")));
	setWidth(get_ulong(data, regex("<Width>[0-9]*")));
	setHeight(get_ulong(data, regex("<Height>[0-9]*")));
}

class Area : public XmlNode
{
private:
	ulong upperLeftX;
	ulong upperLeftY;
	ulong width;
	ulong height;
	ulong supportedScanAreaType;
public:
	// constructors and destructor
	Area() { upperLeftX = upperLeftY = width = height = supportedScanAreaType = 0; }
	Area(ulong ulx, ulong uly, ulong w, ulong h, ulong sSAT)
	{
		upperLeftX = ulx;
		upperLeftY = uly;
		width = w;
		height = h;
		supportedScanAreaType = sSAT;
	}
	// getters
	ulong getUpperLeftX() const { return upperLeftX; }
	ulong getUpperLeftY() const { return upperLeftY; }
	ulong getWidth() const { return width; }
	ulong getHeight() const { return height; }
	ulong getSupportedScanAreaType() const { return supportedScanAreaType; }
	// setters
	void setUpperLeftX(ulong ulx) { upperLeftX = ulx; }
	void setUpperLeftY(ulong uly) { upperLeftY = uly; }
	void setWidth(ulong w) { width = w; }
	void setHeight(ulong h) { height = h; }
	void setSupportedScanAreaType(ulong sSAT) { supportedScanAreaType = sSAT; }
	// other methods
	void readData(const string &data);
};

void Area::readData(const string &data)
{
	setUpperLeftX(get_ulong(data, regex("<UpperLeftX>[0-9]*")));
	setUpperLeftY(get_ulong(data, regex("<UpperLeftY>[0-9]*")));
	setWidth(get_ulong(data, regex("<Width>[0-9]*")));
	setHeight(get_ulong(data, regex("<Height>[0-9]*")));
	setSupportedScanAreaType(get_ulong(data, regex("<SupportedScanAreaType>[0-9]*")));
}

class PatchCodeNotification : public XmlNode
{
private:
	bool enable;
	ushort type;
	ushort direction;
public:
	// constructors and destructor
	PatchCodeNotification() { enable = type = direction = 0; }
	PatchCodeNotification(bool e, ushort t, ushort dir)
	{
		enable = e;
		type = t;
		direction = dir;
	}
	~PatchCodeNotification() {}
	// getters
	bool getEnable() const { return enable; }
	ushort getType() const { return type; }
	ushort getDirection() const { return direction; }
	// setters
	void setEnable(bool e) { enable = e; }
	void setType(ushort t) { type = t; }
	void setDirection(ushort dir) { direction = dir; }
	// other methods
	void readData(const string &data);
};

void PatchCodeNotification::readData(const string &data)
{
	setEnable(getBoolean(data, regex("<Enable>.*?</Enable>")));
	setType(get_ulong(data, regex("<Type>[0-9]*")));
	setDirection(get_ulong(data, regex("<Direction>[0-9]*")));
}

#endif // _XML_NODE_H
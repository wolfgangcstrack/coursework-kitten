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
	string className;
	string xmlTags;

	long get_ulong(const string &data, regex rx)
	{
		auto match = sregex_iterator(data.begin(), data.end(), rx);
		string temp = match->str();
		return stol((sregex_iterator(temp.begin(), temp.end(), regex("[0-9]+"))->str()));
	}

	string getString(const string &data, regex rx)
	{
		auto match = sregex_iterator(data.begin(), data.end(), rx);
		string temp = match->str();
		string pTemp = "";
		for (int i = temp.find('>') + 1; i < temp.length(); i++)
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
	const string & getClassName() const { return className; }
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
	PaperSize() { className = "PaperSize"; paperSpecification = width = height = 0; } // assign default values to primitive types
	PaperSize(ushort pSpec, string sName, string orient, ulong w, ulong h)
	{
		className = "PaperSize";
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
	friend ostream & operator<<(ostream &os, const PaperSize &node)
	{
		os << node.className << endl
			<< "\t" << "unsignedShort PaperSpecification = " << node.paperSpecification << endl
			<< "\t" << "string StandardName = " << node.standardName << endl
			<< "\t" << "string Orientation = " << node.orientation << endl
			<< "\t" << "unsignedLong Width = " << node.width << endl
			<< "\t" << "unsignedLong Height = " << node.height << endl;
		return os;
	}
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
	Area() { className = "Area"; upperLeftX = upperLeftY = width = height = supportedScanAreaType = 0; }
	Area(ulong ulx, ulong uly, ulong w, ulong h, ulong sSAT)
	{
		className = "Area";
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
	friend ostream & operator<<(ostream &os, const Area &node)
	{
		os << node.className << endl
			<< "\t" << "unsignedLong UpperLeftX = " << node.upperLeftX << endl
			<< "\t" << "unsignedLong UpperLeftY = " << node.upperLeftY << endl
			<< "\t" << "unsignedLong Width = " << node.width << endl
			<< "\t" << "unsignedLong Height = " << node.height << endl
			<< "\t" << "unsignedLong SupportedScanAreaType = " << node.supportedScanAreaType << endl;
		return os;
	}
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
	PatchCodeNotification() { className = "PatchCodeNotification"; enable = type = direction = 0; }
	PatchCodeNotification(bool e, ushort t, ushort dir)
	{
		className = "PatchCodeNotification";
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
	friend ostream & operator<<(ostream &os, const PatchCodeNotification &node)
	{
		os << node.className << endl
			<< "\t" << "boolean Enable = " << (node.enable ? "true" : "false") << endl
			<< "\t" << "unsignedShort Type = " << node.type << endl
			<< "\t" << "unsignedShort Direction = " << node.direction << endl;
		return os;
	}
};

void PatchCodeNotification::readData(const string &data)
{
	setEnable(getBoolean(data, regex("<Enable>.*?</Enable>")));
	setType(get_ulong(data, regex("<Type>[0-9]*")));
	setDirection(get_ulong(data, regex("<Direction>[0-9]*")));
}

#endif // _XML_NODE_H
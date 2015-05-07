/*
Lab 2 - Regular Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the main application for testing Lab 2. Note: Execution results
appended to the end of this file in a block comment.
*/

#include "XmlNode.h"
#include "NodeList.h"
#include "XmlRegexIO.h"
#include <iostream>
using namespace std;

void populateList(NodeList &nlist)
{
	XmlRegexIO xmlRIO;
	string filename = "ScanParams.xml";
	string dataFilename = "ScanParamsData.xml";

	XmlNode *paperSize = new PaperSize();
	XmlNode *area = new Area();
	XmlNode *patchCodeNotification = new PatchCodeNotification();

	xmlRIO.setPattern("<element name=\"PaperSize\"\\s*>");
	xmlRIO.getXmlTags(filename, *paperSize);
	xmlRIO.setPattern("<[/]*PaperSize>");
	xmlRIO.getXmlData(dataFilename, *paperSize);

	xmlRIO.setPattern("<element name=\"Area\"\\s*>");
	xmlRIO.getXmlTags(filename, *area);
	xmlRIO.setPattern("<[/]*Area>");
	xmlRIO.getXmlData(dataFilename, *area);

	xmlRIO.setPattern("<element name=\"PatchCodeNotification\".*>");
	xmlRIO.getXmlTags(filename, *patchCodeNotification);
	xmlRIO.setPattern("<[/]*PatchCodeNotification>");
	xmlRIO.getXmlData(dataFilename, *patchCodeNotification);

	nlist.push_back(paperSize);
	nlist.push_back(area);
	nlist.push_back(patchCodeNotification);
}

int main()
{
	cout << "This is a demonstration of Lab 2's XML parser for the PaperSize, Area, and PatchCodeNotification elements.\n\n";
	NodeList nlist;
	populateList(nlist);

	cout << "XML DATA EXTRACTED:\n\n";
	for (int i = 0; i < nlist.size(); i++)
		cout << nlist[i]->getXMLTags() << endl;

	cout << "\n\nPARSED DATA:\n\n";
	cout << *(dynamic_cast<PaperSize *>(nlist[0])) << endl;
	cout << *(dynamic_cast<Area *>(nlist[1])) << endl;
	cout << *(dynamic_cast<PatchCodeNotification *>(nlist[2])) << endl;

	return 0;
}

/* EXECUTION RESULTS
This is a demonstration of Lab 2's XML parser for the PaperSize, Area, and PatchCodeNotification elements.

XML DATA EXTRACTED:

<element name="PaperSize" >
<complexType>
<all>
<element name="PaperSpecification"  type="unsignedShort" />
<element name="StandardName"  type="string" />
<element name="Orientation"  type="string" />
<element name="Width"  type="unsignedLong" />
<element name="Height"  type="unsignedLong" />
</all>
</complexType>
</element>
<element name="Area"  >
<complexType>
<all>
<element name="UpperLeftX"  type="unsignedLong" />
<element name="UpperLeftY"  type="unsignedLong" />
<element name="Width"  type="unsignedLong" />
<element name="Height"  type="unsignedLong" />
<element name="SupportedScanAreaType"  type="unsignedLong" />
</all>
</complexType>
</element>
<element name="PatchCodeNotification"  minOccurs="1" maxOccurs="1" >
<complexType>
<all>
<element name="Enable"  type="xs:boolean" />
<element name="Type"  type="unsignedShort" />
<element name="Direction"  type="unsignedShort" />
</all>
</complexType>
</element>


PARSED DATA:

PaperSize
unsignedShort PaperSpecification = 4
string StandardName = Scanner'sMaximum
string Orientation = Portrait
unsignedLong Width = 14400
unsignedLong Height = 258000

Area
unsignedLong UpperLeftX = 0
unsignedLong UpperLeftY = 0
unsignedLong Width = 14400
unsignedLong Height = 21600
unsignedLong SupportedScanAreaType = 0

PatchCodeNotification
boolean Enable = false
unsignedShort Type = 63
unsignedShort Direction = 6

Press any key to continue . . .
*/
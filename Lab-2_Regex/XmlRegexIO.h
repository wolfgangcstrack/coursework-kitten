/*
Lab 2 - Regular Expressions
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the header file for the XmlRegexIO class. This class extends the
RegexIO class and can instantiate XmlNodes along with its parent class
functionality.
*/

#ifndef XML_REGEX_IO_H_
#define XML_REGEX_IO_H_

#include "RegexIO.h"
#include "XmlNode.h"

class XmlRegexIO : public RegexIO
{
public:
	// constructors and destructor
	XmlRegexIO() {}
	XmlRegexIO(const XmlRegexIO &xRIO) : RegexIO(xRIO) {}
	XmlRegexIO(const std::string &patt) : RegexIO(patt) {}
	~XmlRegexIO() {}
	// other methods
	bool getXmlNodeFromFile(const std::string &filename, XmlNode &store);
};

// instantiates an XmlNode whose fields are grabbed from the file <filename>
// based on this XmlRegexIO's pattern/regex member variable
bool XmlRegexIO::getXmlNodeFromFile(const std::string &filename, XmlNode &store)
{
	if (!fileHasMatch(filename))
		return false;

	XmlNode result;
	std::ifstream ifs;
	ifs.open(filename);

	std::string line;
	std::string temp = "";
	while (getline(ifs, line))
	{
		if (std::regex_search(line, rex)) // Found opening tag
		{
			// get className of XmlNode
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] != ' ' || line[i] != '<' || line[i] != '>')
					temp += line[i];
			}
			result.setClassName(line);

			// read data and child nodes until closing tag is reached
			getline(ifs, line);
			while (!std::regex_search(line, rex))
			{
				// if the next line is data
				if (std::regex_search(line, regex("/\\w?>")))
				{
					std::string tempName = "";
					std::string tempValue = "";
					int i;

					for (i = 0; line[i] != '>'; i++) // get name of data
					{
						if (line[i] != ' ' || line[i] != '<')
							tempName += line[i];
					}

					for (++i; line[i] != '<'; i++) // get value of data
					{
						tempValue += line[i];
					}

					// add data to parent node
					result.addData(tempName, tempValue);
				}
				else // if the next line is a child node
				{
					XmlNode child;
					if (getXmlNodeFromFile(filename, child)) // recursive call to get child node
						result.addChildNode(child);
				}

				getline(ifs, line);
			}
		}

		break; // breaks out of while loop for reading the entire file
	}

	return true;
}

#endif // XML_REGEX_IO_H_
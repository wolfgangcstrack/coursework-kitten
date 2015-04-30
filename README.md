# CIS29-Lab2-Regex
CIS29 Spring Quarter 2015 - Lab 2, Regular Expressions
## Assignment Description
* Design a class to hold XML node data.
* Design a class based on one STL Container (i.e. Vector, Deque, List) to support a list of Nodes.
* Design a utility class to handle RegularExpression functionality.
* Examine the XML Schema data file and Select three of the XML nodes. 
* The selected nodes must contain 3 or more data members.
* One node must contain a child XML node.
* Extract the data for the node from the XML file using your RegularExpression utility class.
* Assign the data to your node class object based on the ScanSchemaData.xml file.
* Store the XML node in your NodeList class.
* Display the NodeList data.
* Do not use any arrays.

 

Data File:

Extensible Markup Language (XML) is a markup language that defines a set of rules for encoding documents in a format which is both human-readable and machine-readable.  The ScanParams.XML file consists of XML nodes and the data associated with the node.  Here is an excerpt starting at line #58:

 

              <element name="Resolution"  >

                <complexType>

                  <all>

                    <element name="X"  type="unsignedLong" />

                    <element name="Y"  type="unsignedLong" />

                  </all>

                </complexType>

              </element>

                                            

The class name is:  Resolution.

The data is two unsigned long values of X and Y.

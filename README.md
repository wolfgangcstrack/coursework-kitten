# CIS29-Lab6-STL-algorithms
CIS29 Spring Quarter 2015 - Lab 6, STL containers and algorithms

## Purpose
Effectively use Class Design, STL Containers and Algorithms

### Data Files
Barcodes.txt, Patient.xml

### Description
This lab focuses on using STL containers and algorithms to store, sort, search and find specific data.  

The Patient data is in this form:

Encrypted Barcode:<br>
5534

Patient xml node:<br>
\<patient><br>
\<name>oxford,tan\</name><br>
\<age>56\</age><br>
\<gender>f\</gender><br>
\<bloodtype>ab\</bloodtype><br>
\<maritalstatus>single\</maritalstatus><br>
\<income>26282\</income><br>
\<dependents>4\</dependents><br>
\</patient><br>

The Barcode data is in this form, and represents a Simulated Barcode:

111101100101100<br>
110000101010011<br>
000100011111010<br>

The Simulated Barcode data is encrypted Binary Data and the Encrypted Barcode is the binary data converted to decimal:

111101100101100 = 31532<br>
110000101010011 = 24915<br>
000100011111010 = 2298<br>

#### Part 1
Select the appropriate container to hold the patient xml date.  Note that the patient data is not in exact xml.  Each xml node is separated by an Encrypted Barcode.  

#### Part 2
The barcode text is a list of Binary barcodes.  Use the barcodes in this list to lookup the patient data in the container defined in part #1. The binary barcode requires conversion to decimal to do the lookup of the patient data.

#### Part 3
Put timer's in your solution. The best lookup time in the class will receive special recognition.

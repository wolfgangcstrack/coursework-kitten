/*
Lab 1 - Bitsets and Vectors
Wolfgang C. Strack
Windows 8 Visual C++ 2013

This is the driver application for Lab 1.

NOTE: Execution results included at the end of this file.
*/

#include "Lab1Decryptor.h"
#include "ANSIChar.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// opens input file for reading, returns false if file does not open correctly
bool openBinaryInputFile(ifstream &ifs);
void readANSI(ifstream &ifs, vector<ANSIChar> &acv);

int main()
{
	cout << "This is a demonstration of the Lab1Decryptor." << endl;
	Lab1Decryptor decryptor;
	vector<ANSIChar> acv;
	string decodedResult;

	ifstream ifs;
	if (!openBinaryInputFile(ifs))
	{
		cout << "Error, file not found" << endl;
		return -1;
	}

	readANSI(ifs, acv);
	decryptor.decrypt(acv, decodedResult);

	cout << "The decoded string is:\n\n";
	cout << decodedResult << endl;
	
	return 0;
}

bool openBinaryInputFile(ifstream &ifs)
{
	string filename;
	cout << "Please enter filename to read from: ";
	getline(cin, filename);
	ifs.open(filename, std::ios_base::binary);
	return ifs.is_open();
}

void readANSI(ifstream &ifs, vector<ANSIChar> &acv)
{
	char temp;

	while (ifs.get(temp))
		acv.push_back(ANSIChar(temp));
}

/* EXECUTION RESULTS
This is a demonstration of the Lab1Decryptor.
Please enter filename to read from: Morse.bin
The decoded string is:

M O R S E   C O D E   W A S   I N V E N T E D   B Y   S A M U E L   M O R S E   I N   1 8 4 3 .   T H E   L I N E   R A N   F R O M   W A S H I N G T O N   D . C .
T O   B A L T I M O R E ,   M A R Y L A N D .   T H E   P U R P O S E   O F   T H E   T E L E G R A P H   W A S   T O   P R O V I D E   R A P I D   C O M M U N I C
A T I O N   O F   L O N G   D I S T A N C E S .   T H E   M E T H O D   O F   C O M M U N I C A T I O N   U S E D   I N   T H E   T E L E G R A P H   W A S   M O R S
E   C O D E ,   W H I C H   W A S   A   S E R I E S   O F   D O T S   A N D   D A S H E S   M A D E   U P   O F   E L E C T R I C     C U R R E N T S   B E I N G
A L T E R N A T E D .   T H E   D O T S   A N D   D A S H E S   M A D E   U P   L E T T E R S   W H I C H   C O M B I N E D   T O   F O R M   W O R D S ,   T H E N
S E N T E N C E S ,   A N D   C O M P L E T E   M E S S A G E S ,   E T C .   M O R S E   C O D E   W A S   U S E D   B Y   M A N Y   G O V E R N M E N T   O F F I
C I A L S ,   S U C H   A S   L I N C O L N .   G E N E R A L S   U L Y S S E S   S .   G R A N T   A N D   R O B E R T   E .   L E E   U S E D   M O R S E   C O D E
T O   A I D   I N   T H E I R   C O M M U N I C A T I O N   O P T I O N S   A S   W E L L .   F I V E   M I L L I O N   M O R S E   C O D E   M E S S A G E S   W
E R E   S E N T   A N U A L L Y   S T A R T I N G   A R O U N   1 8 6 0 .   N U M B E R S   A L L   H A V E   A   S E Q U E N C E   O F   F I V E   D O T S   A N D
O R   D A S H E S ,   B U T   L E T T E R S   H A V E   A   D I F F E R E N T   N U M B E R   O F   S Y M B O L S .   A L L   T O G E T H E R ,   T H E R E   A R E
T H I R T Y   S I X   M A I N   C O M B I N A T I O N S   T O   R E M E M B E R   T O   M A K E   M E E S S A G E S .   T E L E G R A P H   O P E R A T E R S   W E
R E   O F F E R E D   A   C L E A N   A N D   S T A B L E   W O R K I N G   E N V I R O N M E N T   S O   T H E Y   M A Y   F O C U S   O N   T H E I R   T A S K .
M O R S E   C O D E   W A S   V E R Y   I M P O R T A N T   T O   H I S T O R Y   B E C A U S E   I T   W A S   O N E   O F   T H E   F I R S T   U S E S   O F   E
N C R I P T E D   M E S S A G E S   B Y   T H E   U . S .   L I N C O L N   U S E D   M O R S E   C O D E   T O   W I N   T H E   C I V I L   W A R ,   W H I C H
A F F E C T E D   T H E   C O U R S E   O F   T H E   W O R L D   S   H I S T O R Y   I N   A   L A R G E   M A G N I T U D E       T   T     T
Press any key to continue . . .
*/
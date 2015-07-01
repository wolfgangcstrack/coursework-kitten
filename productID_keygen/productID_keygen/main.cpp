/* KEY GEN APPLICATION
Use main1 for generating keys all in separate file.
WARNING: DO NOT USE "projectinput_BACKUP.txt" FILE!!!!!
Use main2 for combining files.
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool openInputFile(ifstream &ifs);
bool openOutputFile(ofstream &ofs);
void genKeys(ifstream &ifs, vector<string>& keys);

int main1();
int main2();

int main()
{
	string temp;
	int choice;

	cout << "Enter choice (1 or 2): ";
	getline(cin, temp);

	stringstream filter(temp);
	filter >> choice;

	switch (choice)
	{
	case 1:
		return main1();
	case 2:
		return main2();
	default:
		cout << "No actions for " << choice << endl;
		return 0;
	}
}

int main2()
{
	ifstream keys;
	ifstream input;
	ofstream final_file;

	cout << endl << "Use file with ONLY keys (should be \"projectinput_keys.txt\")" << endl;
	if (!openInputFile(keys)) // print error and exit program if file not found
	{
		cout << "Error, file not found" << endl;
		return -1;
	}
	cout << endl << "Use file with ONLY input without keys (should be \"projectinput.txt\")" << endl;
	if (!openInputFile(input)) // print error and exit program if file not found
	{
		cout << "Error, file not found" << endl;
		return -1;
	}
	cout << endl << "Use final file ONLY (should be \"projectinput_final.txt\")" << endl;
	if (!openOutputFile(final_file))
	{
		cout << "Error, file not found" << endl;
		return -1;
	}

	string lineKeys, lineInput;

	cout << "OUTPUTTED:" << endl;
	while (getline(input, lineInput) && getline(keys, lineKeys))
	{
		if (lineInput == "" && lineKeys == "")
			continue;
		else if (lineInput == "" || lineKeys == "")
		{
			cout << "Both files do not have the same amount of lines!" << endl;
			return -2;
		}

		string finalLine = lineKeys + ":" + lineInput;

		cout << finalLine << endl;
		final_file << finalLine << endl;
	}
}

int main1()
{
	ifstream ifs;
	ofstream ofs;

	cout << endl << "Use file with ONLY input without keys (should be \"projectinput.txt\")" << endl;
	if (!openInputFile(ifs)) // print error and exit program if file not found
	{
		cout << "Error, file not found" << endl;
		return -1;
	}
	cout << endl << "Use file for ONLY keys (should be \"projectinput_keys.txt\")" << endl;
	if (!openOutputFile(ofs))
	{
		cout << "Error, file not found" << endl;
		return -1;
	}

	vector<string> keys;

	genKeys(ifs, keys);
	
	cout << "OUTPUTTED:" << endl;
	for (int i = 0; i < keys.size(); i++)
	{
		cout << keys[i] << endl;
		ofs << keys[i] << endl;
	}

	return 0;
}

void genKeys(ifstream &ifs, vector<string>& keys)
{
	string line, temp;
	string key = "";

	string fields[6];

	string delimiter = ":";

	while (getline(ifs, line))
	{
		if (line.empty()) // skip empty line
			continue;
		key = "B";
		temp = line;
		size_t pos;
		for (int i = 0; i < 5; i++)
		{
			pos = temp.find(delimiter);
			fields[i] = temp.substr(0, pos);
			temp.erase(0, pos + 1);
		}
		fields[5] = temp;

		char tempchar = toupper(fields[5][0]);
		key += tempchar;	// Category
		tempchar = toupper(fields[4][0]);
		key += tempchar;	// Seller
		tempchar = toupper(fields[0][0]);
		key += tempchar;	// Name

		key += "-";

		stringstream ss;
		string newfield3 = "";
		int price = stod(fields[3]);
		if (price > 65535)
		{
			ss << hex << 65535;
			newfield3 = ss.str();
		}
		else
		{
			ss << hex << price;
			for (int i = ss.str().length(); i < 4; i++)
				newfield3 += "0";
			newfield3 += ss.str();
		}
		key += newfield3;							// Price

		key += "-";

		string newfield1 = "";
		int weight = stod(fields[1]);
		while (weight > 1000)
			weight /= 10;

		bool invalid;
		do
		{ // VECTOR INPUT VALIDATION
			invalid = false;

			for (int i = 0; i < keys.size(); i++)
			{
				if (stoi(keys[i].substr(9, 3)) == weight)
				{
					invalid = true;

					if (weight >= 999)
						weight = 0;
					else
						weight++;

					break;
				}
			}
		} while (invalid);
		for (int i = to_string(weight).length(); i < 3; i++)
			newfield1 += "0";
		newfield1 += to_string(weight);
		key += newfield1;							// Weight

		//cout << key << endl;
		keys.push_back(key);
	}
}

bool openInputFile(ifstream &ifs)
{
	string filename;

	cout << "Enter the input filename: ";
	getline(cin, filename);
	ifs.open(filename.c_str());
	return ifs.is_open();
}

bool openOutputFile(ofstream &ofs)
{
	string filename;

	cout << "Enter the output filename: ";
	getline(cin, filename);
	ofs.open(filename.c_str());
	return ofs.is_open();
}
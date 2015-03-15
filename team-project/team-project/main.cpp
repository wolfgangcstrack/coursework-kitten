/*
Manager: Wolfgang C. Strack

To include:
Initialize Data Structures
while loop for menu/possible function
input file function
tests for memory leaks
*/

#include "HashSC.h"
#include "Global.h"

typedef Item* ITEM_PTR;

// Hash function
int HashProductID(const ITEM_PTR &pItem);
// Compare function
int compareProductID(const ITEM_PTR &left, const ITEM_PTR &right);

// Menu Functions
void display_menu();
void add_new_data(vector<ITEM_PTR>*& items, HashSC<ITEM_PTR>*& pHSC);
void delete_data(vector<ITEM_PTR>*& items, HashSC<ITEM_PTR>*& pHSC);
void find_and_display();
void list_HashTable();
void list_Key_Sequence();
void print_indented_tree();
void write_to_file();
void efficiency();

// properly delete dynamically allocated data structures
void DELETE_EVERYTHING(vector<ITEM_PTR>* items, HashSC<ITEM_PTR>* pHSC);

bool openInputFile(ifstream &ifs);
bool openOutputFile(ofstream &ofs);

int main()
{
	vector<ITEM_PTR>* items = new vector<ITEM_PTR>();
	HashSC<ITEM_PTR>* pHSC = new HashSC<ITEM_PTR>(HashProductID, compareProductID);
	int option = -1;

	while (option != 0)
	{
		cout << endl;
		display_menu();
		cout << "Enter an option (1, 2, 3...0): ";
		if (!(cin >> option)) // if input is not an integer
		{
			cout << endl << "\nInvalid option!" << endl;
			cin.clear();	// clear error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
			option = -1;	// reset option
			continue;		// ask for option again
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
		cout << endl;

		switch (option)
		{
		case 1: add_new_data(items, pHSC);	break;
		case 2: delete_data(items, pHSC);	break;
		case 3: find_and_display();			break;
		case 4: list_HashTable();			break;
		case 5: list_Key_Sequence();		break;
		case 6: print_indented_tree();		break;
		case 7: write_to_file();			break;
		case 8: efficiency();				break;
		case 0: cout << "Sayonara" << endl;	break;

		default: cout << option << " is not an option!" << endl;
		}
		cout << endl << endl << endl;
	}

	DELETE_EVERYTHING(items, pHSC);
	cout << (_CrtDumpMemoryLeaks() ? "\nMemory Leak\n" : "\nNo Leak\n");
}

// ---------------------- Hash and Compare Function -----------------------------------------------
int HashProductID(const ITEM_PTR &pItem)
{
	unsigned int k, retVal = 0;

	string key = "";
	key += pItem->getProductID().substr(2, 3);
	key += pItem->getProductID().substr(6, 4);
	key += pItem->getProductID().substr(11, 3);

	for (k = 0; k < key.length(); k++)
		retVal = 37 * retVal + key[k];

	return retVal;
}


int compareProductID(const ITEM_PTR &left, const ITEM_PTR &right)
{
	if (left->getProductID() < right->getProductID())
		return -1;
	if (left->getProductID() > right->getProductID())
		return 1;
	return 0;
}
// ---------------------- Hash and Compare Function End -------------------------------------------

// ---------------------- Menu Functions ----------------------------------------------------------
void display_menu()
{
	int i;
	for (i = 0; i < 50; i++)
		cout << "-";
	cout << endl << left
		<< "|" << " OPTION# " << setw(39) << "ACTION" << "|" << endl
		<< "|";
	for (i = 0; i < 48; i++)
		cout << "-";
	cout << left << "|" << endl
		<< "|" << "    1    " << setw(39) << "Add Items"						<< "|" << endl
		<< "|" << "    2    " << setw(39) << "Delete Items"						<< "|" << endl
		<< "|" << "    3    " << setw(39) << "Find Items"						<< "|" << endl
		<< "|" << "    4    " << setw(39) << "List Items (HashTable Format)"	<< "|" << endl
		<< "|" << "    5    " << setw(39) << "List Items (Sorted Key Format)"	<< "|" << endl
		<< "|" << "    6    " << setw(39) << "Print Indented Tree"				<< "|" << endl
		<< "|" << "    7    " << setw(39) << "Write Data to File"				<< "|" << endl
		<< "|" << "    8    " << setw(39) << "Efficiency"						<< "|" << endl
		<< "|" << "    0    " << setw(39) << "QUIT"								<< "|" << endl;
	for (i = 0; i < 50; i++)
		cout << "-";

	cout << right << endl << endl;
}

void add_new_data(vector<ITEM_PTR>*& items, HashSC<ITEM_PTR>*& pHSC)
{
	ifstream ifs;

	string line;
	string delimiter = ":";
	size_t pos;

	string fields[7];
	double dims[3];

	int i;

	if (!openInputFile(ifs)) // print error and exit program if file not found
	{
		cout << "Error, file not found" << endl;
		return;
	}

	while (getline(ifs, line)) // while there are still lines in the file
	{
		if (line.empty()) // skip empty line
			continue;

		// pid:name:weight:dims:price:seller:category
		for (i = 0; i < 6; i++) // read in fields separated by delimiter
		{
			pos = line.find(delimiter);
			fields[i] = line.substr(0, pos);
			line.erase(0, pos + 1);
		}
		fields[6] = line;

		stringstream dimFilter(fields[3]);
		double temp;
		for (i = 0; i < 3; i++) // filter string to fill dimensions array
		{
			dimFilter >> temp;
			dims[i] = temp;
		}

		ITEM_PTR newItem = new Item(fields[0], fields[1], stod(fields[2]),
							dims, stod(fields[4]), fields[5], fields[6]);

		if (pHSC->insert(newItem))
		{
			cout << "Inserted ";
			items->push_back(newItem);
		}
		else
			cout << "Could not insert ";
		cout << setw(40)
			<< (newItem->getName().length() < 40 ? newItem->getName() : newItem->getName().substr(0, 37) + "...")
			<< " : " << newItem->getProductID() << endl;
	}
}

void delete_data(vector<ITEM_PTR>*& items, HashSC<ITEM_PTR>*& pHSC)
{
	char choice;

	cout << "There are " << items->size() << " items. Are you sure you want to delete?" << endl;
	cout << "(Y/N): ";
	choice = toupper(cin.get());
	while (choice != 'Y' && choice != 'N')
	{
		cout << "Invalid Choice, Enter Again" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
		cout << "(Y/N): ";
		choice = toupper(cin.get());
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer

	cout << endl;
	if (choice == 'Y')
	{
		vector<ITEM_PTR>* items_copy = items;
		HashSC<ITEM_PTR>* pHSC_copy = pHSC;
		items = new vector<ITEM_PTR>();
		pHSC = new HashSC<ITEM_PTR>(HashProductID, compareProductID);

		DELETE_EVERYTHING(items_copy, pHSC_copy);
		cout << "Items have been deleted" << endl;
	}
	else
		cout << "Did not delete" << endl;
}

void find_and_display()
{
	cout << "MENU_OPTION_STUB3" << endl;
}

void list_HashTable()
{
	cout << "MENU_OPTION_STUB4" << endl;
}

void list_Key_Sequence()
{
	cout << "MENU_OPTION_STUB5" << endl;
}

void print_indented_tree()
{
	cout << "MENU_OPTION_STUB6" << endl;
}

void write_to_file()
{
	cout << "MENU_OPTION_STUB7" << endl;
}

void efficiency()
{
	cout << "MENU_OPTION_STUB8" << endl;
}
// ---------------------- Menu Functions End ------------------------------------------------------

void DELETE_EVERYTHING(vector<ITEM_PTR>* items, HashSC<ITEM_PTR>* pHSC)
{
	// delete all dynamically allocated items
	for (int i = 0; i < items->size(); i++)
		delete (*items)[i];

	// delete vector
	items->clear();
	delete items;

	// delete HashSC
	delete pHSC;
}

bool openInputFile(ifstream &ifs)
{
	string filename;

	cout << "Enter the input filename: ";
	getline(cin, filename);
	ifs.open(filename.c_str());
	return ifs.is_open();
}
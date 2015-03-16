/*
Manager: Wolfgang C. Strack

To include:
Initialize Data Structures
while loop for menu/possible function
input file function
tests for memory leaks
*/

#include "Global.h"
#include "HashSC.h"
#include "BST.h"

typedef Item* ITEM_PTR;

// Hash function
int HashProductID(const ITEM_PTR &pItem);
int Hash(const string &key);
// Compare function
int compareProductID(const ITEM_PTR &left, const ITEM_PTR &right);

// visit functions for BST
void displayITEM_PTR(ITEM_PTR &item);
void displayITEM_PTR_Indented(ITEM_PTR &item, string &tabs);
void deleteITEM_PTR(ITEM_PTR &item);

// Menu Functions
void display_menu();
void add_new_data(HashSC<ITEM_PTR>*& pHSC, BinarySearchTree<ITEM_PTR>* pTree, vector<ITEM_PTR>* items);
void delete_data(HashSC<ITEM_PTR>*& pHSC, BinarySearchTree<ITEM_PTR>* pTree, vector<ITEM_PTR>* items);
void find_and_display(HashSC<ITEM_PTR>*& pHSC);
void list_HashTable(HashSC<ITEM_PTR>*& pHSC);
void list_Key_Sequence(BinarySearchTree<ITEM_PTR>* pTree);
void print_indented_tree(BinarySearchTree<ITEM_PTR>* pTree);
void write_to_file();
void efficiency(HashSC<ITEM_PTR>*& pHSC, BinarySearchTree<ITEM_PTR>* pTree);

// properly delete dynamically allocated data structures
void DELETE_EVERYTHING(HashSC<ITEM_PTR>* pHSC, BinarySearchTree<ITEM_PTR>* pTree, vector<ITEM_PTR>* items);

bool openInputFile(ifstream &ifs);
bool openOutputFile(ofstream &ofs);

int main()
{
	HashSC<ITEM_PTR>* pHSC = new HashSC<ITEM_PTR>(HashProductID, compareProductID);
	BinarySearchTree<ITEM_PTR>* pTree = new BinarySearchTree<ITEM_PTR>(compareProductID);
	vector<ITEM_PTR>* items = new vector<ITEM_PTR>();

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
		case 1: add_new_data(pHSC, pTree, items);		break;
		case 2: delete_data(pHSC, pTree, items);		break;
		case 3: find_and_display(pHSC);					break;
		case 4: list_HashTable(pHSC);					break;
		case 5: list_Key_Sequence(pTree);				break;
		case 6: print_indented_tree(pTree);				break;
		case 7: write_to_file();						break;
		case 8: efficiency(pHSC, pTree);				break;
		case 0: cout << "Sayonara" << endl;				break;

		default: cout << option << " is not an option!" << endl;
		}
		cout << endl << endl << endl;
	}

	DELETE_EVERYTHING(pHSC, pTree, items);
	cout << (_CrtDumpMemoryLeaks() ? "\nMemory Leak\n" : "\nNo Leak\n");
}

// ---------------------- Hash and Compare Functions ----------------------------------------------
int HashProductID(const ITEM_PTR &pItem)
{
	string key = pItem->getProductID();
	return Hash(key);
}

int Hash(const string &key)
{
	unsigned int k;
	long retVal = 0;

	retVal += strtol(key.substr(2, 3).c_str(), 0, 16);
	retVal += strtol(key.substr(6, 4).c_str(), 0, 16);
	retVal += strtol(key.substr(11, 3).c_str(), 0, 16);

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
// ---------------------- Hash and Compare Functions End ------------------------------------------

// ---------------------- BST Visit Functions -----------------------------------------------------
void displayITEM_PTR(ITEM_PTR &item)
{
	cout << "[";
	item->write(cout);
	cout << "]" << endl;
}

void displayITEM_PTR_Indented(ITEM_PTR &item, string &tabs)
{
	cout << tabs;
	tabs += "\t";
	displayITEM_PTR(item);
}

void deleteITEM_PTR(ITEM_PTR &item)
{
	if (item != 0)
		delete item;
	item = 0;
}
// ---------------------- BST Visit Functions End -------------------------------------------------

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

// OPTION# 1
void add_new_data(HashSC<ITEM_PTR>*& pHSC, BinarySearchTree<ITEM_PTR>* pTree, vector<ITEM_PTR>* items)
{
	ifstream ifs;

	string line;
	string delimiter = ":";
	size_t pos;

	string fields[7];
	double dims[3];

	bool duplicates = false;
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
			pTree->insert(newItem);
		}
		else
		{
			cout << "Could not insert ";
			duplicates = true;
		}
		cout << setw(100)
			<< (newItem->getName().length() < 100 ? newItem->getName() : newItem->getName().substr(0, 97) + "...")
			<< " : " << newItem->getProductID() << endl;
	}

	if (duplicates)
		cout << "\nREPORT: There was duplicate data in the file. Non-duplicates successfully inserted." << endl;
	else
		cout << "\nInsert Successful!" << endl;
}

// OPTION# 2
void delete_data(HashSC<ITEM_PTR>*& pHSC, BinarySearchTree<ITEM_PTR>* pTree, vector<ITEM_PTR>* items)
{
	char choice;

	cout << "There are " << pHSC->size() << " items. Are you sure you want to delete?" << endl;
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
		HashSC<ITEM_PTR>* pHSC_copy = pHSC;
		BinarySearchTree<ITEM_PTR>* pTree_copy = pTree;
		vector<ITEM_PTR>* items_copy = items;

		pHSC = new HashSC<ITEM_PTR>(HashProductID, compareProductID);
		pTree = new BinarySearchTree<ITEM_PTR>(compareProductID);
		items = new vector<ITEM_PTR>();

		DELETE_EVERYTHING(pHSC_copy, pTree_copy, items_copy);
		cout << "Items have been deleted" << endl;
	}
	else
		cout << "Did not delete" << endl;
}

// OPTION# 3
void find_and_display(HashSC<ITEM_PTR>*& pHSC)
{
	string input;
	char choice = 'Y';
	ITEM_PTR item;

	while (choice == 'Y')
	{
		cout << "Enter a Product ID (Format is BLLL-NNNN-NNN, L is any letter and N is any number): ";
		getline(cin, input);

		if (input.length() < 13)
			input += "             ";

		ITEM_PTR temp, target;
		double dummydim[3] = { 0., 0., 0., };
		temp = new Item(input.substr(0, 13), "", 0, dummydim, 0, "", "");

		cout << endl;
		if (pHSC->getEntry(temp, target) && compareProductID(temp, target) == 0)
			target->display(cout);
		else
			cout << "Item with Product ID " << input << " not found." << endl;

		delete temp;
		temp = 0;

		cout << "\nWould you like to search for another item?" << endl;
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
	}

	cout << "\nReturning to menu" << endl;
}

// OPTION# 4
void list_HashTable(HashSC<ITEM_PTR>*& pHSC)
{
	cout << "Displaying Items (HashTable Format):" << endl << endl;
	pHSC->write(cout);
	cout << endl;
}

// OPTION# 5
void list_Key_Sequence(BinarySearchTree<ITEM_PTR>* pTree)
{
	cout << "Displaying Items (Sorted Key Sequence Format:" << endl << endl;
	pTree->inOrder(displayITEM_PTR);
	cout << endl;
}

// OPTION# 6
void print_indented_tree(BinarySearchTree<ITEM_PTR>* pTree)
{
	cout << "Printing Indented Tree:" << endl << endl;
	pTree->printIndentedTree(displayITEM_PTR_Indented);
}

// OPTION# 7
void write_to_file()
{
	cout << "MENU_OPTION_STUB7" << endl;
}

// OPTION# 8
void efficiency(HashSC<ITEM_PTR>*& pHSC, BinarySearchTree<ITEM_PTR>* pTree)
{
	cout << "HashSC Statistics:" << endl;
	pHSC->displayStatistics();
}
// ---------------------- Menu Functions End ------------------------------------------------------

void DELETE_EVERYTHING(HashSC<ITEM_PTR>* pHSC, BinarySearchTree<ITEM_PTR>* pTree, vector<ITEM_PTR>* items)
{
	// delete all dynamically allocated items
	for (int i = 0; i < items->size(); i++)
		delete (*items)[i];

	// delete vector
	items->clear();
	delete items;

	// delete BST
	delete pTree;

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
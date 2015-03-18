/*
Manager: Wolfgang C. Strack

This is the main application. It includes
- Hash function for HashSC
- Compare function for both HashSC and BinarySearchTree
- visit functions for BinarySearchTree
- menu functions such as display_menu and user options
- a function for deleting all dynamically allocated data structures
- functions for opening input/output files properly
*/

#include "Global.h"
#include "HashSC.h"
#include "BST.h"

typedef Item* ITEM_PTR;

// Hash function
int HashProductID				(const ITEM_PTR &pItem);
int Hash						(const string &key);
// Compare function
int compareProductID			(const ITEM_PTR &left, const ITEM_PTR &right);

// visit functions for BST
void displayITEM_PTR			(ITEM_PTR &item);
void displayITEM_PTR_Indented	(ITEM_PTR &item, string &tabs);
void deleteITEM_PTR				(ITEM_PTR &item);

// Menu Functions
void display_menu();
void add_new_data				(HashTable<ITEM_PTR>*& pHSC, BinarySearchTree<ITEM_PTR>*& pTree);
void delete_data				(HashTable<ITEM_PTR>*& pHSC, BinarySearchTree<ITEM_PTR>*& pTree);
void find_and_display			(HashTable<ITEM_PTR>*& pHSC);
void list_HashTable				(HashTable<ITEM_PTR>*& pHSC);
void list_Key_Sequence			(BinarySearchTree<ITEM_PTR>*& pTree);
void print_indented_tree		(BinarySearchTree<ITEM_PTR>*& pTree);
void write_to_file				(HashTable<ITEM_PTR>*& pHSC);
void efficiency					(HashTable<ITEM_PTR>*& pHSC);

// validates keys from input
bool validKey					(const string& key);

// properly delete dynamically allocated data structures
void DELETE_EVERYTHING			(HashTable<ITEM_PTR>*& pHSC, BinarySearchTree<ITEM_PTR>*& pTree);

// functions for opening files properly
bool openInputFile				(ifstream &ifs);
bool openOutputFile				(ofstream &ofs);

// ---------------------- Main --------------------------------------------------------------------
int main()
{
	HashTable<ITEM_PTR>* pHSC			= new HashSC<ITEM_PTR>(HashProductID, compareProductID);
	BinarySearchTree<ITEM_PTR>* pTree	= new BinarySearchTree<ITEM_PTR>(compareProductID);

	int option = -1;

	while (option != 0)
	{
		display_menu();
		cout << endl << "Enter an option (1, 2, 3...0): ";
		if (!(cin >> option))	// if input is not an integer
		{
			cout << "\n\nInvalid option!" << endl;
			cin.clear();		// clear error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
			option = -1;		// reset option
			continue;			// ask for option again
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer

		cout << endl;

		switch (option)
		{
		case 1: add_new_data		(pHSC, pTree);			break;
		case 2: delete_data			(pHSC, pTree);			break;
		case 3: find_and_display	(pHSC);					break;
		case 4: list_HashTable		(pHSC);					break;
		case 5: list_Key_Sequence	(pTree);				break;
		case 6: print_indented_tree	(pTree);				break;
		case 7: write_to_file		(pHSC);					break;
		case 8: efficiency			(pHSC);					break;
		case 0: cout << "Now Exiting" << endl;				break;

		default: cout << option << " is not an option!" << endl;
		}
		cout << endl << endl;
	}

	cout << endl; 
	
	ofstream ofs;
	ofs.open("output_ALL.txt");
	if (ofs.is_open()) // by default, write to a file the data that has been input
	{
		cout << "Saving data to output_ALL.txt" << endl;
		(static_cast<HashSC<ITEM_PTR>*>(pHSC))->write(ofs);
	}

	// Release all dynamically allocated memory
	cout << "Deleting all dynamically allocated memory." << endl;
	DELETE_EVERYTHING(pHSC, pTree);

	// Check for memory leaks
	cout << (_CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak!\n");
}
// ---------------------- Main --------------------------------------------------------------------

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

	// Add hex value of each part of the Product ID
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
	cout << *item;
	cout << "]" << endl;
}

void displayITEM_PTR_Indented(ITEM_PTR &item, string &tabs)
{
	cout << tabs;
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
		<< "|" << "    8    " << setw(39) << "Check Efficiency"					<< "|" << endl
		<< "|" << "    0    " << setw(39) << "QUIT"								<< "|" << endl;
	for (i = 0; i < 50; i++)
		cout << "-";

	cout << right << endl << endl;
}

// OPTION# 1
void add_new_data(HashTable<ITEM_PTR>*& pHSC, BinarySearchTree<ITEM_PTR>*& pTree)
{
	int option;
	cout << "Input from file (1) or enter manually (2)?" << endl;
	cout << "(Enter 1 or 2): ";
	if (!(cin >> option)) // if input is not an integer
	{
		cout << "\n\nInvalid option!" << endl;
		cin.clear();	// clear error flag
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
		return;
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
	
	/////////////// if entering data manually
	if (option == 2)
	{
		string key, name, seller, category, dimstemp;
		double weight, price;
		double dims[3] = { 0., 0., 0. };

		cout << "Enter a Product ID (Format is BLLL-HHHH-NNN, L is any letter, H is either a number or letter from a-f, and N is any number): ";
		getline(cin, key);
		if (!validKey(key))
		{
			cout << "Invalid key!" << endl;
			return;
		}

		// Check if input Product ID already exists in the data
		ITEM_PTR temp = new Item(key, "", 0, dims, 0, "", "");
		ITEM_PTR check = 0;
		if (pHSC->getEntry(temp, check) && compareProductID(temp, check) == 0)
		{
			cout << "Item with PID " << key << " already exists." << endl;
			check->display(cout);
			delete temp;
			return;
		}
		delete temp;

		// If the PID is unique, user now enters the rest of the fields
		cout << "Enter product name: ";
		getline(cin, name);

		cout << "Enter product weight (lbs): ";
		cin >> weight;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer

		cout << "Enter product dimensions (inches) with each field separated by a space (L W H): ";
		getline(cin, dimstemp);
		stringstream filter(dimstemp);
		for (int i = 0; i < 3; i++)
			filter >> dims[i];

		cout << "Enter product price (USD, do not include $): ";
		cin >> price;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer

		cout << "Enter product's seller name: ";
		getline(cin, seller);

		cout << "Enter product category: ";
		getline(cin, category);

		// Insert new item with input fields
		ITEM_PTR newItem = new Item(key, name, weight, dims, price, seller, category);
		pHSC->insert(newItem);
		pTree->insert(newItem);
		cout << "\nThe item you have entered\n" << endl;
		newItem->display(cout);
		cout << "\nhas been added." << endl;
		
		return;
	}

	/////////////// if entering data from file
	ifstream ifs;

	if (!openInputFile(ifs)) // print error and exit function if file not found
	{
		cout << "Error, file not found" << endl;
		return;
	}

	string line;
	string delimiter = ":";
	size_t pos;

	string fields[7];
	double dims[3];

	bool duplicates = false;
	int i;

	while (getline(ifs, line))	// while there are still lines in the file
	{
		if (line.empty())		// skip empty lines
			continue;

		for (i = 0; i < 6; i++)	// read in fields separated by delimiter
		{
			pos = line.find(delimiter);
			fields[i] = line.substr(0, pos);
			line.erase(0, pos + 1);
		}
		fields[6] = line;

		stringstream dimFilter(fields[3]);
		double temp;
		for (i = 0; i < 3; i++)	// filter string to fill dimensions array
		{
			dimFilter >> temp;
			dims[i] = temp;
		}

		// pid:name:weight:dims:price:seller:category
		ITEM_PTR newItem = new Item(fields[0], fields[1], stod(fields[2]),
							dims, stod(fields[4]), fields[5], fields[6]);

		if (pHSC->insert(newItem))
		{
			cout << "Inserted ";
			pTree->insert(newItem);
		}
		else
		{
			cout << "Could not insert ";
			delete newItem;
			duplicates = true;
		}
		cout << setw(100)
			<< (fields[1].length() < 100 ? fields[1] : fields[1].substr(0, 97) + "...")
			<< " : " << fields[0] << endl;
	}

	cout << endl;
	if (duplicates)
		cout << "REPORT: There was duplicate data in the file. Non-duplicates successfully inserted." << endl;
	else
		cout << "Insert Successful!" << endl;
}

// OPTION# 2
void delete_data(HashTable<ITEM_PTR>*& pHSC, BinarySearchTree<ITEM_PTR>*& pTree)
{
	char choice;

	cout << "There are " << pHSC->size() << " items. Are you sure you want to delete?" << endl;
	cout << "(Y/N): ";
	choice = toupper(cin.get());							// get user input
	while (choice != 'Y' && choice != 'N')					// check for valid user input
	{
		cout << "Invalid Choice, Enter Again" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
		cout << "(Y/N): ";
		choice = toupper(cin.get());
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');	// clear buffer

	cout << endl;
	if (choice == 'Y')
	{
		HashTable<ITEM_PTR>* pHSC_copy = pHSC;
		BinarySearchTree<ITEM_PTR>* pTree_copy = pTree;

		pHSC = new HashSC<ITEM_PTR>(HashProductID, compareProductID);
		pTree = new BinarySearchTree<ITEM_PTR>(compareProductID);

		DELETE_EVERYTHING(pHSC_copy, pTree_copy);
		cout << "Items have been deleted" << endl;
	}
	else
		cout << "Did not delete" << endl;
}

// OPTION# 3
void find_and_display(HashTable<ITEM_PTR>*& pHSC)
{
	string input;
	char choice = 'Y';
	ITEM_PTR item;

	while (choice == 'Y')
	{
		cout << "Enter a Product ID (Format is BLLL-HHHH-NNN, L is any letter, H is either a number or letter from a-f, and N is any number): ";
		getline(cin, input);

		if (input.length() < 13)
			input += "              "; // to avoid substring errors

		ITEM_PTR temp, target;
		double dummydim[3] = { 0., 0., 0., };
		temp = new Item(input.substr(0, 13), "", 0, dummydim, 0, "", ""); // used for key comparison

		cout << endl;
		if (pHSC->getEntry(temp, target) && compareProductID(temp, target) == 0)// if keys match
			target->display(cout);												// display found item
		else
			cout << "Item with Product ID " << input << " not found." << endl;

		delete temp;
		temp = 0;

		cout << endl << "Would you like to search for another item?" << endl;
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

	cout << endl << "Returning to menu" << endl;
}

// OPTION# 4
void list_HashTable(HashTable<ITEM_PTR>*& pHSC)
{
	cout << "Displaying Items (HashTable Format):" << endl << endl;
	(static_cast<HashSC<ITEM_PTR>*>(pHSC))->display(cout);
	cout << endl;
}

// OPTION# 5
void list_Key_Sequence(BinarySearchTree<ITEM_PTR>*& pTree)
{
	cout << "Displaying Items (Sorted Key Sequence Format):" << endl << endl;
	pTree->inOrder(displayITEM_PTR);
	cout << endl;
}

// OPTION# 6
void print_indented_tree(BinarySearchTree<ITEM_PTR>*& pTree)
{
	cout << "Printing Indented Tree:" << endl << endl;
	pTree->printIndentedTree(displayITEM_PTR_Indented);
}

// OPTION# 7
void write_to_file(HashTable<ITEM_PTR>*& pHSC)
{
	ofstream ofs;

	if (!openOutputFile(ofs)) // print error and exit program if file not found
	{
		cout << "Error, file not found" << endl;
		return;
	}

	cout << "Writing items to file..." << endl;
	(static_cast<HashSC<ITEM_PTR>*>(pHSC))->write(ofs);
}

// OPTION# 8
void efficiency(HashTable<ITEM_PTR>*& pHSC)
{
	cout << "Efficiency of HashSC:" << endl;
	pHSC->displayStatistics();
}
// ---------------------- Menu Functions End ------------------------------------------------------

// validates keys from input from add_new_data option
bool validKey(const string & key)
{
	if (key.length() != 13)
		return false;
	if (key.front() != 'B')
		return false;
	if (key.at(4) != '-' || key.at(9) != '-')
		return false;

	return true;
}

// deletes EVERYTHING!!!
void DELETE_EVERYTHING(HashTable<ITEM_PTR>*& pHSC, BinarySearchTree<ITEM_PTR>*& pTree)
{
	// delete all dynamically allocated data
	pTree->postOrder(deleteITEM_PTR);

	// delete BST
	delete pTree;

	// delete HashSC
	delete pHSC;
}

// for adding data
bool openInputFile(ifstream &ifs)
{
	string filename;

	cout << "Enter the input filename: ";
	getline(cin, filename);
	ifs.open(filename.c_str());
	return ifs.is_open();
}

// for writing data to file
bool openOutputFile(ofstream &ofs)
{
	string filename;

	cout << "Enter the output filename: ";
	getline(cin, filename);
	if (filename == "input_BACKUP.txt") // user cannot use this file
		return false;
	ofs.open(filename.c_str());
	return ofs.is_open();
}
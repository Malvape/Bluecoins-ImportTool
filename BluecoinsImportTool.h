#pragma once
// BluecoinsImportTool.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

const int menusize = 10;
const string defaultJsonFileName = "D:\\WinLibrary\\Documents\\GIT-Code\\Bluecoins-ImportTool\\Tests\\ktn.json";
bool splitTransac = false;


// Used to store all properties in the json file.
json properties;

// Used to store current entry before writing into file.
struct ENTRY {
	string type = "";			// Transaction category.
	string transCat = "";		// Transaction parent.
	string transChild = "";		// Transaction child.
	string accCat = "";			// Account category.
	string accChild = "";		// Account child.
	unsigned short int		// Date & time.
		year = 0,
		month = 0,
		day = 0,
		hour = 1000,
		mins = 1000;
	double amount = 3.14159265359;
	string item = "";			// Title of transaction.
	string notes = "";
	char status = '\0';
	string label = "";

	// Special variables for transfers
	string sourceAccCat = "";
	string sourceAccChild = "";
	string destAccCat = "";
	string destAccChild = "";
};
ENTRY entry;

// Utility functions:

// Resets all entry to initial values.
void reset() {
	entry.type = "";
	entry.transCat = "";
	entry.transChild = "";
	entry.accCat = "";
	entry.accChild = "";
	entry.year = 0;
	entry.month = 0;
	entry.day = 0;
	entry.hour = 1000;
	entry.mins = 1000;
	entry.amount = 3.14159265359;
	entry.item = "";
	entry.notes = "";
	entry.status = '\0';
	entry.label = "";
	entry.sourceAccCat = "";
	entry.sourceAccChild = "";
	entry.destAccCat = "";
	entry.destAccChild = "";
}

// Some arbituary introduction to the program during launch.
void introduction() {

}

// Outputs a line of j length of character k.
void line(int j = 50, char k = '=', bool nextLineAtEnd = true) {
	for (int i = 0; i < j; i++) {
		cout << k;
	}
	if (nextLineAtEnd) {
		cout << endl;
	}
}

// Outputs the following in the console
// --------------------------------------------------
// ID   Details
// --------------------------------------------------
void attrib() {
	line(50, '-');
	cout << left << setw(5) << "ID" << "Description" << endl;
	line(50, '-');
}

// Main menu for program.
int mainMenu() {
	int selection;

	struct MENU {
		int count = 0;
		string content = "";
	};
	MENU menu[menusize];

	// Define menus
	menu[0].count = 0;
	menu[0].content = "Load New Json File";
	menu[1].count = 1;
	menu[1].content = "Set New Output File";
	menu[2].count = 2;
	menu[2].content = "View All Current Categories";
	menu[3].count = 3;
	menu[3].content = "View Last Entry";
	menu[4].count = 4;
	menu[4].content = "Input New Entry";

	menu[6].count = 6;
	menu[6].content = "Toggle split entry status";

	menu[9].count = 9;
	menu[9].content = "Exit";

	// Output menu.
	attrib();
	for (int j = 0; j < menusize; j++) {
		if (menu[j].content != "" && menu[j].count != 0) {
			cout << left << setw(5) << menu[j].count << menu[j].content;
		}
		cout << endl;
	}

	cout << endl;

	// To output the status of split transaction mode if there is.
	if (splitTransac) {
	line(50, '-', true);
	cout << "Split transaction mode : True" << endl;
	cout << "Do take note that split transction mode will be switched on until you manually toggle it off. Please make sure that the date, time and title are the same." << endl;
	cout << "Using different label sets and status for each split is not currently supported. Only the first row of those will be used for each split transaction." << endl;
	line(50, '-', true);
	}
	
	cout << "Your Selection? : ";
	cin >> selection;

	return selection;
}

// Returns the json string without the quotes
string returnString(json i) {
	return(i);
}

// Returns all current inputted items in entry.
void inputted() {
	cout << endl;

	if (entry.item != "") {
		cout << "Title: " << entry.item << endl;
	}

	if (entry.type != "") {
		cout << "Type: " << entry.type << endl;
	}

	if (entry.transCat != "") {
		cout << "Category: " << entry.transCat << endl;
	}

	if (entry.transChild != "") {
		cout << "Category Child: " << entry.transChild << endl;
	}


	if (entry.type == "Transfer") {
		if (entry.sourceAccCat != "") {
			cout << "Source Account Category: " << entry.sourceAccCat << endl;
		}

		if (entry.sourceAccChild != "") {
			cout << "Source Account Child: " << entry.sourceAccChild << endl;
		}

		if (entry.destAccCat != "") {
			cout << "Destination Account Category: " << entry.destAccCat << endl;
		}

		if (entry.destAccChild != "") {
			cout << "Destination Account Child: " << entry.destAccChild << endl;
		}

	} else {
		if (entry.accCat != "") {
			cout << "Account Type: " << entry.accCat << endl;
		}

		if (entry.accChild != "") {
			cout << "Account Child: " << entry.accChild << endl;
		}
	}

	if ((entry.year != 0) &&
		(entry.month != 0) &&
		(entry.day != 0) &&
		(entry.hour != 1000) &&
		(entry.mins != 1000)
		) {
		cout << "Date (YYYY/MM/DD): "
			<< right << entry.year << "/"
			<< setfill('0') << setw(2) << entry.month << "/"
			<< setfill('0') << setw(2) << entry.day
			<< endl;

		cout << "Time (HH:MM): "
			<< setfill('0') << setw(2) << entry.hour << ":"
			<< setfill('0') << setw(2) << entry.mins
			<< endl;
		cout << setfill(' ');
	}

	if (entry.amount != 3.14159265359) {
		cout << "Amount: " << fixed << showpoint << setprecision(2) << entry.amount << endl;
	}


	if (entry.status != '\0') {
		cout << "Status: " << entry.status << endl;
	}

	if (entry.label != "") {
		cout << "Label: " << entry.label << endl;
	}

	if (entry.notes != "") {
		cout << "\nNotes:\n" << entry.notes << endl << endl;
	}


}

// Outputs all properties and their respective values.
void outAllProperties() {
	cout << "json type : " << returnString(properties["jsonType"]) << endl;
	// If filepath property exist then load it as default path, and change behaviour accordingly
	if (properties.contains("outFile")) {
		if (properties["outFile"][0].contains("filePath")) {
			cout << "default output path : " << returnString(properties["outFile"][0]["filePath"]) << endl;
		}
		if (properties["outFile"][0].contains("defaultAppend")) {
			cout << "    Default is append : " << properties["outFile"][0]["defaultAppend"] << endl;
		}
	}

	int i = 0,
		j = 0,
		k = 0;

	while (i < properties["presetLists"].size()) {
		j = 0;
		k = 0;
		cout << returnString(properties["presetLists"][i]["type"]) << " : " << endl;

		while (j < properties["presetLists"][i]["catList"].size()) {
			k = 0;
			line(4, ' ', false);
			cout << returnString(properties["presetLists"][i]["catList"][j]["cat"]) << " : " << endl;

			while (k < properties["presetLists"][i]["catList"][j]["child"].size()) {
				line(8, ' ', false);
				cout << returnString(properties["presetLists"][i]["catList"][j]["child"][k]) << endl;
				k++;
			}
			j++;
		}
		line();
		i++;
	}
}

// === Unused function ===
// Outputs elements one level below, excluding unspecified arrays.
// Place a space if want to output all types.
// If only type provided, list cat.
// If both type and cat provided, list child.
void outArray(string type, string cat = " ") {
	int i = 0;
	bool found0 = false;

	if (type == " ") { // If type is space show all types.
		while (i < properties["presetLists"].size()) {
			cout << returnString(properties["presetLists"][i]["type"]) << endl;
			i++;
		}
	} else {


		while (i < properties["presetLists"].size()) {
			if (returnString(properties["presetLists"][i]["type"]) == type) {
				found0 = true;

				if (cat == " ") { // If only type stated then only output list of categories.
					int j = 0;

					while (j < properties["presetLists"][i]["catList"].size()) {
						cout << returnString(properties["presetLists"][i]["catList"][j]["cat"]) << endl;
						j++;
					}

					break;

				} else { // Else if stated then output child
					int j = 0;
					bool found1 = false;

					while (j < properties["presetLists"][i]["catList"].size()) {
						if (returnString(properties["presetLists"][i]["catList"][j]["cat"]) == cat) {
							int k = 0;
							found1 = true;

							while (k < properties["presetLists"][i]["catList"][j]["child"].size()) {
								cout << returnString(properties["presetLists"][i]["catList"][j]["child"][k]) << endl;
								k++;
							}

						}
						break;
					}

					if (!found1) { // If not found in list then category not found.
						cout << "Category not found." << endl;
					}

				}
				break;
			}

			i++;
		}
		if (!found0) { // If not found in list then type not found.
			cout << "Type not found." << endl;
		}
	}
}

// Outputs all elements one level below according to the index number.
// Also provides index number in the process.
// *Does not output bank accounts unless specified.
void outArray(bool isAccount = false, int type = 10000, int cat = 10000) {
	int i = 0;

	// If selection is account, then start from array entry 1.
	if (isAccount) {
		i = 0;
	} else {
		i = 1;
	}


	if (type == 10000) { // If type is unspecified show all types.
		attrib();
		while (i < properties["presetLists"].size()) {
			cout << left << setw(5) << i << returnString(properties["presetLists"][i]["type"]) << endl;
			i++;
		}
	} else {

		if (type < properties["presetLists"].size()) { // Only display if type is less than size of presetList
			if (cat == 10000) { // If only type stated then only output list of categories.
				int j = 0;
				attrib();

				while (j < properties["presetLists"][type]["catList"].size()) {
					cout << left << setw(5) << j << returnString(properties["presetLists"][type]["catList"][j]["cat"]) << endl;
					j++;
				}

			} else { // If type and cat stated then output child.
				int j = 0;

				if (cat < properties["presetLists"][type]["catList"].size()) {
					attrib();
					while (j < properties["presetLists"][type]["catList"][cat]["child"].size()) {
						cout << left << setw(5) << j << returnString(properties["presetLists"][type]["catList"][cat]["child"][j]) << endl;
						j++;
					}

				} else {
					cout << "Category number invalid." << endl;
				}

			}


		} else {
			cout << "Type number invalid." << endl;
		}
	}

	cout << endl;
}

// For user to input all entry information.
bool entryInput() {
	// Integer for expense, income category parent and child.
	int
		i = 0, // To describe type of transaction
		j = 0, // To describe parent
		k = 0; // To describe child

	bool illegal = true;

	// User input : Short Description
	system("cls");
	inputted();
	line(50, '-');
	cout << "Transaction title? (Only press 'enter' when done, no multi-line support yet)" << endl;
	line(50, '-');
	cin.ignore();
	getline(cin, entry.item);

	// User input : Type of Transaction
	illegal = true;
	while (illegal) {
		system("cls");
		inputted();
		outArray(false);
		cout << endl << left << setw(5) << "5" << "Transfer" << endl;

		cout << endl << "Type? ";
		cin >> i;

		if ((i == 1) || (i == 2) || (i == 5)) {
			illegal = false;
		} else {
			cout << "Illegal action!" << endl;
			system("pause");
			continue;
		}
	}

	// If transaction type is transfer
	if (i == 5) {
		// Transfer cases
		entry.transCat = "(Transfer)";
		entry.transChild = "(Transfer)";
		entry.type = "Transfer";

		//To determine source account
		// User input : Account Type
		illegal = true;
		while (illegal) {
			system("cls");
			inputted();
			outArray(true, 0);

			cout << "Source Account Type? ";
			cin >> j;

			if ((j < properties["presetLists"][0]["catList"].size()) && (j >= 0)) {
				illegal = false;
			} else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}
		}
		entry.sourceAccCat = returnString(properties["presetLists"][0]["catList"][j]["cat"]);

		// User input : Account
		illegal = true;
		while (illegal) {
			system("cls");
			inputted();
			outArray(true, 0, j);

			cout << "Source Account Child? ";
			cin >> k;

			if ((k < properties["presetLists"][0]["catList"][j]["child"].size()) && (k >= 0)) {
				illegal = false;
			} else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}
		}
		entry.sourceAccChild = returnString(properties["presetLists"][0]["catList"][j]["child"][k]);

		// To determine destination account.
		j = 0;
		k = 0;
		// User input : Account Type
		illegal = true;
		while (illegal) {
			system("cls");
			inputted();
			outArray(true, 0);

			cout << "Destination Account Type? ";
			cin >> j;

			if ((j < properties["presetLists"][0]["catList"].size()) && (j >= 0)) {
				illegal = false;
			} else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}
		}
		entry.destAccCat = returnString(properties["presetLists"][0]["catList"][j]["cat"]);

		// User input : Account
		illegal = true;
		while (illegal) {
			system("cls");
			inputted();
			outArray(true, 0, j);
			cout << "Destination Account Child? ";
			cin >> k;
			if ((k < properties["presetLists"][0]["catList"][j]["child"].size()) && (k >= 0)) {
				illegal = false;
			} else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}
			entry.destAccChild = returnString(properties["presetLists"][0]["catList"][j]["child"][k]);

		}

	} else {
	// User input : Expense / Income Parent Category
		entry.type = returnString(properties["presetLists"][i]["type"]);
		illegal = true;
		while (illegal) {
			system("cls");
			inputted();
			outArray(false, i);

			cout << "Category? ";
			cin >> j;

			if ((j < properties["presetLists"][i]["catList"].size()) && (j >= 0)) {
				illegal = false;
			} else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}

		}
		entry.transCat = returnString(properties["presetLists"][i]["catList"][j]["cat"]);

		// User input : Expense / Income Category
		illegal = true;
		while (illegal) {
			system("cls");
			inputted();
			outArray(false, i, j);

			cout << "Category Child? ";
			cin >> k;

			if ((k < properties["presetLists"][i]["catList"][j]["child"].size()) && (k >= 0)) {
				illegal = false;
			} else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}

		}
		entry.transChild = returnString(properties["presetLists"][i]["catList"][j]["child"][k]);

		// User input : Account Type
		illegal = true;
		while (illegal) {
			system("cls");
			inputted();
			outArray(true, 0);

			cout << "Account Type? ";
			cin >> j;

			if ((j < properties["presetLists"][0]["catList"].size()) && (j >= 0)) {
				illegal = false;
			} else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}

		}
		entry.accCat = returnString(properties["presetLists"][0]["catList"][j]["cat"]);

		// User input : Account
		illegal = true;
		while (illegal) {
			system("cls");
			inputted();
			outArray(true, 0, j);

			cout << "Account Child? ";
			cin >> k;

			if ((k < properties["presetLists"][0]["catList"][j]["child"].size()) && (k >= 0)) {
				illegal = false;
			} else {
				cout << "Illegal action!" << endl;
				system("pause");
				continue;
			}

		}
		entry.accChild = returnString(properties["presetLists"][0]["catList"][j]["child"][k]);

	}

	// Date & time input :
	system("cls");
	inputted();
	line(50, '-');
	cout << "Date & time input: " << endl;
	line(50, '-');

	// User input : Year
	cout << "Year? ";
	cin >> entry.year;

	// User input : Month
	cout << "Month? ";
	cin >> entry.month;

// User input : Day
	cout << "Day? ";
	cin >> entry.day;

	// User input : Hour
	cout << "Hour? ";
	cin >> entry.hour;

// User input : Mins
	cout << "Mins? ";
	cin >> entry.mins;
// ==================================================

	// User input : Amount
	system("cls");
	inputted();
	line(50, '-');
	cout << "Amount? ";
	cin >> entry.amount;


	// User input : Notes (No multi-line)
	system("cls");
	inputted();
	line(50, '-');
	cout << "Notes? (Only press 'enter' when done, no multi-line support yet)" << endl;
	line(50, '-');
	cin.ignore();
	getline(cin, entry.notes);

	// User input : Status
	illegal = true;
	while (illegal) {
		system("cls");
		inputted();
		attrib();
		char statusSelect = '\0';
		cout << left << setw(5) << "R" << "Reconciled" << endl;
		cout << left << setw(5) << "C" << "Cleared" << endl;
		cout << left << setw(5) << "0" << "<None>" << endl;
		cout << "Status? ";
		cin >> statusSelect;
		statusSelect = toupper(statusSelect);
		switch (statusSelect) {
			case 'R':
			{
				entry.status = 'R';
				illegal = false;
				break;
			} case 'C':
			{
				entry.status = 'C';
				illegal = false;
				break;
			} case '0':
			{
				illegal = false;
				break;
			}
			default:
				break;
		}

	}

	// System generate : Label
	time_t rawtime = time(&rawtime);
	struct tm now;
	localtime_s(&now, &rawtime);
	int thisYear = now.tm_year + 1900;
	if (now.tm_mon < 10) {
		entry.label = "Import " + to_string(thisYear) + "0" + to_string(now.tm_mon);
	} else {
		entry.label = "Import " + to_string(thisYear) + to_string(now.tm_mon);

	}

	// Review entry, then press key to return commit intent.
	illegal = true;
	while (illegal) {
		system("cls");
		inputted();
		line(50, '-');
		char commit;
		cout << "Commit changes? (y/n) ";
		cin >> commit;
		commit = tolower(commit);

		if (commit == 'y' || commit == '1') {
			illegal = false;
			return true;
		} else if (commit == 'n' || commit == '0') {
			illegal = false;
			return false;
		}
	}
}

// Global variables related with file output.
ifstream fileCheck;
ofstream file;
bool append = false;
string outFilename, 
	jsonFilename;

// Function to load output file.
void fileFunc(bool ignore = false, string path = "", bool toAppend = false) {
	if (path == "") {
		cout << "File path for output file? ";
		if (ignore) {
			cin.ignore();
		}
		getline(cin, outFilename);
	}

	fileCheck.open(outFilename);
	if (!fileCheck) {
		cout << "Output file does not exist, create file? (y/n)";
		char intent;
		cin >> intent;
		intent = tolower(intent);

		// If 'y' then create file else go back main menu
		if (intent == 'y') {
			file.open(outFilename);
		}

	} else {
		char intent = '\0';
		if (!toAppend) {
			cout << "Output file exists, append? (y/n/c) \nSelecting 'n' will clear the existing file. Press 'c' to cancel. " << endl;
			cin >> intent;
			intent = tolower(intent);

		}

		if (intent == 'c') {
			outFilename = "";
		} else if ((intent == 'y') || (toAppend == true)) {
			file.open(outFilename, ios::app);
			append = true;
		} else if ((intent == 'n') || (toAppend == false)) {
			file.open(outFilename);
		}

	}
	fileCheck.close();

}

// Request json file path, opens it and imports it into the json struct.
void readFile(bool ignore = false) {
	ifstream jsonFile;
	while (true) {
		cout << "File path for json file ? ";
		if (ignore) {
			cin.ignore();
		}
		getline(cin, jsonFilename);

		if (jsonFilename == "d") {
			jsonFilename = defaultJsonFileName;
		}

		jsonFile.open(jsonFilename);

		if (!jsonFile) {
			cout << "File does not exist. " << endl;
			continue;
		} else {
			break;
		}

	}

	jsonFile >> properties;

	// If filepath property exist then load it as default path, and change behaviour accordingly
	if (properties.contains("outFile")) {
		if (properties["outFile"][0].contains("filePath")) {
			outFilename = returnString(properties["outFile"][0]["filePath"]);
		}
		if (properties["outFile"][0].contains("defaultAppend")) {
			append = properties["outFile"][0]["defaultAppend"];
		}
		fileFunc(false, outFilename, append);
	}

	cout << "File succesfully imported." << endl;

	jsonFile.close();
}


// Outputs everything stored in current entry to the output file.
void writeToFile() {
	// If user selects to append or is not first entry then will not output this line.
	if (!append) {
		file << "(1)Type,(2)Date,(3)Item or Payee,(4)Amount,(5)Parent Category,(6)Category,(7)Account Type,(8)Account,(9)Notes,(10) Label,(11) Status,(12) Split" << endl;
	}

	// There are different logics for transfers and normal transactions.
	if (entry.type == "Transfer") {
	// Source Account
		file << "Transfer" << ",";
		file << right << setfill('0')
			<< setw(2) << entry.month << "/"
			<< setw(2) << entry.day << "/"
			<< entry.year << " "
			<< setw(2) << entry.hour << ":"
			<< setw(2) << entry.mins << ","
			<< setfill(' ');
		file << entry.item << ",";
		file << entry.amount * -1 << ",";
		file << "(Transfer)" << ",";
		file << "(Transfer)" << ",";
		file << entry.sourceAccCat << ",";
		file << entry.sourceAccChild << ",";
		file << entry.notes << ",";
		file << entry.label << ",";
		if(entry.status != '\0'){
			file << entry.status;
		}
		file << ",";
		if (splitTransac) {
			file << "split";
		}
		file << endl;
	// Destination Account
		file << "Transfer" << ",";
		file << right << setfill('0')
			<< setw(2) << entry.month << "/"
			<< setw(2) << entry.day << "/"
			<< entry.year << " "
			<< setw(2) << entry.hour << ":"
			<< setw(2) << entry.mins << ","
			<< setfill(' ');
		file << entry.item << ",";
		file << entry.amount << ",";
		file << "(Transfer)" << ",";
		file << "(Transfer)" << ",";
		file << entry.destAccCat << ",";
		file << entry.destAccChild << ",";
		file << entry.notes << ",";
		file << entry.label << ",";
		if(entry.status != '\0'){
			file << entry.status;
		}
		file << ",";
		if (splitTransac) {
			file << "split";
		}
		file << endl;

	} else { // For normal use cases.
		file << entry.type << ",";
		file << right << setfill('0')
			<< setw(2) << entry.month << "/"
			<< setw(2) << entry.day << "/"
			<< entry.year << " "
			<< setw(2) << entry.hour << ":"
			<< setw(2) << entry.mins << ","
			<< setfill(' ');

		file << entry.item << ",";
		file << entry.amount << ",";
		file << entry.transCat << ",";
		file << entry.transChild << ",";
		file << entry.accCat << ",";
		file << entry.accChild << ",";
		file << entry.notes << ",";
		file << entry.label << ",";
		if(entry.status != '\0'){
			file << entry.status;
		}
		file << ",";
		if (splitTransac) {
			file << "split";
		}
		file << endl;

	}
}

// TODO: Reference additional headers your program requires here.

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

json properties;

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


// Request file path, opens it and imports it into the json struct.
void readFile() {
	ifstream jsonFile;

	while (true) {
		cout << "File path for json file ? ";
		string filename;
		getline(cin, filename);

		if (filename == "d") {
			filename = "D:\\WinLibrary\\Documents\\GIT-Code\\Bluecoins-ImportTool\\Tests\\ktn.json";
		}

		jsonFile.open(filename);

		if (!jsonFile) {
			cout << "File does not exist. " << endl;
			continue;
		} else {
			break;
		}

	}

	jsonFile >> properties;

	cout << "File succesfully imported." << endl;

}

// Returns the json string without the quotes
string returnString(json i) {
	return(i);
}

// Outputs all properties and their respective values.
void outAllProperties() {
	cout << "json type : " << returnString(properties["jsonType"]) << endl;

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

// Outputs elements one level below, excluding unspecified arrays.
// If only type provided, list cat.
// If both type and cat provided, list child.
void outArray(string type, string cat = " ") {
	int i = 0;
	bool found0 = false;

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

// Outputs all elements one level below according to the index number.
// Also provides index number in the process.
void outArray(int type, int cat = NULL) {
	int i = 0;
	line(50, '-');
	if (type < properties["presetLists"].size()) { // Only display if type is less than size of presetList
		if (cat == NULL) { // If only type stated then only output list of categories.
			int j = 0;
			cout << left << setw(5) << "ID" << "Description" << endl;
			line(50, '-');

			while (j < properties["presetLists"][type]["catList"].size()) {
				cout << left << setw(5) << j << returnString(properties["presetLists"][type]["catList"][j]["cat"]) << endl;
				j++;
			}

		} else { // Else if stated then output child
			int j = 0;

			if (cat < properties["presetLists"][type]["catList"].size()) {
				cout << left << setw(5) << "ID" << "Description" << endl;
				line(50, '-');
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





// TODO: Reference additional headers your program requires here.

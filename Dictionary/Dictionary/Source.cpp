#include <iostream>
#include "Dictionary.h"
#include <vector>
using namespace std;

void listOptions(int activeDictionary, int numberOfDictionaries) {
	cout << "Muveletek:" << endl;
	if (activeDictionary != -1) {
		cout << "k) Szo keresese az aktiv szotarban" << endl;
		cout << "a) Szo hozzaadasa az aktiv szotarhoz" << endl;
		cout << "t) Szo torlese az aktiv szotarbol" << endl;
		cout << "f) Az aktiv szotar feltoltese allomanybol" << endl;
		cout << "l) Az aktiv szotar listazasa" << endl;
		cout << "d) Az aktiv szotar torlese" << endl;
		cout << "v) Az aktiv szotar kivalasztasa" << endl;
		cout << "u) Uj szotar hozzaadasa" << endl;
		cout << "r) A rendelkezesre allo szotarak listazasa" << endl;
		cout << "q) Kilepes" << endl;
	}
	else {
		cout << "u) Uj szotar hozzaadasa" << endl;
		if (numberOfDictionaries > 0) {
			cout << "v) Az aktiv szotar kivalasztasa" << endl;
			cout << "r) A rendelkezesre allo szotarak listazasa" << endl;
		}
		cout << "q) Kilepes" << endl;
	}
}

void listDictionaries(vector<Dictionary*> dictionaries, int numberOfDictionaries) {
	cout << "Rendelkezesre allo szotarak: ";
	for (int i = 0; i < numberOfDictionaries; i++) {
		cout << i + 1 << ") " << dictionaries[i]->GetName() << ' ';
	}
	cout << endl;
}

void deleteDictionary(vector<Dictionary*>& dictionaries, int& activeDictionary, int& numberOfDictionaries) {
	delete dictionaries[activeDictionary];
	for (int i = activeDictionary; i < numberOfDictionaries - 1; i++) {
		dictionaries[i] = dictionaries[i + 1];
	}
	numberOfDictionaries--;
	dictionaries.resize(numberOfDictionaries);
	activeDictionary = -1;
}

int main() {
	int numberOfDictionaries = 0;
	vector<Dictionary*> dictionaries; //Letrejon a szotarakbol allo vektor
	cout << "--------------SzotarKezelo--------------" << endl;
	char option = 'x';
	int activeDictionary = -1;
	while (option != 'q') { //A program muveletek ajanl fel, amig a felhasznalo ki nem lepik
		cout << endl;
		if (activeDictionary != -1) {
			cout << "Aktiv szotar: " << dictionaries[activeDictionary]->GetName() << endl;
		}
		listOptions(activeDictionary, numberOfDictionaries);
		cin >> option;
		if (activeDictionary != -1) {
			string inputString1, inputString2;
			int inputInteger;
			switch (option) {
			case 'k':
				cout << "Adja meg a keresendo szavat: ";
				cin >> inputString1;
				for (int i = 0; i < inputString1.length(); i++) {
					inputString1[i] = tolower(inputString1[i]);
				}
				cout << dictionaries[activeDictionary]->SearchWord(inputString1);
				break;
			case 'a':
				cout << "Adja meg a hozzaadando szavat es a forditasat: ";
				cin >> inputString1 >> inputString2;
				for (int i = 0; i < inputString1.length(); i++) {
					inputString1[i] = tolower(inputString1[i]);
				}
				for (int i = 0; i < inputString2.length(); i++) {
					inputString2[i] = tolower(inputString2[i]);
				}
				dictionaries[activeDictionary]->AddWord(inputString1, inputString2);
				break;
			case 't':
				cout << "Adja meg a torlendo szavat: ";
				cin >> inputString1;
				for (int i = 0; i < inputString1.length(); i++) {
					inputString1[i] = tolower(inputString1[i]);
				}
				dictionaries[activeDictionary]->DeleteWord(inputString1);
				break;
			case 'f':
				cout << "Adja meg az allomany nevet: ";
				cin >> inputString1;
				dictionaries[activeDictionary]->LoadFromFile(inputString1);
				break;
			case 'l':
				dictionaries[activeDictionary]->List();
				break;
			case 'd':
				deleteDictionary(dictionaries, activeDictionary, numberOfDictionaries);
				break;
			case 'v':
				cout << "Adja meg a kivalasztott szotar szamat (" << "1-" << numberOfDictionaries << "): ";
				cin >> inputInteger;
				if (inputInteger < 1 || inputInteger > numberOfDictionaries) {
					cout << "Hiba: nem letezik " << inputInteger << ". szotar!" << endl;
					continue;
				}
				else {
					activeDictionary = inputInteger - 1;
				}
				break;
			case 'u':
				cout << "Adja meg az uj szotar nevet: ";
				cin >> inputString1;
				dictionaries.push_back(new Dictionary(inputString1));
				numberOfDictionaries++;
				break;
			case 'r':
				listDictionaries(dictionaries, numberOfDictionaries);
				break;
			case 'q':
				break;
			default:
				cout << "Hibas muvelet!" << endl;
				continue;
			}
		}
		else {
			string inputString1;
			int inputInteger;
			switch (option) {
			case 'u':
				cout << "Adja meg az uj szotar nevet: ";
				cin >> inputString1;
				dictionaries.push_back(new Dictionary(inputString1));
				numberOfDictionaries++;
				break;
			case 'v':
				if (numberOfDictionaries == 0) { cout << "Hibas muvelet!" << endl; continue; }
				cout << "Adja meg a kivalasztott szotar szamat (" << "1-" << numberOfDictionaries << "): ";
				cin >> inputInteger;
				if (inputInteger < 1 || inputInteger > numberOfDictionaries) {
					cout << "Hiba: nem letezik " << inputInteger << ". szotar!" << endl;
					continue;
				}
				else {
					activeDictionary = inputInteger - 1;
				}
				break;
			case 'r':
				if (numberOfDictionaries == 0) { cout << "Hibas muvelet!" << endl; continue; }
				listDictionaries(dictionaries, numberOfDictionaries);
				break;
			case 'q':
				break;
			default:
				cout << "Hibas muvelet!" << endl;
				continue;
			}
		}
	}
	for (int i = 0; i < dictionaries.size(); i++) {
		delete dictionaries[i];
	}
	return 0;
}
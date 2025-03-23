#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "HashTable.h"

using namespace std;

class Dictionary
{
private:
	string name;
	HashTable words;

public:
	Dictionary(const string&);
	void AddWord(const string&, const string&);
	void DeleteWord(const string&);
	string SearchWord(const string&)const;
	void LoadFromFile(const string&);
	string GetName()const;
	void List()const;
};
#endif


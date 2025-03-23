#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>

using namespace std;

struct Entry {
    string key;
    string value;
    bool deleted;

    Entry() : deleted(false) {};
    Entry(const string& key, const string& value) : key(key), value(value), deleted(false) {};
};

class HashTable {
private:
    Entry** table;
    int tableSize;
    int elementCount;

    int Hash(const string& key, const int size)const;
    void ReHash();

public:
    HashTable(int size);
    ~HashTable();
    void Add(const string& key, const string& value);
    string Search(const string& key)const;
    void Delete(const string& key);
    void List()const;
};
#endif
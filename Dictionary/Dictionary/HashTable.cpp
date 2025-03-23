#include "HashTable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size) : tableSize(size), elementCount(0) {
    table = new Entry * [tableSize];
    for (int i = 0; i < tableSize; i++) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < tableSize; i++) {
        delete table[i];
    }
    delete[] table;
}

//Meghatarozza az indexet a kulcs alapjan (hasito fuggveny)
int HashTable::Hash(const string& key, const int size) const {
    int hashValue = 0;
    for (char c : key) {
        hashValue += c;
    }
    hash<int> hashFunction;
    return hashFunction(hashValue) % size;
}

//Ketszeresere noveli a meretet es ujrahasheli az osszes elemet
void HashTable::ReHash() {
    int newSize = tableSize * 2;
    Entry** newTable = new Entry * [newSize];
    for (int i = 0; i < newSize; i++) {
        newTable[i] = nullptr;
    }

    for (int i = 0; i < tableSize; i++) {
        if (table[i] != nullptr && !table[i]->deleted) {
            int newIndex = Hash(table[i]->key, newSize);
            while (newTable[newIndex] != nullptr) {
                newIndex = (newIndex + 1) % newSize;
            }
            newTable[newIndex] = table[i];
        }
    }

    delete[] table;
    table = newTable;
    tableSize = newSize;
}

//A kulcs alapjan hozzaadja az erteket a tablahoz (Ellenorzi a telitettseget)
void HashTable::Add(const string& key, const string& value) {
    if ((double)elementCount / tableSize > 0.75) {
        ReHash();
    }

    int index = Hash(key, tableSize);
    int originalIndex = index;

    while (table[index] != nullptr) {
        if (table[index]->deleted || table[index]->key == key) {
            break;
        }
        index = (index + 1) % tableSize;

        if (index == originalIndex) {
            return; //A ReHash megoldja
        }
    }
    if (table[index] == nullptr) {
        table[index] = new Entry(key, value);
        elementCount++;
    }
    else {
        table[index]->value = value;
        if (table[index]->deleted) {
            table[index]->deleted = false;
            elementCount++;
        }
    }
}

//Visszateriti a megadott kulcsnak megfelelo erteket, ha nincs ilyen hiba uzenetet terit vissza
string HashTable::Search(const string& key)const {
    int index = Hash(key, tableSize);
    int originalIndex = index;

    while (table[index] != nullptr) {
        if (table[index]->key == key && !table[index]->deleted) {
            return table[index]->value;
        }
        index = (index + 1) % tableSize;
        if (index == originalIndex) {
            break;
        }
    }
    return "Hiba: " + key + " nem talalhato!";
}

//Tolri a megadott kulcsnak megfelelo erteket, ha nincs ilyen figyelmen kivul hagyja
void HashTable::Delete(const string& key) {
    int index = Hash(key, tableSize);
    int originalIndex = index;

    while (table[index] != nullptr) {
        if (table[index]->key == key && !table[index]->deleted) {
            table[index]->deleted = true; // Megjelolve toroltkent
            elementCount--;
            return;
        }
        index = (index + 1) % tableSize;
        if (index == originalIndex) {
            return; // Eleve nincs benne a torlendo elem
        }
    }
}

//Kilistazza a tabla osszes elemet
void HashTable::List() const {
    for (int i = 0; i < tableSize; i++) {
        if (table[i] != nullptr && !table[i]->deleted) {
            cout << table[i]->key << ": " << table[i]->value << endl;
        }
    }
}
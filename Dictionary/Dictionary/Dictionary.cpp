#include "Dictionary.h"
#include <iostream>
#include <fstream>

using namespace std;

Dictionary::Dictionary(const string& name) : name(name), words(19) {};

//Hozzadja a megadott szopart a szotarhoz (nativ, idegen)
void Dictionary::AddWord(const string& native, const string& foreign) {
    words.Add(native, foreign);
    cout << "A(z) " + native + " szo " + foreign + " forditasa hozzaadva a(z) " + name + " szotarhoz!" << endl;
}

//Kitoroli a megadott nativ szavat a szotarbol a forditasaval egyutt
void Dictionary::DeleteWord(const string& native) {
    words.Delete(native);
    cout << native + " torolve lett a(z) " + name + " szotarbol!" << endl;
}

//Visszateriti a nativ nyelven keresett szo forditasat, ha nincs benne a szotarban hibauzenetet terit vissza
string Dictionary::SearchWord(const string& native) const {
    return native + " a(z) " + name + " szotar szerint: " + words.Search(native) + "\n";
}

//A megadott fajlbol feltolti a szotarat
void Dictionary::LoadFromFile(const string& fileName) {
    ifstream input(fileName.c_str());
    if (!input.is_open()) {
        cout << "Hiba: Nem sikerult feltolteni a(z) " + name + " szotarat! (" << fileName << " nem letezik)"<<endl;
    }
    else {
        string native, foreign;
        while (input >> native >> foreign) {
            words.Add(native, foreign);
        }
        cout << "A(z) " + name + " szotar sikeresen feltotve!" << endl;
    }
}

//Visszateriti a szotar nevet
string Dictionary::GetName()const {
    return name;
}

//Listazza a szotar minden szoparjat
void Dictionary::List()const {
    cout << name + " szotar:" << endl;
    words.List();
}

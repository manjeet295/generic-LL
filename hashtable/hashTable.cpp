#include "hash.h"
#include<iostream>
using namespace std;

int main() {
    Hash<int, string> h1(5);
    h1.insert(1, "Apple");
    h1.insert(2, "Banana");
    h1.insert(3,"changed");
    h1.insert(4, "class");
    h1.insert(5, "name");
    h1.insert(6,"roll");
    cout << h1.get(1) << endl;
    cout << h1.get(2) << endl;
    cout << h1.get(3) << endl;
    cout << h1.get(4) << endl;
    cout << h1.get(5) << endl;
    cout << h1.get(6) << endl;
     h1.remove(2);


  
    // Hash<string,int> h2;
    // h2.insert("Apple",5);
    // h2.insert("Banana",2);

    // cout << h2.get("Apple") << endl;
    // cout << h2.get("Banana") << endl;
    // cout << h2.get("Kiwi") << endl; 

    return 0;
}
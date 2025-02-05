#include "OpenHashing.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <graphics.h>
#include <string>

using namespace std;

int main() {
     
    closegraph();
    initwindow(1200, 800, "Open Hashing with Strings");
    
    OpenHashing hashTable(13);
    vector<string> data;
    string input;
    
    cout << "Ingrese los strings a insertar en la tabla hash (ingrese -1 para terminar):" << endl;
    while (true) {
        cin >> input;
        if (input == "-1") break;
        data.push_back(input);
    }
    
    sort(data.begin(), data.end());
    
    for (const string& value : data) {
        hashTable.insert(value);
        hashTable.display();
        getch();
    }
    
    char response;
    do {
        cout << "Desea eliminar algun elemento? (s/n): ";
        cin >> response;
        
        if (tolower(response) == 's') {
            string keyToDelete;
            cout << "Ingrese el string a eliminar: ";
            cin >> keyToDelete;
            
            if (hashTable.remove(keyToDelete)) {
                cout << "Elemento '" << keyToDelete << "' eliminado exitosamente." << endl;
                hashTable.display();
                getch();
            } else {
                cout << "Elemento '" << keyToDelete << "' no encontrado." << endl;
            }
        }
    } while (tolower(response) == 's');
    
    closegraph();
    return 0;
}
#include "OpenHashing.cpp"
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int gd = DETECT, gm;
    int width = 800;  // Ancho de la ventana
    int height = 1000; // Alto de la ventana
    initwindow(width, height, "Graphics Window");

    OpenHashing hashTable(13);
    std::vector<int> data;
    int num;

    std::cout << "Ingrese los datos a insertar en la tabla hash (ingrese -1 para terminar):" << std::endl;
    while (true) {
        std::cin >> num;
        if (num == -1) break;
        data.push_back(num);
    }

    std::sort(data.begin(), data.end());

    for (int value : data) {
        hashTable.insert(value);
        hashTable.display();
        getch();
    }

    closegraph();
    return 0;
}


/*
#include "OpenHashing.cpp"

int main() {
    int gd = DETECT, gm;
    int width = 800;  // Ancho de la ventana
    int height = 1000; // Alto de la ventana
    initwindow(width, height, "Graphics Window");

    OpenHashing hashTable(13);
    hashTable.insert(15);
    hashTable.display();
    getch();
    hashTable.insert(25);
    hashTable.display();
    getch();
    hashTable.insert(35);
    hashTable.display();
    getch();
    hashTable.insert(45);
    hashTable.display();
    getch();
    hashTable.insert(55);
    hashTable.display();
    getch();
    hashTable.insert(16);
    hashTable.display();
    getch();

    closegraph();
    return 0;
}
*/
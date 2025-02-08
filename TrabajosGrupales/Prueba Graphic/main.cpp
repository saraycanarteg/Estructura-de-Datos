#include "OpenHashing.cpp"


void insertNumbers(OpenHashing& hashTable) {
    std::vector<int> data;
    int num;

    std::cout << "Ingrese los datos a insertar en la tabla hash (ingrese -1 para terminar):" << std::endl;
    while (true) {
        std::cin >> num;
        if (num == -1) break;
        data.push_back(num);
    }

    std::sort(data.begin(), data.end());

    int gd = DETECT, gm;
    int width = 2000;
    int height = 1200;
    initwindow(width, height, "Open Hashing");

    for (int value : data) {
        hashTable.insert(value);
        hashTable.display();
        getch();
    }

    closegraph();
}

void deleteNumber(OpenHashing& hashTable) {
    std::cout << "Ingrese el numero a eliminar: ";
    int num;
    std::cin >> num;
    
    int gd = DETECT, gm;
    int width = 2000;
    int height = 1200;
    initwindow(width, height, "Open Hashing");
    
    hashTable.remove(num);
    hashTable.display();
    getch();
    
    closegraph();
}

int main() {
    OpenHashing hashTable(13);
    int option;

    do {
        system("cls");
        std::cout << "\n=== MENU HASH TABLE ===\n";
        std::cout << "1. Insertar elementos\n";
        std::cout << "2. Eliminar elemento\n";
        std::cout << "3. Salir\n";
        std::cout << "Ingrese opcion: ";
        std::cin >> option;

        switch(option) {
            case 1:
                insertNumbers(hashTable);
                break;
            case 2:
                deleteNumber(hashTable);
                break;
            case 3:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opcion invalida\n";
                system("pause");
        }
    } while(option != 3);

    return 0;
}
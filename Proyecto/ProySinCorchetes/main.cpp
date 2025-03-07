#include "Simulation.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

void gotoxy(int x, int y) {
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

void clearScreen() {
    system("cls");
}

class MenuOption {
public:
    std::string text;
    MenuOption* next;
    MenuOption(std::string t) : text(t), next(nullptr) {}
};

int main() {
    std::string playerName;
    bool running = true;
    int selectedOption = 0;
    int totalOptions = 3;

    // Crear lista enlazada de opciones
    MenuOption* menuHead = new MenuOption("1. Iniciar Simulacion");
    menuHead->next = new MenuOption("2. Ver Records");
    menuHead->next->next = new MenuOption("3. Salir");

    clearScreen();
    std::cout << "\n\t=== TRAFICO URBANO ===\n\n";
    std::cout << "\tIngrese su nombre: ";
    std::getline(std::cin, playerName);

    while(running) {
        clearScreen();
        std::cout << "\n\t=== TRAFICO URBANO ===\n\n";
        std::cout << "\tJugador: " << playerName << "\n\n";

        // Mostrar opciones usando la lista enlazada
        MenuOption* current = menuHead;
        int i = 0;
        while(current != nullptr) {
            if(i == selectedOption) {
                std::cout << "\t>> " << current->text << " <<\n";
            } else {
                std::cout << "\t   " << current->text << "\n";
            }
            current = current->next;
            i++;
        }

        std::cout << "\n\tUse flechas arriba/abajo y Enter para seleccionar\n";

        char key = _getch();
        
        if(key == 72) { // Flecha arriba
            selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;
        }
        else if(key == 80) { // Flecha abajo
            selectedOption = (selectedOption + 1) % totalOptions;
        }
        else if(key == 13) { // Enter
            switch(selectedOption) {
                case 0: {
                    clearScreen();
                    Simulation simulation;
                    simulation.setPlayerName(playerName);
                    simulation.initialize();
                    simulation.run();
                    system("pause");
                    break;
                }
                case 1: {
                    clearScreen();
                    std::cout << "\n\tRecords del juego:\n";
                    Simulation simulation;
                    simulation.displayRecords();
                    system("pause");
                    break;
                }
                case 2:
                    running = false;
                    break;
            }
        }
    }

    // Liberar memoria de las opciones del menú
    while(menuHead != nullptr) {
        MenuOption* temp = menuHead;
        menuHead = menuHead->next;
        delete temp;
    }

    clearScreen();
    std::cout << "\n\tGracias por jugar!\n\n";
    return 0;
}
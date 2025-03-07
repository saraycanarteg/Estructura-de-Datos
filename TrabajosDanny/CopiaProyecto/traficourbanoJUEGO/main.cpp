#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include "Simulation.h"
#include "pdf_generator.h"

// Función para posicionar el cursor en la consola
void gotoxy(int x, int y)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

void clearScreen()
{
    system("cls");
}

int main()
{
    const int NUM_OPTIONS = 3;
    std::string playerName;
    std::string options[NUM_OPTIONS] = {
        "1. Iniciar Simulacion",
        "2. Ver Records",
        "3. Salir"};
    int selectedOption = 0;
    bool running = true;

    clearScreen();
    std::cout << "\n\t=== TRAFICO URBANO ===\n\n";
    std::cout << "\tIngrese su nombre: ";
    std::getline(std::cin, playerName);

    while (running)
    {
        clearScreen();
        std::cout << "\n\t=== TRAFICO URBANO ===\n\n";
        std::cout << "\tJugador: " << playerName << "\n\n";
        // Mostrar opciones
        for (int i = 0; i < NUM_OPTIONS; i++)
        {
            if (i == selectedOption)
            {
                std::cout << "\t>> " << options[i] << " <<\n";
            }
            else
            {
                std::cout << "\t   " << options[i] << "\n";
            }
        }

        std::cout << "\n\tUse flechas arriba/abajo y Enter para seleccionar\n";

        // Capturar input
        char key = _getch();

        if (key == 72)
        { // Flecha arriba
            selectedOption = (selectedOption - 1 + NUM_OPTIONS) % NUM_OPTIONS;
        }
        else if (key == 80)
        { // Flecha abajo
            selectedOption = (selectedOption + 1) % NUM_OPTIONS;
        }
        else if (key == 13)
        { // Enter
            switch (selectedOption)
            {
            case 0:
            { // Iniciar Simulación
                clearScreen();
                Simulation simulation;
                simulation.setPlayerName(playerName); // Asumiendo que agregaste este método a Simulation
                simulation.initialize();
                simulation.run();
                system("pause");
                break;
            }
            case 1:
            { // Ver Records
                clearScreen();
                std::cout << "\n\tRecords del juego:\n";
                Simulation simulation;
                //simulation.displayRecords();

                // Ejemplo de generación de PDF
                std::vector<GameRecord> records = {
                    {playerName, 100, "2024-03-06"},
                    {"Jugador1", 1000, "2024-03-05"},
                    {"Jugador2", 800, "2024-03-04"}};
                createGameRecordsPDF(records, "records_juego.pdf");

                std::cout << "\n\tSe ha generado el archivo PDF con los records.\n";
                system("pause");
                break;
            }
            case 2: // Salir
                running = false;
                break;
            }
        }
    }

    clearScreen();
    std::cout << "\n\tGracias por jugar!\n\n";
    return 0;
}
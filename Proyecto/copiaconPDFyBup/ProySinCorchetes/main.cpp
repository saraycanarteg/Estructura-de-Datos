#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <ctime>

#include "Simulation.h"

void createBackup();
void restoreBackup();
void gotoxy(int x, int y);
void clearScreen();

class MenuOption
{
public:
    std::string text;
    MenuOption *next;
    MenuOption(std::string t) : text(t), next(nullptr) {}
};


int main()
{
    std::string playerName;
    bool running = true;
    int selectedOption = 0;
    int totalOptions = 4; // Changed from 3 to 4

    // Update menu options
    MenuOption *menuHead = new MenuOption("1. Iniciar Simulacion");
    menuHead->next = new MenuOption("2. Ver Records");
    menuHead->next->next = new MenuOption("3. Restaurar Backup");
    menuHead->next->next->next = new MenuOption("4. Salir");

    clearScreen();
    std::cout << "\n\t=== TRAFICO URBANO ===\n\n";
    std::cout << "\tIngrese su nombre: ";
    std::getline(std::cin, playerName);

    while (running)
    {
        clearScreen();
        std::cout << "\n\t=== TRAFICO URBANO ===\n\n";
        std::cout << "\tJugador: " << playerName << "\n\n";

        // Mostrar opciones usando la lista enlazada
        MenuOption *current = menuHead;
        int i = 0;
        while (current != nullptr)
        {
            if (i == selectedOption)
            {
                std::cout << "\t>> " << current->text << " <<\n";
            }
            else
            {
                std::cout << "\t   " << current->text << "\n";
            }
            current = current->next;
            i++;
        }

        std::cout << "\n\tUse flechas arriba/abajo y Enter para seleccionar\n";

        char key = _getch();

        if (key == 72)
        { // Flecha arriba
            selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;
        }
        else if (key == 80)
        { // Flecha abajo
            selectedOption = (selectedOption + 1) % totalOptions;
        }
        else if (key == 13)
        { // Enter
            switch (selectedOption)
            {
            case 0:
            {
                clearScreen();
                Simulation simulation;
                simulation.setPlayerName(playerName);
                simulation.initialize();
                simulation.run();
                system("pause");
                break;
            }
            case 1:
            {
                clearScreen();
                std::cout << "\n\tRecords del juego:\n";
                Simulation simulation;
                simulation.displayRecords();
                system("pause");
                break;
            }
            case 2:
            {
                clearScreen();
                restoreBackup();
                break;
            }
            case 3:
                running = false;
                break;
            }
        }
    }

    // Liberar memoria de las opciones del menú
    while (menuHead != nullptr)
    {
        MenuOption *temp = menuHead;
        menuHead = menuHead->next;
        delete temp;
    }

    // Crear backup antes de cerrar
    createBackup();

    clearScreen();
    std::cout << "\n\tGracias por jugar!\n\n";
    return 0;
}void createBackup()
{
    // Obtener timestamp para el nombre del archivo
    std::time_t now = std::time(nullptr);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", std::localtime(&now));

    // Definir rutas completas de origen y destino
    std::string sourcePath = "D:\\Universidad\\Tercer Semestre\\Estructura de datos\\RepositorioGit\\Estructura-de-Datos\\TrabajosDanny\\CopiaProyecto\\ProySinCorchetes\\output\\records.txt";
    std::string backupPath = "D:\\Universidad\\Tercer Semestre\\Estructura de datos\\RepositorioGit\\Estructura-de-Datos\\TrabajosDanny\\CopiaProyecto\\ProySinCorchetes\\output\\backup\\backup_" + std::string(timestamp) + ".txt";

    // Copiar el archivo
    std::ifstream source(sourcePath);
    if (!source.is_open())
    {
        std::cout << "\n\tNo se encontró el archivo records.txt\n";
        return;
    }

    std::ofstream dest(backupPath);
    if (!dest.is_open())
    {
        std::cout << "\n\tError al crear el archivo de backup\n";
        source.close();
        return;
    }

    dest << source.rdbuf();

    source.close();
    dest.close();

    std::cout << "\n\tBackup creado exitosamente como: backup_" << timestamp << ".txt\n";
}

// Add after createBackup() function and before gotoxy()

void restoreBackup()
{
    WIN32_FIND_DATAA findData;
    HANDLE hFind;
    MenuOption *backupHead = nullptr;
    MenuOption *backupTail = nullptr;
    int totalBackups = 0;

    // Definir la ruta base
    std::string basePath = "D:\\Universidad\\Tercer Semestre\\Estructura de datos\\RepositorioGit\\Estructura-de-Datos\\TrabajosDanny\\CopiaProyecto\\ProySinCorchetes\\";

    // Buscar archivos de backup
    hFind = FindFirstFileA((basePath + "output\\backup\\backup_*.txt").c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::cout << "\n\tNo se encontraron archivos de backup.\n";
        return;
    }

    do
    {
        if (!backupHead)
        {
            backupHead = new MenuOption(findData.cFileName);
            backupTail = backupHead;
        }
        else
        {
            backupTail->next = new MenuOption(findData.cFileName);
            backupTail = backupTail->next;
        }
        totalBackups++;
    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);

    if (!backupHead)
    {
        std::cout << "\n\tNo se encontraron archivos de backup.\n";
        return;
    }

    // Mostrar lista de backups
    std::cout << "\n\tBackups disponibles:\n\n";
    int i = 1;
    MenuOption *current = backupHead;
    while (current != nullptr)
    {
        std::cout << "\t" << i++ << ". " << current->text << "\n";
        current = current->next;
    }

    // Seleccionar backup
    int selection = 0;
    bool validInput = false;
    std::string input;

    do
    {
        std::cout << "\n\tSeleccione el numero de backup a restaurar (0 para cancelar): ";
        std::getline(std::cin, input);

        // Verificar si la entrada es un número
        bool isNumber = true;
        for (char c : input)
        {
            if (!isdigit(c))
            {
                isNumber = false;
                break;
            }
        }

        if (isNumber && !input.empty())
        {
            selection = std::stoi(input);
            if (selection >= 0 && selection <= totalBackups)
            {
                validInput = true;
            }
            else
            {
                std::cout << "\n\tPor favor, ingrese un numero entre 0 y " << totalBackups << "\n";
            }
        }
        else
        {
            std::cout << "\n\tPor favor, ingrese solo numeros\n";
        }
    } while (!validInput);

    if (selection == 0)
    {
        std::cout << "\n\tOperacion cancelada.\n";
        // Liberar memoria
        while (backupHead != nullptr)
        {
            MenuOption *temp = backupHead;
            backupHead = backupHead->next;
            delete temp;
        }
        return;
    }

    // Encontrar el backup seleccionado
    current = backupHead;
    for (i = 1; i < selection; i++)
    {
        current = current->next;
    }

    // Restaurar el backup seleccionado
    std::string selectedBackup = basePath + "output\\backup\\" + current->text;
    std::string recordsPath = basePath + "output\\records.txt";

    std::ifstream source(selectedBackup);
    if (!source.is_open())
    {
        std::cout << "\n\tError al abrir el archivo de backup.\n";
        // Liberar memoria
        while (backupHead != nullptr)
        {
            MenuOption *temp = backupHead;
            backupHead = backupHead->next;
            delete temp;
        }
        return;
    }

    std::ofstream dest(recordsPath);
    if (!dest.is_open())
    {
        std::cout << "\n\tError al restaurar el backup.\n";
        source.close();
        // Liberar memoria
        while (backupHead != nullptr)
        {
            MenuOption *temp = backupHead;
            backupHead = backupHead->next;
            delete temp;
        }
        return;
    }

    dest << source.rdbuf();

    source.close();
    dest.close();

    // Liberar memoria
    while (backupHead != nullptr)
    {
        MenuOption *temp = backupHead;
        backupHead = backupHead->next;
        delete temp;
    }

    std::cout << "\n\tBackup restaurado exitosamente.\n";
    system("pause");
}

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
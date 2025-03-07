#include "RecordManager.h"
#include "pdf_generator.h"
#include <fstream>
#include <graphics.h>
#include <iostream>
#include <conio.h>
#include <cstring>

RecordManager::RecordManager() : head(nullptr) {}

RecordManager::~RecordManager() {
    while (head != nullptr) {
        Record* temp = head;
        head = head->next;
        delete temp;
    }
}

void RecordManager::addRecord(const std::string& name, int score) {
    // Primero verificar si el jugador ya existe
    Record* current = head;
    while (current != nullptr) {
        if (current->getName() == name) {
            // Si el nuevo puntaje es mayor, actualizar
            if (score > current->score) {
                current->score = score;
                sortRecords(); // Reordenar después de actualizar
            }
            return;
        }
        current = current->next;
    }
    
    // Si el jugador no existe, crear nuevo record
    Record* newRecord = new Record(name, score);
    
    // Si la lista está vacía
    if (head == nullptr) {
        head = newRecord;
        saveRecords(); // Guardar después de cada cambio
        return;
    }
    
    // Si el nuevo record debe ir al inicio
    if (score > head->score) {
        newRecord->next = head;
        head = newRecord;
    } else {
        current = head;
        while (current->next != nullptr && current->next->score >= score) {
            current = current->next;
        }
        newRecord->next = current->next;
        current->next = newRecord;
    }
    
    trimRecords();
    saveRecords(); // Guardar después de cada cambio
    generatePDF(); // Generar PDF actualizado
}

void RecordManager::sortRecords() {
    if (head == nullptr || head->next == nullptr) return;
    
    bool swapped;
    Record* current;
    Record* last = nullptr;
    
    do {
        swapped = false;
        current = head;
        
        while (current->next != last) {
            if (current->score < current->next->score) {
                // Intercambiar puntajes y nombres
                int tempScore = current->score;
                std::string tempName = current->getName();
                
                current->score = current->next->score;
                current->name = current->next->getName();
                
                current->next->score = tempScore;
                current->next->name = tempName;
                
                swapped = true;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

// ...existing code...

void RecordManager::generatePDF() {
    std::string tempFilePath = "temp_records.txt";
    std::ofstream tempFile(tempFilePath);
    if (!tempFile) {
        std::cerr << "Error al crear archivo temporal" << std::endl;
        return;
    }
    
    // Escribir encabezados
    tempFile << "Jugador;Puntaje;Fecha;Posicion\n";
    
    // Escribir records
    Record* current = head;
    int position = 1;
    while (current != nullptr) {
        tempFile << current->getName() << ";"
                << current->getScore() << ";"
                << "2024-03-07" << ";" 
                << position << "\n";
        current = current->next;
        position++;
    }
    
    tempFile.close();
    
    // Generar PDF usando la función existente
    createPDF(tempFilePath.c_str());  // Cambiado aquí para pasar const char*
    
    // Eliminar archivo temporal
    remove(tempFilePath.c_str());
}

void RecordManager::trimRecords() {
    int count = 0;
    Record* current = head;
    
    while (current != nullptr && count < MAX_RECORDS) {
        current = current->next;
        count++;
    }
    
    // If more than max records, delete extras
    if (current != nullptr) {
        Record* prev = head;
        for (int i = 0; i < count - 1; i++) {
            prev = prev->next;
        }
        
        // Delete extra records
        while (current != nullptr) {
            Record* temp = current;
            current = current->next;
            delete temp;
        }
        prev->next = nullptr;
    }
}

void RecordManager::loadRecords() {
    // Clear existing records
    while (head != nullptr) {
        Record* temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
    
    // Try to load from file
    std::ifstream inFile("records.txt");
    if (!inFile) return;
    
    std::string name;
    int score;
    
    while (inFile >> name >> score) {
        addRecord(name, score);
    }
    
    inFile.close();
}

void RecordManager::saveRecords() {
    std::ofstream outFile("records.txt");
    if (!outFile) {
        std::cerr << "Error al abrir archivo records.txt" << std::endl;
        return;
    }
    
    Record* current = head;
    while (current != nullptr) {
        outFile << current->getName() << " " << current->getScore() << std::endl;
        current = current->next;
    }
    
    outFile.close();
}

void RecordManager::displayRecords(int x, int y) {
    // Limpiar pantalla
    system("cls");
    
    // Título
    std::cout << "\n\t=== TOP 10 RECORDS ===\n\n";
    
    // Mostrar records
    Record* current = head;
    int i = 0;
    
    if (current == nullptr) {
        std::cout << "\tNo hay records disponibles.\n";
    }
    
    while (current != nullptr && i < MAX_RECORDS) {
        std::cout << "\t" << (i + 1) << ". " 
                 << current->getName() << " - " 
                 << current->getScore() << " puntos\n";
        current = current->next;
        i++;
    }
    
    std::cout << "\n\tPresione cualquier tecla para continuar...\n";
    _getch();
}

Record* RecordManager::getHead() const {
    return head;
}
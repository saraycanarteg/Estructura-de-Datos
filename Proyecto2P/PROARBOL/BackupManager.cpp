/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Gestionar Backups                                        *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "BackupManager.h"
#include <iostream>
#include <windows.h> // Para las funciones de Windows
#include <direct.h>  // Para mkdir en Windows
#include <sys/stat.h> // Para _stat
#include <fstream>   // Para trabajar con archivos

using namespace std;


void BackupManager::crearCarpetaSiNoExiste(const string& ruta) {
    struct _stat st;

    // Verificar si la carpeta existe
    if (_stat(ruta.c_str(), &st) != 0) {
        // Si la carpeta no existe, la creamos
        if (_mkdir(ruta.c_str()) == 0) {
            cout << "Carpeta creada: " << ruta << endl;
        } else {
            cerr << "Error al crear la carpeta: " << ruta << endl;
        }
    } else {
        cout << "La carpeta ya existe: " << ruta << endl;
    }
}

vector<string> BackupManager::listarArchivosEnCarpeta(const string& carpeta) {
    vector<string> archivos;
    string path = carpeta + "\\*"; // Agregar comodín para buscar todos los archivos
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA(path.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        cerr << "Error al acceder a la carpeta: " << carpeta << endl;
        return archivos;
    }

    do {
        string archivo = findFileData.cFileName;
        if (archivo != "." && archivo != "..") { // Ignorar "." y ".."
            archivos.push_back(archivo);
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);
    return archivos;
}

void BackupManager::restaurarBackup(LibroManager& lista) {
    string carpetaBackup = "backup"; // Carpeta donde se almacenan los backups
    vector<string> archivos = listarArchivosEnCarpeta(carpetaBackup);

    if (archivos.empty()) {
        cout << "No se encontraron archivos de backup en la carpeta " << carpetaBackup << ".\n";
        return;
    }

    // Filtrar archivos de backup
    vector<string> archivosBackup;
    for (const auto& archivo : archivos) {
        if (archivo.find(".txt") != string::npos) {
            archivosBackup.push_back(archivo);
        }
    }

    if (archivosBackup.empty()) {
        cout << "No se encontraron archivos de backup en la carpeta " << carpetaBackup << ".\n";
        return;
    }

    // Mostrar los archivos disponibles
    cout << "Archivos disponibles para restaurar:\n";
    for (size_t i = 0; i < archivosBackup.size(); ++i) {
        cout << i + 1 << ". " << archivosBackup[i] << endl;
    }

    // Seleccionar archivo
    int seleccion;
    cout << "Seleccione un archivo para restaurar (ingrese el número): ";
    cin >> seleccion;

    if (seleccion < 1 || seleccion > archivosBackup.size()) {
        cout << "Selección invalida.\n";
        return;
    }

    string archivoSeleccionado = carpetaBackup + "\\" + archivosBackup[seleccion - 1];
    cout << "Cargando backup desde: " << archivoSeleccionado << endl;

    // Restaurar el archivo de backup
    ifstream archivoBackup(archivoSeleccionado, ios::binary);
    if (!archivoBackup) {
        cerr << "Error al abrir el archivo de backup: " << archivoSeleccionado << endl;
        return;
    }

    ofstream archivoDestino("book_tree.txt", ios::binary);
    if (!archivoDestino) {
        cerr << "Error al abrir el archivo de destino: book_tree.txt" << endl;
        archivoBackup.close();
        return;
    }

    archivoDestino << archivoBackup.rdbuf();

    archivoBackup.close();
    archivoDestino.close();

    cout << "Backup restaurado: " << archivoSeleccionado << endl;
}

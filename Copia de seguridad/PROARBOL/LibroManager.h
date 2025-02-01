/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Interfaz para Realizar una Lista circular doble          *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#ifndef LIBROMANAGER_H
#define LIBROMANAGER_H

#include <iostream>
#include <string>
#include <sstream>
#include "Nodo.h"
#include "Libro.h"
#include "Persona.cpp"
#include "BPlusTree.h"

using namespace std;

class LibroManager {
private:
    BPlusTree isbnTree;
    BPlusTree isniTree;
    BPlusTree bookTree;
    BPlusTree bPlusTree;
    std::string generalFile;
    bool evitarGuardar = false; // Para evitar guardar al restaurar un backup
    string archivoLibros = "book_tree.txt"; // Archivo de libros

public:
    LibroManager();
    LibroManager(int t, const std::string& generalFile);
    void insertLibro(Libro* libro);
    void saveTrees();
    void loadTrees();
    void agregarLibro(const Libro& libro);
    void limpiarLista();
    void imprimirLibros();
  
    void guardarLibrosEnArchivo();
    void cargarLibrosDesdeArchivo();
    void crearBackup(const std::string& nombreArchivo);
    void restaurarBackup(const std::string& nombreArchivo);
    void imprimirTitulosLibros() const;
};

#endif
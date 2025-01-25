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
    std::string generalFile;
    bool evitarGuardar = false; // Para evitar guardar al restaurar un backup
    string archivoLibros = "libros.txt"; // Archivo de libros

public:
    LibroManager(int t, const std::string& generalFile);
    void insertLibro(Libro* libro);
    Libro* searchByISBN(const std::string& isbn);
    Libro* searchByISNI(const std::string& isni);
    void saveTrees();
    void loadTrees();
    void agregarLibro(const Libro& libro);
    void limpiarLista();
    void imprimirLibros();
  
    Libro* buscarLibroPorIsbn(const std::string& isbn);
    Persona buscarAutorPorIsni(const std::string& isni);
    void eliminarLibro(const std::string& titulo);
    void guardarLibrosEnArchivo();
    void cargarLibrosDesdeArchivo();
    void crearBackup(const std::string& nombreArchivo);
    void restaurarBackup(const std::string& nombreArchivo);
   // Libro* buscarLibroPorTitulo(const std::string& titulo);
    void imprimirTitulosLibros() const;
    std::vector<std::string> buscarLibroConAutocompletado(const std::string& prefijo);
    std::vector<std::string> buscarLibroConErroresTipograficos(const std::string& prefijo);
    void listarLibrosPorLetra(const char letra);
    void buscarLibroCortoLargo();
    void buscarLibroPorSubcadena(const std::string& subcadena);
    void buscarLibroPorIsbnConAutocompletado(const std::string& prefijo);
    void buscarLibroCercano(const std::string& ruta, const int anioInicio, const int anioFin);
};

#endif
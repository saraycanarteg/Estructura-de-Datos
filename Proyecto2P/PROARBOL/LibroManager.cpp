/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Realizar una Lista circular doble                        *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "LibroManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <direct.h>        // Para mkdir en Windows
#include <sys/stat.h>      // Para usar _stat
#include "BackupManager.h" // Incluir el archivo de cabecera con la declaración de la función
#include <algorithm>
#include "BPlusTree.h"
#include <cctype>
#include <locale>

using namespace std;

// trim from start (in place)
static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                    { return !std::isspace(ch); }));
}

// trim from end (in place)
static inline void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                         { return !std::isspace(ch); })
                .base(),
            s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s)
{
    ltrim(s);
    rtrim(s);
}

LibroManager::LibroManager()
    : bPlusTree(3),
      isbnTree(3),
      isniTree(3),
      bookTree(3),
      generalFile("libros.txt") {}

LibroManager::LibroManager(int t, const std::string &generalFile)
    : bPlusTree(t),
      isbnTree(t),
      isniTree(t),
      bookTree(t),
      generalFile(generalFile) {}

// Agregar libro
void LibroManager::agregarLibro(const Libro &libro)
{
    // Código para agregar el libro al árbol
    // bPlusTree.insert(libro);

    // Guardar el árbol en un archivo de texto después de agregar el libro
    // bPlusTree.saveTreeToFile("libros.txt");

    /*std::ofstream bookFile("book_tree.txt");

    // Insertar en los árboles B+
    isbnTree.insert(libro.getIsbn(), libro.getTitulo());
    isniTree.insert(libro.getAutor().getIsni(), libro.getTitulo());
    bookTree.insertObject(libro.getIsbn(), libro);
    cout << "Libro agregado: " << libro.getTitulo() << endl;
    // Guardar solo si no se está restaurando un backup
    if (!evitarGuardar) {
        isbnTree.saveToFile("isbn_tree.txt");
        isniTree.saveToFile("isni_tree.txt");
        bookTree.saveNodeToFileObject(bookTree.getRoot(), bookFile);
    }*/

    std::ifstream checkFile("book_tree.txt");
    bool fileExists = checkFile.good();
    checkFile.close();

    std::ofstream bookFile("book_tree.txt", std::ios::app);
    if (!bookFile.is_open())
    {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return;
    }

    const Fecha &fechaPub = libro.getFechaPublicacion();
    const Fecha &fechaNac = libro.getAutor().getFechaNacimiento();

    bookFile << libro.getTitulo() << ";"
             << libro.getIsbn() << ";"
             << libro.getAutor().getNombre() << ";"
             << libro.getAutor().getIsni() << ";"
             << fechaNac.getDia() << "/" << fechaNac.getMes() << "/" << fechaNac.getAnio() << ";"
             << fechaPub.getDia() << "/" << fechaPub.getMes() << "/" << fechaPub.getAnio()
             << endl;

    bookFile.close();
    std::cout << "Libro guardado en book_tree.txt" << endl;

    bookTree.insertObject(libro.getIsbn(), libro);
    isbnTree.insert(libro.getIsbn(), libro.getTitulo());
    isniTree.insert(libro.getAutor().getIsni(), libro.getTitulo());
}

// Imprimir todos los libros
void LibroManager::imprimirLibros()
{
    std::ifstream archivo(generalFile);
    std::string linea;
    while (getline(archivo, linea))
    {
        std::cout << linea << std::endl;
    }
}

/*Buscar libro por título
Libro* LibroManager::buscarLibro(const string& titulo) {
    std::ifstream archivo(generalFile);
    std::string linea;
    while (getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string tituloArchivo, nombreAutor, isni, fechaNac, isbn, fechaPub;
        getline(ss, tituloArchivo, ';');
        if (tituloArchivo == titulo) {
            getline(ss, nombreAutor, ';');
            getline(ss, isni, ';');
            getline(ss, fechaNac, ';');
            getline(ss, isbn, ';');
            getline(ss, fechaPub, ';');
            Persona autor(nombreAutor, isni, Fecha::crearDesdeCadena(fechaNac));
            return new Libro(tituloArchivo, autor, isbn, Fecha::crearDesdeCadena(fechaPub));
        }
    }
    return nullptr;
}*/


// Guardar los libros en el archivo (actualizado)
void LibroManager::guardarLibrosEnArchivo()
{
    ofstream archivo("libros_temp.txt");
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo temporal para guardar.\n\n";
        return;
    }

    // Verificar si el archivo temporal se creó correctamente
    if (FILE *file = fopen("libros_temp.txt", "r"))
    {
        fclose(file);
    }
    else
    {
        cout << "No se pudo crear el archivo temporal correctamente.\n";
        return;
    }

    // Eliminar el archivo de destino si ya existe
    if (remove(archivoLibros.c_str()) != 0)
    {
        // Si el archivo no se puede eliminar, mostrar error
        cout << "Error al eliminar el archivo de destino: " << archivoLibros << endl;
    }

    // Renombrar el archivo temporal a la ubicación final
    if (rename("libros_temp.txt", archivoLibros.c_str()) != 0)
    {
        // Mostrar error si renombrar falla
        perror("Error al renombrar el archivo temporal");
    }
    else
    {
        cout << "Libros guardados en el archivo: " << archivoLibros << endl;
    }
}

// Cargar los libros desde el archivo
void LibroManager::cargarLibrosDesdeArchivo()
{
    ifstream archivo(archivoLibros);
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo para cargar los libros.\n";
        return;
    }

    string linea;
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string titulo, nombreAutor, isni, fechaNacAutor, isbn, fechaPublicacion;
        getline(ss, titulo, ';');
        getline(ss, nombreAutor, ';');
        getline(ss, isni, ';');
        getline(ss, fechaNacAutor, ';');
        getline(ss, isbn, ';');
        getline(ss, fechaPublicacion, ';');

        // Procesar fechas
        Fecha fechaNacimientoAutor = Fecha::crearDesdeCadena(fechaNacAutor);
        Fecha fechaPublicacionLibro = Fecha::crearDesdeCadena(fechaPublicacion);

        Persona autorPersona(nombreAutor, isni, fechaNacimientoAutor);
        Libro libro(titulo, isbn, autorPersona, fechaPublicacionLibro);
        agregarLibro(libro);
    }
    archivo.close();
    cout << "Libros cargados desde el archivo.\n";
}

// Backup
void LibroManager::crearBackup(const string &nombreArchivo)
{
    string carpetaBackup = "backup"; // Carpeta donde se almacenan los backups

    // Asegurarnos de que la carpeta de backups exista
    BackupManager::crearCarpetaSiNoExiste(carpetaBackup);

    // Crear la ruta completa para el archivo de backup dentro de la carpeta "backup"
    string rutaCompleta = carpetaBackup + "\\" + nombreArchivo;

    // Crear el archivo de backup
    ofstream archivo(rutaCompleta);
    if (!archivo.is_open())
    {
        cout << "Error al crear el archivo de backup en la ruta: " << rutaCompleta << endl;
        return;
    }

    std::ifstream archivoOriginal(generalFile);
    std::string linea;
    while (getline(archivoOriginal, linea))
    {
        archivo << linea << std::endl;
    }
    archivoOriginal.close();
    archivo.close();
    cout << "Backup creado correctamente en: " << rutaCompleta << endl;
}

// Restaurar backup y sobreescribir archivo
void LibroManager::restaurarBackup(const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo de backup.\n";
        return;
    }

    cout << "Cargando backup desde: " << nombreArchivo << endl;

    limpiarLista();
    evitarGuardar = true; // Evitar guardar durante la restauración

    string linea;
    while (getline(archivo, linea))
    {
        stringstream ss(linea);
        string titulo, nombreAutor, isni, fechaNacStr, isbn, fechaPubStr;

        // Leer datos del archivo
        getline(ss, titulo, ';');
        getline(ss, nombreAutor, ';');
        getline(ss, isni, ';');
        getline(ss, fechaNacStr, ';');
        getline(ss, isbn, ';');
        getline(ss, fechaPubStr, ';');

        // Parsear la fecha de nacimiento del autor
        int diaNac, mesNac, anioNac;
        sscanf(fechaNacStr.c_str(), "%d/%d/%d", &diaNac, &mesNac, &anioNac);
        Fecha fechaNacimientoAutor(diaNac, mesNac, anioNac);

        // Parsear la fecha de publicación
        int diaPub, mesPub, anioPub;
        sscanf(fechaPubStr.c_str(), "%d/%d/%d", &diaPub, &mesPub, &anioPub);
        Fecha fechaPublicacion(diaPub, mesPub, anioPub);

        // Crear los objetos correspondientes
        Persona autor(nombreAutor, isni, fechaNacimientoAutor);
        Libro libro(titulo, isbn, autor, fechaPublicacion);

        // Agregar libro a la lista
        agregarLibro(libro);
    }

    evitarGuardar = false; // Volver a guardar normalmente
    archivo.close();

    guardarLibrosEnArchivo();
    cout << "Backup restaurado: " << nombreArchivo << endl;
}

// Función para imprimir todos los títulos de los libros
void LibroManager::imprimirTitulosLibros() const
{
    std::ifstream archivo(generalFile);
    std::string linea;
    while (getline(archivo, linea))
    {
        std::stringstream ss(linea);
        std::string titulo;
        getline(ss, titulo, ';');
        cout << titulo << endl;
    }
}

void LibroManager::insertLibro(Libro *libro)
{
    std::ofstream archivo(generalFile, std::ios::app);
    archivo << libro->getTitulo() << ";"
            << libro->getAutor().getNombre() << ";"
            << libro->getAutor().getIsni() << ";"
            << libro->getAutor().getFechaNacimiento().mostrar() << ";"
            << libro->getIsbn() << ";"
            << libro->getFechaPublicacion().mostrar() << std::endl;
    archivo.close();

    isbnTree.insert(libro->getIsbn(), libro->getTitulo());
    isniTree.insert(libro->getAutor().getIsni(), libro->getTitulo());
}

void LibroManager::limpiarLista() {

}

void LibroManager::saveTrees()
{
    isbnTree.saveToFile("isbnTree.txt");
    isniTree.saveToFile("isniTree.txt");
}

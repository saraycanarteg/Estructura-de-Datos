/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZARMADAS ESPE                                       *
 * Proposito:                      Menu principal                                           *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/

#include "Menu.h"
#include "BackupManager.cpp"
#include "Validaciones.cpp"
#include <conio.h>
#include <vector>
#include <sstream>
#include <ctime>
#include "pdf_generator.h"
#include <windows.h>
#include "funciones.h"
#include <algorithm>
#include "BPlusTree.h"
#include "LibroManager.h"

using namespace std;

void eliminarLibro(BPlusTree &arbol, const string &isbn);
std::wstring getExecutablePath()
{
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    std::wstring path(buffer);
    return path.substr(0, path.find_last_not_of(L"\\/"));
}

int ingresarAnio(const string &mensaje)
{
    int anio;
    string input;
    while (true)
    {
        cout << mensaje;
        getline(cin, input); // Usamos getline para permitir validación de la entrada completa

        // Eliminar espacios al inicio y al final de la entrada
        input.erase(0, input.find_first_not_of(' '));
        input.erase(input.find_last_not_of(' ') + 1);

        // Validar si la entrada está vacía
        if (input.empty())
        {
            cout << "Error: Debe ingresar un dato (no puede estar vacío o contener solo espacios)." << endl;
            continue;
        }

        // Validar si la entrada contiene espacios en medio
        if (input.find(' ') != string::npos)
        {
            cout << "Error: No debe ingresar espacios, solo números enteros." << endl;
            continue;
        }

        // Validar que el año sea numérico y tenga 4 dígitos
        try
        {
            anio = stoi(input); // Convertimos la entrada a entero
            if (anio < 1 || anio > 2024)
            {
                throw invalid_argument("Año fuera de rango.");
            }
            break; // Salimos del bucle si el año es válido
        }
        catch (const invalid_argument &e)
        {
            cout << "Error: Ingrese un año válido de 4 dígitos entre 0001 y 2024." << endl;
        }
    }
    return anio;
}

void mostrarMenu(BPlusTree &arbol, BPlusTree &arbol_fechas)
{
    arbol.loadFromFile("book_tree.txt");
    arbol_fechas.change_to_date(arbol.getRoot());

    LibroManager libroManager;
    BackupManager backupManager;

    // backupManager.crearCarpetaSiNoExiste("backup");
    vector<string> opciones = {
        "Agregar libro",
        "Buscar libro",
        "Buscar autor",
        // busquedas binarias
        "Buscar por palabra inicial",
        "Buscar por prefijo de ISBN",
        "Eliminar libro",
        "Ver todos los libros",
        "Exportar en archivo PDF",
        "Crear backup",
        "Restaurar backup",
        "Buscar por rango",
        "Buscar por 10 aniversario",
        "Salir"};
    int seleccion = 0;
    string ruta = "book_tree.txt"; // Ruta del archivo
    int anioInicio, anioFin;

    while (true)
    {
        system("cls");
        cout << "=== Menu Principal ===\n";
        for (size_t i = 0; i < opciones.size(); ++i)
        {
            if (static_cast<int>(i) == seleccion)
                cout << ">> " << opciones[i] << " <<\n";
            else
                cout << "   " << opciones[i] << endl;
        }

        char tecla = _getch();
        if (tecla == 72)
        { // Flecha Arriba
            seleccion = (seleccion - 1 + opciones.size()) % opciones.size();
        }
        else if (tecla == 80)
        { // Flecha Abajo
            seleccion = (seleccion + 1) % opciones.size();
        }
        else if (tecla == '\r')
        { // Enter
            if (opciones[seleccion] == "Agregar libro")
            {
                string titulo, isbn, isni;
                string fechaPub, fechaNac;
                Persona autor;

                do
                {
                    cout << "Ingrese título del libro: ";
                    getline(cin, titulo);
                } while (!Validaciones::validarTitulo(titulo, "Título"));

                do
                {
                    cout << "Ingrese ISBN: ";
                    getline(cin, isbn);
                } while (!Validaciones::validarIsbn(isbn));

                if (!arbol.search(isbn).getTitulo().empty())
                {
                    cout << "El ISBN ya existe. Información del libro existente:\n";
                    cout << endl;
                    arbol.search(isbn).mostrar();
                }
                else
                {
                    // Solicitar ISNI del autor
                    do
                    {
                        cout << "Ingrese ISNI del autor: ";
                        getline(cin, isni);
                    } while (!Validaciones::validarIsni(isni));
                    Libro libroExistente = arbol.searchByIsni(isni);
                    Persona autor;
                    if (!libroExistente.getAutor().getNombre().empty())
                    {
                        cout << "Autor existente encontrado. Usando información del autor.\n";
                        autor = libroExistente.getAutor();
                        fechaNac = autor.getFechaNacimiento().mostrar();
                    }
                    else
                    {
                        string nombreAutor;
                        do
                        {
                            cout << "Ingrese nombre del autor: ";
                            getline(cin, nombreAutor);
                        } while (!Validaciones::validarTituloNombre(nombreAutor, "Nombre del Autor"));

                        // Solicitar fecha de nacimiento del autor
                        do
                        {
                            cout << "Ingrese fecha de nacimiento del autor (DD-MM-YYYY): ";
                            getline(cin, fechaNac);
                        } while (!Validaciones::validarFecha(fechaNac));

                        // Crear el autor
                        Fecha fechaNacimientoAutor = Fecha::crearDesdeCadena(fechaNac);
                        autor = Persona(nombreAutor, isni, fechaNacimientoAutor);
                    }

                    // Solicitar fecha de publicación del libro
                    do
                    {
                        cout << "Ingrese fecha de publicación del libro (DD-MM-YYYY): ";
                        getline(cin, fechaPub);
                    } while (!Validaciones::validarFechaPublicacion(fechaPub, fechaNac));

                    // Crear el libro
                    Fecha fechaPublicacion = Fecha::crearDesdeCadena(fechaPub);
                    string libroInfo = titulo + " " + autor.getNombre() + " " + fechaPub;

                    // Agregar libro al árbol
                    arbol.insert(isbn, libroInfo);
                    arbol.insertObject(isbn, Libro(titulo, isbn, autor, fechaPublicacion));

                    libroManager.agregarLibro(Libro(titulo, isbn, autor, fechaPublicacion));
                    arbol.loadFromFile("book_tree.txt");
                }
            }
            else if (opciones[seleccion] == "Buscar libro")
            {
                string isbn;
                do
                {
                    cout << "Ingrese el ISBN del libro a buscar: ";
                    getline(cin, isbn);
                } while (!Validaciones::validarIsbn(isbn));

                Libro libro;
                arbol.easy_search(arbol.getRoot(), libro, isbn);
                if (!libro.getTitulo().empty())
                {
                    cout << "Información del libro: " << endl;
                    libro.mostrar();
                }
                else
                {
                    cout << "Libro no encontrado.\n";
                }
            }

            else if (opciones[seleccion] == "Buscar autor")
            {
                string isni;
                do
                {
                    cout << "Ingrese el ISNI del autor a buscar: ";
                    getline(cin, isni);
                } while (!Validaciones::validarIsni(isni));

                Libro autor = arbol.searchByIsni(isni);
                if (autor.getAutor().getIsni() == isni)
                {
                    cout << "Autor encontrado:\n";
                    cout << "ISNI: " << autor.getAutor().getIsni() << "\n";
                    cout << "Nombre: " << autor.getAutor().getNombre() << "\n";
                    cout << "Fecha de Nacimiento: " << autor.getAutor().getFechaNacimiento().mostrar() << "\n";
                    cout << endl;
                    vector<Libro> libros = arbol.searchBooksByAuthor(isni);
                    if (!libros.empty())
                    {
                        cout << left << setw(41) << "Título"
                             << setw(25) << "Autor"
                             << setw(25) << "ISNI"
                             << setw(20) << "ISBN"
                             << setw(15) << "Publicación"
                             << setw(15) << "Nac. Autor" << endl;
                        cout << string(140, '-') << endl;
                        for (const auto &libro : libros)
                        {
                            cout << left << setw(40) << libro.getTitulo()
                                 << setw(25) << libro.getAutor().getNombre()
                                 << setw(25) << libro.getAutor().getIsni()
                                 << setw(20) << libro.getIsbn()
                                 << setw(15) << libro.getFechaPublicacion().mostrar()
                                 << setw(15) << libro.getAutor().getFechaNacimiento().mostrar() << endl;
                        }
                    }
                    else
                    {
                        cout << "Libros no encontrados.\n";
                    }
                }
                else
                {
                    cout << "Autor no encontrado.\n";
                }
            }
            else if (opciones[seleccion] == "Buscar por palabra inicial")
            {
                string palabra;
                do
                {
                    cout << "Ingrese título del libro: ";
                    getline(cin, palabra);
                } while (!Validaciones::validarTitulo(palabra, "Título"));

                cout << endl
                     << left;
                cout << setw(40) << "Título"
                     << setw(25) << "Autor"
                     << setw(22) << "ISNI"
                     << setw(20) << "ISBN"
                     << setw(15) << "Publicación"
                     << "Nac. Autor" << endl;

                cout << string(120, '-') << endl; // Línea divisoria
                arbol.search_by_first_word(arbol.getRoot(), palabra);
            }
            else if (opciones[seleccion] == "Buscar por prefijo de ISBN")
            {
                string prefix;
                do
                {
                    cout << "Ingrese los primeros 4 dígitos del ISBN: ";
                    getline(cin, prefix);
                    if (prefix.length() != 4 || !all_of(prefix.begin(), prefix.end(), ::isdigit))
                    {
                        cout << "Error: Ingrese exactamente 4 dígitos numéricos.\n";
                    }
                } while (prefix.length() != 4 || !all_of(prefix.begin(), prefix.end(), ::isdigit));

                cout << endl
                     << left;
                cout << setw(40) << "Título"
                     << setw(25) << "Autor"
                     << setw(22) << "ISNI"
                     << setw(20) << "ISBN"
                     << setw(15) << "Publicación"
                     << "Nac. Autor" << endl;

                cout << string(120, '-') << endl; // Línea divisoria
                arbol.search_by_isbn_prefix(arbol.getRoot(), prefix);
            }
            else if (opciones[seleccion] == "Eliminar libro")
            {
                string isbn;
                do
                {
                    cout << "Ingrese el ISBN del libro a eliminar: ";
                    getline(cin, isbn);
                } while (!Validaciones::validarIsbn(isbn));

                eliminarLibro(arbol, isbn);
            }
            else if (opciones[seleccion] == "Ver todos los libros")
            {
                arbol.loadFromFile("book_tree.txt");
                arbol.traverse();
            }
            else if (opciones[seleccion] == "Exportar en archivo PDF")
            {
                const std::string inputFile = "book_tree.txt";
                createPDF(inputFile);
            }
            else if (opciones[seleccion] == "Crear backup")
            {
                time_t ahora = time(0);
                tm *tiempo = localtime(&ahora);
                stringstream ss;
                ss << (1900 + tiempo->tm_year) << "_" << (1 + tiempo->tm_mon) << "_" << tiempo->tm_mday << "_"
                   << tiempo->tm_hour << "_" << tiempo->tm_min << "_" << tiempo->tm_sec << ".txt";
                arbol.createBackup(ss.str());
                cout << "Backup creado: " << ss.str() << endl;
            }
            else if (opciones[seleccion] == "Restaurar backup")
            {
                backupManager.restaurarBackup(libroManager);
            }
            else if (opciones[seleccion] == "Buscar por rango")
            {
                const std::string inputFile12 = "book_tree.txt";

                while (true)
                {
                    anioFin = ingresarAnio("Ingrese el año de fin (0001 a 2024): ");
                    anioInicio = ingresarAnio("Ingrese el año de inicio (0001 a 2024): ");

                    // Validar que el año final sea mayor al inicial
                    if (anioFin > anioInicio)
                    {
                        break;
                    }
                    else
                    {
                        cout << "Error: El año de fin debe ser mayor al año de inicio, y no pueden ser iguales." << endl;
                    }
                }

                cout << "Registros encontrados entre " << anioInicio << " y " << anioFin << ":\n";
                buscarPorRango(ruta, anioInicio, anioFin); // Assuming you have a method for range search
            }
            else if (opciones[seleccion] == "Buscar por 10 aniversario")
            {
                const std::string inputFile12 = "book_tree.txt";
                buscar10Aniversario(ruta);
            }
            else if (opciones[seleccion] == "Salir")
            {
                break;
            }
            arbol.loadFromFile("book_tree.txt");
            cout << "Presione cualquier tecla para continuar...\n";
            _getch();
        }
        else if (GetAsyncKeyState(VK_F1) & 0x8000)
        { // F1
            std::wstring base_path = getExecutablePath();
            std::wstring ayuda_path = base_path + L"\\output\\ayuda.exe";
            std::string command = "start cmd /C \"" + std::string(ayuda_path.begin(), ayuda_path.end()) + "\"";
            system(command.c_str());
        }
    }
}
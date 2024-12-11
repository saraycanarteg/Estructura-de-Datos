#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include "Menu.cpp"
#include "Libro.h"
#include "Libro.cpp"
#include "Autor.cpp"
#include "Fecha.cpp"
#include "ListaLibros.cpp"
#include "ListaAutores.cpp"
#include "Validation.cpp"

using namespace std;

int main() {
    Validation<string> validacion_string;
    Validation<string> validacion_isbn;

    ListaLibros listaLibros;
    ListaAutores listaAutores;

    Menu main_menu;
    main_menu.set_menu("1. Ingresar libro");
    main_menu.set_menu("2. Buscar libro");
    main_menu.set_menu("3. Mostrar libreria");
    main_menu.set_menu("4. Eliminar libro");
    main_menu.set_menu("5. Recuperar Backup");
    main_menu.set_menu("6. Ayuda");
    main_menu.set_menu("7. Gestion de Autores");
    main_menu.set_menu("8. Buscar por fehca");
    main_menu.set_menu("9. Salir");

    Menu book_entry_menu;
    book_entry_menu.set_menu("1. Ingresar libro");
    book_entry_menu.set_menu("2. Regresar");

    Menu search_menu;
    search_menu.set_menu("1. Buscar por titulo");
    search_menu.set_menu("2. Buscar por isbn");
    search_menu.set_menu("3. Regresar");

    Menu show_menu;
    show_menu.set_menu("1. Mostrar por autor");
    show_menu.set_menu("2. Mostrar por libros");
    show_menu.set_menu("3. Regresar");

    Menu elimination_menu;
    elimination_menu.set_menu("1. Eliminar por titulo");
    elimination_menu.set_menu("2. Eliminar por isbn");
    elimination_menu.set_menu("3. Regresar");

    Menu help_menu;
    help_menu.set_menu("1. Ver Ayuda");
    help_menu.set_menu("2. Regresar");

    Menu autor_menu;
    autor_menu.set_menu("1. Registrar autor");
    autor_menu.set_menu("2. Buscar autor por ID");
    autor_menu.set_menu("3. Eliminar autor");
    autor_menu.set_menu("4. Modificar autor");
    autor_menu.set_menu("5. Mostrar autores");
    autor_menu.set_menu("6. Regresar");

    Menu buscar_autor_menu;
    buscar_autor_menu.set_menu("1. Buscar autor por ID");
    buscar_autor_menu.set_menu("2. Buscar libros de un autor");
    buscar_autor_menu.set_menu("3. Regresar");

    string titulo, isbn;
    int op;
    int sub_menu_op;
    Libro* libroEncontrado;

    do {
        op = main_menu.coursor("REGISTRO Y CONSULTA DE LIBROS");

        switch (op) {
            case 1: {
                string nombreAutor, apellidoAutor, id, nacionalidad, editorial;

                sub_menu_op = book_entry_menu.coursor("REGISTRO DE LIBROS");
                system("cls");

                if (sub_menu_op == 2) {
                    break;
                } else {
                    do {
                        cout << "INGRESO DE LIBRO\n\n";
                        cout << "Ingrese el titulo del libro: ";
                        titulo = validacion_string.enter_a_char_or_string_with_may(20);
                        cout << "\n--------------------------------------";
                        cout << "\nIngrese los nombres del autor: ";
                        nombreAutor = validacion_string.enter_a_char_or_string_with_may(20);
                        cout << "\nIngrese los apellidos del autor: ";
                        apellidoAutor = validacion_string.enter_a_char_or_string_with_may(20);
                        cout << "\nIngrese el ID del autor: ";
                        id = validacion_string.enter_a_char_or_string_with_may(20);
                        cout << "\nIngrese la nacionalidad del autor: ";
                        nacionalidad = validacion_string.enter_a_char_or_string_with_may(20);
                        cout << "\n--------------------------------------";

                        if (titulo.empty() || nombreAutor.empty() || apellidoAutor.empty()) {
                            cout << "\n\nDebe ingresar todos los campos requeridos. Intente de nuevo...\n" << endl;
                            system("pause");
                            system("cls");
                        }
                    } while (titulo.empty() || nombreAutor.empty() || apellidoAutor.empty());

                    Autor autorLibro(nombreAutor, apellidoAutor, id, nacionalidad);
                    string fechaIngresada = validacion_string.enter_date();

                    // Parsear la fecha
                    stringstream ss(fechaIngresada);
                    int dia, mes, anio;
                    char delimiter;
                    ss >> dia >> delimiter >> mes >> delimiter >> anio;

                    Fecha fechaPublicacion(dia, mes, anio);

                    bool isbn_valido = false;
                    do {
                        cout << "\nIngrese el ISBN del libro: ";
                        isbn = validacion_string.enter_a_char_or_string_only_nums(10);

                        if (validacion_isbn.validate_isbn(isbn)) {
                            isbn_valido = true;
                        } else {
                            cout << "El ISBN ingresado no es válido. Por favor, intente nuevamente." << endl;
                        }
                    } while (!isbn_valido);

                    cout << "\nIngrese editorial del libro: ";
                    editorial = validacion_string.enter_a_char_or_string_with_may(20);

                    Libro nuevoLibro(titulo, autorLibro, fechaPublicacion, isbn, editorial);
                    listaLibros.registrarLibro(nuevoLibro);
                    cout << "\nLibro registrado exitosamente." << endl;
                    system("pause");
                }
                break;
            }

            case 2: {
                sub_menu_op = buscar_autor_menu.coursor("BÚSQUEDA");
                system("cls");

                switch (sub_menu_op) {
                    case 1: {
                        cout<<"Ingrese el titulo de libro: ";
                        titulo = validacion_string.enter_a_char_or_string_with_may(20);
                        libroEncontrado = listaLibros.buscarLibroPorTitulo(titulo);
                        if (libroEncontrado) {
                            cout << "Libro encontrado:" << endl;
                            cout << "Titulo: " << libroEncontrado->getTitulo() << endl;
                            cout << "Autor: " << libroEncontrado->getAutor().getNombreCompleto() << endl;
                            cout << "Fecha de publicacion: " << libroEncontrado->getFechaPublicacion().getFechaComoString() << endl;
                            cout << "ISBN: " << libroEncontrado->getIsbn() << endl;
                            system("pause");
                        } else {
                            cout << "\n\nNo se encontro el libro.\n" << endl;
                            system("pause");
                        }
                        break;
                    }
                    case 2: {
                        string idAutor;
                        cout << "BÚSQUEDA DE LIBROS POR AUTOR\n\n";
                        cout << "Ingrese el ID del autor: ";
                        idAutor = validacion_string.enter_a_char_or_string_with_may(10);

                        Autor* autorBuscado = listaAutores.buscarAutorPorId(idAutor);
                        if (autorBuscado) {
                            ListaLibros librosDelAutor;
                            listaLibros.buscarLibrosPorAutor(idAutor, librosDelAutor);

                            if (librosDelAutor.obtenerTamano() > 0) {
                                cout << "Libros del autor " << autorBuscado->getNombreCompleto() << ":\n";
                                librosDelAutor.imprimirLibros();
                            } else {
                                cout << "No se encontraron libros para este autor." << endl;
                            }
                        } else {
                            cout << "No se encontró un autor con ese ID." << endl;
                        }
                        system("pause");
                        break;
                    }
                }
                break;
            }

            case 3: {
                sub_menu_op = show_menu.coursor("IMPRESION DE DATOS");
                system("cls");
                switch (sub_menu_op) {
                    case 1:
                        cout << "LIBROS DEL AUTOR:" << endl;
                        // TODO: Implementar
                        system("pause");
                        break;
                    case 2:
                        listaLibros.imprimirLibros();
                        system("pause");
                        break;
                }
                break;
            }

            case 4: {
                sub_menu_op = elimination_menu.coursor("ESCOJA UN LIBRO PARA ELIMINAR");
                system("cls");
                switch (sub_menu_op) {
                    case 1: {
                        cout << "ELIMINACION POR TITULO\n\n";
                        cout << "Ingrese el titulo del libro a eliminar: ";
                        titulo = validacion_string.enter_a_char_or_string_with_may(20);
                        cout << endl << endl;

                        if (listaLibros.eliminarLibroPorTitulo(titulo)) {
                            cout << "Libro eliminado exitosamente." << endl;
                        } else {
                            cout << "No se encontró un libro con ese título." << endl;
                        }
                        system("pause");
                        break;
                    }
                    case 2:{
                        cout<<"ELIMINACION POR ISBN"<<endl;
                        /* code */
                        system("pause");
                        break;
                    }
                    case 3:{
                        break;
                    }
                    break;
                  }
            }
            case 5: { // Nueva opción para restaurar backup
                string fechaHoraIngresada;
                cout << "Ingrese la fecha y hora del respaldo en el formato dd.mm.aaaa.HH.MM.SS: ";
                cin >> fechaHoraIngresada;
                listaLibros.restaurarBackup(fechaHoraIngresada);
                system("pause");
                break;
            }
            case 6: { // Ayuda
                Ayuda::mostrarAyuda();
                system("pause");
                break;
            }
            case 7: {
                op = autor_menu.coursor("GESTIÓN DE AUTORES");
                system("cls");
                switch (op) {
                    case 1: { // Registrar autor
                        string nombreAutor, apellidoAutor, id, nacionalidad;
                        cout << "REGISTRO DE AUTOR\n\n";
                        cout << "Ingrese los nombres del autor: ";
                        nombreAutor = validacion_string.enter_a_char_or_string_with_may(20);
                        cout << "Ingrese los apellidos del autor: ";
                        apellidoAutor = validacion_string.enter_a_char_or_string_with_may(20);
                        cout << "Ingrese el ID del autor: ";
                        id = validacion_string.enter_a_char_or_string_with_may(10);
                        cout << "Ingrese la nacionalidad del autor: ";
                        nacionalidad = validacion_string.enter_a_char_or_string_with_may(20);

                        Autor nuevoAutor(nombreAutor, apellidoAutor, id, nacionalidad);
                        listaAutores.registrarAutor(nuevoAutor);
                        cout << "\nAutor registrado exitosamente." << endl;
                        system("pause");
                        break;
                    }
                    case 2: { // Buscar autor por ID
                        string id;
                        cout << "BUSQUEDA DE AUTOR POR ID\n\n";
                        cout << "Ingrese el ID del autor: ";
                        id = validacion_string.enter_a_char_or_string_with_may(10);
                        
                        Autor* autorEncontrado = listaAutores.buscarAutorPorId(id);
                        if (autorEncontrado) {
                            cout << "Autor encontrado:" << endl;
                            cout << "Nombre: " << autorEncontrado->getNombreCompleto() << endl;
                            cout << "ID: " << autorEncontrado->getId() << endl;
                            cout << "Nacionalidad: " << autorEncontrado->getNacionalidad() << endl;
                        } else {
                            cout << "No se encontró un autor con ese ID." << endl;
                        }
                        system("pause");
                        break;
                    }
                    case 3: { // Eliminar autor
                        string id;
                        cout << "ELIMINACIÓN DE AUTOR\n\n";
                        cout << "Ingrese el ID del autor a eliminar: ";
                        id = validacion_string.enter_a_char_or_string_with_may(10);
                        
                        if (listaAutores.eliminarAutorPorId(id)) {
                            cout << "Autor eliminado exitosamente." << endl;
                        } else {
                            cout << "No se encontró un autor con ese ID." << endl;
                        }
                        system("pause");
                        break;
                    }
                    case 4: { // Modificar autor
                        /*string id;
                        cout << "MODIFICACIÓN DE AUTOR\n\n";
                        cout << "Ingrese el ID del autor a modificar: ";
                        id = validacion_string.enter_a_char_or_string_with_may(10);
                        
                        Autor* autorExistente = listaAutores.buscarAutorPorId(id);
                        if (autorExistente) {
                            string nombreAutor, apellidoAutor, nacionalidad;
                            cout << "Ingrese los nuevos nombres del autor (actual: " << autorExistente->getNombre() << "): ";
                            nombreAutor = validacion_string.enter_a_char_or_string_with_may(20);
                            cout << "Ingrese los nuevos apellidos del autor (actual: " << autorExistente->getApellido() << "): ";
                            apellidoAutor = validacion_string.enter_a_char_or_string_with_may(20);
                            cout << "Ingrese la nueva nacionalidad del autor (actual: " << autorExistente->getNacionalidad() << "): ";
                            nacionalidad = validacion_string.enter_a_char_or_string_with_may(20);

                            Autor nuevoAutor(nombreAutor, apellidoAutor, id, nacionalidad);
                            if (listaAutores.modificarAutorPorId(id, nuevoAutor)) {
                                cout << "Autor modificado exitosamente." << endl;
                            } else {
                                cout << "Error al modificar el autor." << endl;
                            }
                        } else {
                            cout << "No se encontró un autor con ese ID." << endl;
                        }
                        system("pause");
                        break;*/
                    }
                    case 5: { // Mostrar autores
                        listaAutores.imprimirAutores();
                        system("pause");
                        break;
                    }
                }
                break;
            }
case 8: {
    string fechaInicio, fechaFin;
    ListaLibros listaLibros;

    cout << "BUSCAR LIBROS POR FECHA\n\n";
    
    // Solicitar la fecha de inicio
    cout << "Ingrese la fecha de inicio (formato dd.MM.yyyy.HH.mm.ss): ";
    getline(cin, fechaInicio);
    
    // Solicitar la fecha de fin
    cout << "Ingrese la fecha de fin (formato dd.MM.yyyy.HH.mm.ss): ";
    getline(cin, fechaFin);
    
    // Llamar al método de búsqueda por rango de fechas
    listaLibros.buscarLibrosPorFechaIngreso(fechaInicio, fechaFin);
    
    system("pause");
    break;
}


            
       }
       
   }while(op!=9);
}

        



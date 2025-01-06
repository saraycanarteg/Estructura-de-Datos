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

using namespace std;

int main()
{
    Validation<string> validacion_string, validacion_isbn;
    Validation<int> validacion_int;
    Validation<char> validacion_char;

    ListaLibros listaLibros;
    ListaAutores listaAutores;

    listaLibros.cargarLibrosDesdeCSV();

    Menu main_menu;
    main_menu.set_menu("1. Ingresar libro");
    main_menu.set_menu("2. Buscar libro");
    main_menu.set_menu("3. Mostrar libreria");
    main_menu.set_menu("4. Eliminar libro");
    main_menu.set_menu("5. Editar libro");
    main_menu.set_menu("6. Recuperar Backup");
    main_menu.set_menu("7. Gestion de Autores");
    main_menu.set_menu("8. Buscar por anio de publicacion");
    main_menu.set_menu("9. Busquedas binarias por cabeza");
    main_menu.set_menu("10. Salir");

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

    Menu identificador_para_menu_modificacion;
    identificador_para_menu_modificacion.set_menu("1. Por Titulo");
    identificador_para_menu_modificacion.set_menu("2. Por ISBN");

    Menu campo_a_modificar_menu;
    campo_a_modificar_menu.set_menu("Titulo");
    campo_a_modificar_menu.set_menu("Autor");
    campo_a_modificar_menu.set_menu("Fecha de Publicacion");
    campo_a_modificar_menu.set_menu("ISBN");
    campo_a_modificar_menu.set_menu("Editorial");
    campo_a_modificar_menu.set_menu("Regresar");

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
    autor_menu.set_menu("4. Mostrar autores");
    autor_menu.set_menu("5. Regresar");

    Menu buscar_autor_menu;
    buscar_autor_menu.set_menu("1. Buscar por titulo");
    buscar_autor_menu.set_menu("2. Buscar libros de un autor");
    buscar_autor_menu.set_menu("3. Regresar");

    Menu binary_search;
    // saray
    binary_search.set_menu("1. Buscar libros proximos a cumplir 1 decada de aniversario");
    binary_search.set_menu("2. Buscar libros libros con el mismo prefijo de ISBN");
    binary_search.set_menu("3. Libros con titulos similares (palabras clave)");
    binary_search.set_menu("4. Buscar por letra inicial");
    binary_search.set_menu("5. Buscar libros de la misma editorial");
    binary_search.set_menu("6. Buscar libros publicados en la misma decada");
    binary_search.set_menu("7. Regresar");

    string titulo, isbn, nombreAutor, apellidoAutor, id, nacionalidad, editorial;
    int op, sub_menu_op;
    Libro *libroEncontrado;

    do
    {
        op = main_menu.coursor("REGISTRO Y CONSULTA DE LIBROS");

        switch (op)
        {
        case 1:
        {
            sub_menu_op = book_entry_menu.coursor("REGISTRO DE LIBROS");
            system("cls");

            if (sub_menu_op == 2)
            {
                break;
            }
            else
            {
                do
                {
                    cout << "INGRESO DE LIBRO\n\nIngrese el titulo del libro: ";
                    titulo = validacion_string.enter_a_char_or_string_with_may_and_nums(20);
                    cout << "\n--------------------------------------";

                    cout << "\nIngrese el ID del autor (Formato: A001): ";
                    id = validacion_string.enter_a_char_or_string_with_may_and_nums(4);

                    if (listaLibros.existeAutorPorId(id))
                    {
                        bool autorExistente = true;
                        cout << "\n\nEl autor con ID " << id << " ya existe. Se utilizará la información existente." << endl;

                        std::vector<Autor> autoresExistentes = listaLibros.cargarAutoresDesdeCSV();
                        for (const auto &autorExistente : autoresExistentes)
                        {
                            if (autorExistente.getId() == id)
                            {
                                nombreAutor = autorExistente.getNombre();
                                apellidoAutor = autorExistente.getApellido();
                                nacionalidad = autorExistente.getNacionalidad();
                                break;
                            }
                        }
                    }
                    else
                    {
                        cout << "\nIngrese los nombres del autor: ";
                        nombreAutor = validacion_string.enter_a_char_or_string_with_may(20);
                        cout << "\nIngrese los apellidos del autor: ";
                        apellidoAutor = validacion_string.enter_a_char_or_string_with_may(20);
                        cout << "\nIngrese la nacionalidad del autor: ";
                        nacionalidad = validacion_string.enter_a_char_or_string_with_may(20);
                        cout << "\n--------------------------------------";
                        // autorExistente = false;
                    }
                    cout << "\n--------------------------------------";

                    if (titulo.empty() || nombreAutor.empty() || apellidoAutor.empty() || nacionalidad.empty() || !validacion_string.validar_id_autor(id))
                    {
                        if (!validacion_string.validar_id_autor(id))
                        {
                            cout << "\n\nId no valido. Intente de nuevo...";
                        }
                        cout << "\n\nDebe ingresar todos los campos requeridos. Intente de nuevo...\n"
                             << endl;
                        system("pause");
                        system("cls");
                    }

                } while (titulo.empty() || nombreAutor.empty() || apellidoAutor.empty() || id.empty() || nacionalidad.empty() || !validacion_string.validar_id_autor(id));

                Autor autorLibro(nombreAutor, apellidoAutor, id, nacionalidad);
                string fechaIngresada = validacion_string.enter_date();

                // Parsear la fecha
                stringstream ss(fechaIngresada);
                int dia, mes, anio;
                char delimiter;
                ss >> dia >> delimiter >> mes >> delimiter >> anio;

                Fecha fechaPublicacion(dia, mes, anio);

                bool isbn_valido = false;
                do
                {
                    cout << "\nIngrese el ISBN del libro: ";
                    isbn = validacion_string.enter_a_char_or_string_only_nums(10);

                    if (validacion_isbn.validate_isbn(isbn))
                    {
                        isbn_valido = true;
                    }
                    else
                    {
                        cout << "\n\nEl ISBN ingresado no es válido. Por favor, intente nuevamente." << endl;
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

        case 2:
        {
            system("cls");
            sub_menu_op = buscar_autor_menu.coursor("BÚSQUEDA");

            switch (sub_menu_op)
            {
            case 1:
            {
                cout << "\nIngrese el titulo de libro: ";
                titulo = validacion_string.enter_a_char_or_string_with_may_and_nums(20);
                libroEncontrado = listaLibros.buscarLibroPorTitulo(titulo);
                if (libroEncontrado)
                {
                    cout << "\nLibro encontrado:" << endl;
                    cout << "Titulo: " << libroEncontrado->getTitulo() << endl;
                    cout << "Autor: " << libroEncontrado->getAutor().getNombreCompleto() << endl;
                    cout << "Fecha de publicacion: " << libroEncontrado->getFechaPublicacion().getFechaComoString() << endl;
                    cout << "ISBN: " << libroEncontrado->getIsbn() << endl;
                    system("pause");
                }
                else
                {
                    cout << "\n\nNo se encontro el libro.\n"
                         << endl;
                    system("pause");
                }
                break;
            }
            case 2:
            {
                string idAutor;
                cout << "BUSQUEDA DE LIBROS POR AUTOR\n\n";
                cout << "Ingrese el ID del autor: ";
                idAutor = validacion_string.enter_a_char_or_string_with_may_and_nums(10);
                system("pause");
                break;
            }
            }
            break;
        }

        case 3:
        {
            system("cls");
            sub_menu_op = show_menu.coursor("IMPRESION DE DATOS");
            switch (sub_menu_op)
            {
            case 1:
                cout << "\n\nLIBROS DEL AUTOR:" << endl;
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

        case 4:
        {
            sub_menu_op = elimination_menu.coursor("ESCOJA UN LIBRO PARA ELIMINAR");
            system("cls");
            switch (sub_menu_op)
            {
            case 1:
            {
                cout << "ELIMINACION POR TITULO\n\n";
                cout << "Ingrese el titulo del libro a eliminar: ";
                titulo = validacion_string.enter_a_char_or_string_with_may_and_nums(20);
                cout << endl
                     << endl;

                if (listaLibros.eliminarLibroPorTitulo(titulo))
                {
                    cout << "\nLibro eliminado exitosamente." << endl;
                }
                else
                {
                    cout << "\nNo se encontró un libro con ese titulo." << endl;
                }
                system("pause");
                break;
            }
            case 2:
            {
                cout << "ELIMINACION POR ISBN" << endl;
                /* code */
                system("pause");
                break;
            }
            case 3:
            {
                break;
            }
            break;
            }
            break;
        }
        case 5:
        {
            system("cls");
            string identificador;
            op = identificador_para_menu_modificacion.coursor("ESCOJA EL TIPO DE BUSQUEDA PARA LA MODIFICACION");
            bool validation;
            do
            {
                if (op == 1)
                {
                    cout << "\nIngrese un Titulo para la busqueda: ";
                    identificador = validacion_string.enter_a_char_or_string_with_may_and_nums(20);
                    if (identificador.empty())
                    {
                        validation = false;
                        cout << "\nNo debe dejar el campo vacio. Intente de nuevo... \n\n";
                        system("pause");
                        system("cls");
                    }
                    else
                    {
                        validation = true;
                    }
                }
                else
                {
                    cout << "\nIngrese un ISBN para la busqueda: ";
                    identificador = validacion_string.enter_a_char_or_string_only_nums(20);
                    if (!validacion_isbn.validate_isbn(identificador) || identificador.empty())
                    {
                        cout << "\nDebe ingresar un ISBN valido. Intente de nuevo...\n";
                        validation = false;
                        system("pause");
                        system("cls");
                    }
                    else
                    {
                        validation = true;
                    }
                }

            } while (!validation);

            string campo_a_modificar = campo_a_modificar_menu.coursor_string("ATRIBUTO A MODIFICAR");

            listaLibros.modificarLibroEnCSV(identificador, campo_a_modificar);

            break;
        }
        case 6:
        { // Nueva opción para restaurar backup
            string fechaHoraIngresada;
            cout << "Ingrese la fecha y hora del respaldo en el formato dd.mm.aaaa.HH.MM.SS: ";
            fechaHoraIngresada = validacion_string.validation_buckup();
            listaLibros.restaurarBackup(fechaHoraIngresada);
            system("pause");
            break;
        }
        case 7:
        {
            op = autor_menu.coursor("GESTIÓN DE AUTORES");
            system("cls");
            switch (op)
            {
            case 1:
            { // Registrar autor
                string nombreAutor, apellidoAutor, id, nacionalidad;
                do
                {

                    cout << "REGISTRO DE AUTOR\n\n";
                    cout << "Ingrese los nombres del autor: ";
                    nombreAutor = validacion_string.enter_a_char_or_string_with_may(20);
                    cout << "\nIngrese los apellidos del autor: ";
                    apellidoAutor = validacion_string.enter_a_char_or_string_with_may(20);
                    cout << "\nIngrese el ID del autor: ";
                    id = validacion_string.enter_a_char_or_string_with_may_and_nums(10);
                    cout << "\nIngrese la nacionalidad del autor: ";
                    nacionalidad = validacion_string.enter_a_char_or_string_with_may(20);
                    if (nombreAutor.empty() || apellidoAutor.empty() || id.empty() || nacionalidad.empty() || !validacion_string.validar_id_autor(id))
                    {
                        if (!validacion_string.validar_id_autor(id))
                        {
                            cout << "\nId ingresado no valido. Intente de nuevo...";
                        }
                        cout << "\nDebe ingresar todos los campos requeridos. Intente de nuevo...\n";
                        system("pause");
                        system("cls");
                    }

                } while (nombreAutor.empty() || apellidoAutor.empty() || id.empty() || nacionalidad.empty() || !validacion_string.validar_id_autor(id));

                Autor nuevoAutor(nombreAutor, apellidoAutor, id, nacionalidad);
                listaAutores.registrarAutor(nuevoAutor);
                cout << "\nAutor registrado exitosamente." << endl;
                system("pause");
                break;
            }
            case 2:
            { // Buscar autor por ID
                string id;
                cout << "BUSQUEDA DE AUTOR POR ID\n\n";
                cout << "Ingrese el ID del autor: ";
                id = validacion_string.enter_a_char_or_string_with_may_and_nums(10);

                Autor *autorEncontrado = listaAutores.buscarAutorPorId(id);
                if (autorEncontrado)
                {
                    cout << "Autor encontrado:" << endl;
                    cout << "Nombre: " << autorEncontrado->getNombreCompleto() << endl;
                    cout << "ID: " << autorEncontrado->getId() << endl;
                    cout << "Nacionalidad: " << autorEncontrado->getNacionalidad() << endl;
                }
                else
                {
                    cout << "No se encontró un autor con ese ID." << endl;
                }
                system("pause");
                break;
            }
            case 3:
            { // Eliminar autor
                string id;
                cout << "ELIMINACIÓN DE AUTOR\n\n";
                cout << "Ingrese el ID del autor a eliminar: ";
                id = validacion_string.enter_a_char_or_string_with_may_and_nums(10);

                if (listaAutores.eliminarAutorPorId(id))
                {
                    cout << "Autor eliminado exitosamente." << endl;
                }
                else
                {
                    cout << "No se encontró un autor con ese ID." << endl;
                }
                system("pause");
                break;
            }
            case 4:
            { // Modificar autor
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
            case 5:
            { // Mostrar autores
                listaAutores.imprimirAutores();
                system("pause");
                break;
            }
            }
            break;
        }
        case 8:
        {
            int anioInicio, anioFin;

            cout << "\nIngrese el anio inicial del rango: ";
            anioInicio = validacion_int.enter_a_number("int");
            cout << "\nIngrese el anio final del rango: ";
            anioFin = validacion_int.enter_a_number("int");

            if (anioInicio > anioFin)
            {
                cout << "\nEl anio inicial no puede ser mayor que el anio final. Intente de nuevo." << endl;
                break;
            }

            listaLibros.filtrarLibrosPorRangoDeAnios(anioInicio, anioFin);
            system("pause");
            break;
        }
        case 9:
        {
            system("cls");
            sub_menu_op = binary_search.coursor("BUSQUEDAS BINARIAS");

            switch (sub_menu_op)
            {
            case 1:
            {
                system("cls");
                cout << "BUSQUEDA DE LIBROS PROXIMOS A CUMPLIR UNA DECADA DE PUBLICACION\n\n";
                listaLibros.buscarLibrosDecada();
                system("pause");
                break;
            }
            case 2:
            {
                system("cls");
                cout << "BUSQUEDA DE LIBROS POR PREFIJO DE ISBN\n\n";
                string prefijo;
                cout << "Ingrese los primeros tres digitos del ISBN: ";
                prefijo = validacion_string.enter_a_char_or_string_only_nums(3);
                listaLibros.buscarLibrosPorPrefijoISBN(prefijo);
                system("pause");
                break;
            }
            case 3:
            {
                system("cls");
                cout << "BUSQUEDA DE LIBROS POR PALABRA CLAVE EN EL TITULO\n\n";
                string palabraClave;
                cout << "Ingrese una palabra clave para buscar en los tiitulos: ";
                palabraClave = validacion_string.enter_a_char_or_string_with_may_and_nums(20);
                listaLibros.buscarLibrosPorPalabraClave(palabraClave);
                system("pause");
                break;
            }
            case 4:
            {
                system("cls");
                cout << "BUSQUEDA POR LETRA INICIAL\n\n";
                string letra;
                cout << "Ingrese un caracter: ";
                letra = validacion_string.enter_a_char_or_string(12);
                cout << endl;
                cout << endl;
                if (letra.length() > 1)
                {
                    cout << "\n\nSe ha ingresado mal de un caracter. Vuelva a intentar...\n\n";
                    system("pause");
                    system("cls");
                }
                else
                {
                    char new_letra = letra[0];
                    listaLibros.buscarLibrosPorLetraInicial(new_letra);
                    system("pause");
                }

                break;
            }
            case 5:
            {
                system("cls");
                cout << "BUSQUEDA POR EDITORIAL\n\n";
                cout << "Ingrese una editorial: ";
                editorial = validacion_string.enter_a_char_or_string_with_may_and_nums(25);
                cout << endl;
                listaLibros.buscarLibrosPorEditorial(editorial);
                system("pause");
                break;
            }
            case 6:
            {
                system("cls");
                cout << "BUSQUEDA LIBROS POR DÉCADA\n\n";
                cout << "Ingrese un año (ej: 1990, 2000): ";
                int year = validacion_int.enter_a_number("int");
                cout << endl;
                listaLibros.buscarLibrosPorDecada(year);
                system("pause");
                break;
            }
            default:
                break;
            }
            break;
        }
        }

    } while (op != 10);
}

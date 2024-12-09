#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include "Menu.cpp"
#include "Libro.h"
#include "Libro.cpp"
#include "Autor.cpp" 
#include "Fecha.cpp"
#include "ListaLibros.cpp"
#include "Validation.cpp"
/*#include "Libro.h"
#include "Autor.h" 
#include "Fecha.h"
#include "ListaLibros.h"*/

using namespace std;

int main(){

    Validation<string> validacion_string;
    Validation<string> validacion_isbn;

    ListaLibros listaLibros;
    
    Menu main_menu;
    main_menu.set_menu("1. Ingresar libro");
    main_menu.set_menu("2. Buscar libro");
    main_menu.set_menu("3. Mostrar libreria");
    main_menu.set_menu("4. Eliminar libro");
    main_menu.set_menu("5. Recuperar Backup");
    main_menu.set_menu("6. Ayuda");
    main_menu.set_menu("7. Salir");

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

    string titulo, isbn;
    Libro* libroEncontrado;

    int op;
    int sub_menu_op;

    do{  
        op = main_menu.coursor("REGISTRO Y CONSULTA DE LIBROS");

        switch (op){
        case 1:{
            string nombreAutor, apellidoAutor;

            sub_menu_op = book_entry_menu.coursor("REGISTRO DE LIBROS");
            system("cls");

            if(sub_menu_op==2){
                break;
            }else{
                do{
                    cout<<"INGRESO DE LIBRO\n\n";
                    cout << "Ingrese el titulo del libro: ";    
                    titulo = validacion_string.enter_a_char_or_string_with_may(20);
                    cout << "\nIngrese los nombres del autor: ";
                    nombreAutor = validacion_string.enter_a_char_or_string_with_may(20);
                    cout << "\nIngrese los apellidos del autor: ";
                    apellidoAutor = validacion_string.enter_a_char_or_string_with_may(20);
                    if((titulo == " ") && (nombreAutor == " ") && (apellidoAutor == " ")){
                        cout<<"\n\nDebe ingresar todos los campos requeridos. Intente de nuevo...\n"<<endl;
                        system("pause");
                        system("cls");
                    }

                }while((titulo == " ") && (nombreAutor == " ") && (apellidoAutor == " "));

                Autor autorLibro(nombreAutor, apellidoAutor);

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
                    isbn = validacion_string.enter_a_char_or_string_only_nums(10); // Captura la entrada completa del usuario

                    if (validacion_isbn.validate_isbn(isbn)) {
                        isbn_valido = true; // ISBN válido
                    } else {
                        cout << "El ISBN ingresado no es válido. Por favor, intente nuevamente." << endl;
                    }
                } while (!isbn_valido);

                Libro nuevoLibro(titulo, autorLibro, fechaPublicacion, isbn);
                listaLibros.registrarLibro(nuevoLibro);
                cout << "\nLibro registrado exitosamente." << endl;
                system("pause");
            }
            break;
        }
        case 2:{
            sub_menu_op = search_menu.coursor("BUSQUEDA DE LIBROS");
            system("cls");
            switch (sub_menu_op){
            case 1:{
                cout<<"BUSQUEDA POR LIBRO\n\n";
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
            case 2:
                cout<<"\nBUSQUEDA POR ISBN\n\n";
                system("pause");
                break;
            case 3:
                break;
            }
            break;
        }
        case 3:{
            sub_menu_op = show_menu.coursor("IMPRESION DE DATOS");
            system("cls");
            switch (sub_menu_op){
            case 1:
                cout<<"LIBROS DEL AUTOR: "<<endl;
                //TODO
                system("pause");
                break;
            case 2:
                listaLibros.imprimirLibros();
                system("pause");
                break;
            case 3:
                /* code */
                break;
            }

            break;
        }
        case 4:{
            
            sub_menu_op = elimination_menu.coursor("ESCOJA UN LIBRO PARA ELIMINAR");
            system("cls");
            switch (sub_menu_op){
            case 1:{
                cout<<"ELIMINACION POR TITULO"<<endl<<endl;
                cout << "Ingrese el titulo del libro a eliminar: ";
                titulo = validacion_string.enter_a_char_or_string_with_may(20);
                cout<<endl<<endl;

                if (listaLibros.eliminarLibroPorTitulo(titulo)) {
                    cout << "Libro eliminado exitosamente." << endl;
                } else {
                    cout << "No se encontro un libro con ese titulo." << endl;
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
            case 3:
                break;
            }
            break;
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
            default:
                cout<<"GRACIAS POR USARNOS\n";
                cout<<op;
            break;
        }
    }while(op!=7);
}

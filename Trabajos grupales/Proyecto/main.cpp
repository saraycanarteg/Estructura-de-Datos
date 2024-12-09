#include <stdlib.h>
#include <iostream>
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

    ListaLibros listaLibros;
    
    Menu main_menu;
    main_menu.set_menu("1. Ingresar libro");
    main_menu.set_menu("2. Buscar libro");
    main_menu.set_menu("3. Mostrar libreria");
    main_menu.set_menu("4. Eliminar libro");
    main_menu.set_menu("5. Salir");

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

    string titulo, isbn;
    Libro* libroEncontrado;

    int op;
    int sub_menu_op;

    do{  
        op = main_menu.coursor("REGISTRO Y CONSULTA DE LIBROS");
        cout<<op<<endl;

        switch (op){
        case 1:{
            string nombreAutor, apellidoAutor;

            sub_menu_op = book_entry_menu.coursor("REGISTRO DE LIBROS");
            system("cls");

            if(sub_menu_op==2){
                break;
            }else{
                cout<<"INGRESO DE LIBRO\n\n";
                cout << "Ingrese el titulo del libro: ";    
                titulo = validacion_string.enter_a_char_or_string_with_may(20);
                cout << "\nIngrese los nombres del autor: ";
                nombreAutor = validacion_string.enter_a_char_or_string_with_may(20);
                cout << "\nIngrese los apellidos del autor: ";
                apellidoAutor = validacion_string.enter_a_char_or_string_with_may(20);
                Autor autorLibro(nombreAutor, apellidoAutor);

                cout << "\nIngrese la fecha de publicacion (dd mm aaaa): ";
                int dia, mes, anio;         //Ingrese validaciones de fecha
                cin >> dia >> mes >> anio;
                fflush(stdin);
                Fecha fechaPublicacion(dia, mes, anio);

                cout << "\nIngrese el ISBN del libro: "; //Ingrese validaciones isbn
                cin >> isbn;
                fflush(stdin);
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
            default:
                cout<<"GRACIAS POR USARNOS\n";
                cout<<op;
            break;
        }
    }while(op!=5);
}

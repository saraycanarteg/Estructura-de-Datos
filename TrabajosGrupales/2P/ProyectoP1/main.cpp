#include <iostream>
#include "Menu.cpp"
#include "Libro.h"
#include "Libro.cpp"
#include "Autor.cpp" 
#include "Fecha.cpp"
#include "ListaLibros.cpp"
/*#include "Libro.h"
#include "Autor.h" 
#include "Fecha.h"
#include "ListaLibros.h"*/

using namespace std;

int main(){
    Menu main_menu;
    ListaLibros listaLibros;
    main_menu.set_menu("1. Ingresar libro");
    main_menu.set_menu("2. Buscar libro");
    main_menu.set_menu("3. Mostrar libreria");
    main_menu.set_menu("4. Eliminar libro");
    main_menu.set_menu("5. Salir");

    Menu book_entry_menu;
    book_entry_menu.set_menu("1. Regresar");

    Menu search_menu;
    search_menu.set_menu("1. Buscar por titulo");
    search_menu.set_menu("2. Buscar por autor");
    search_menu.set_menu("3. Buscar por isbn");
    search_menu.set_menu("4. Regresar");

    Menu show_menu;
    show_menu.set_menu("1. Mostrar por autor");
    show_menu.set_menu("2. Mostrar por libros");
    show_menu.set_menu("3. Regresar");

    Menu elimination_menu;
    elimination_menu.set_menu("1. Regresar");

    string titulo, isbn;
    Libro* libroEncontrado;

    int op;
    do{  
        op = main_menu.coursor("REGISTRO Y CONSULTA DE LIBROS");
        cout<<op<<endl;

        switch (op)
        {
        case 1:{
            op = book_entry_menu.coursor("INGRESO DE LIBROS");
            cout << "Ingrese el titulo del libro: ";
            cin.ignore();
            getline(cin, titulo);
            cout << "Ingrese el autor del libro: ";
            string nombreAutor, apellidoAutor, nacionalidadAutor;
            cin >> nombreAutor >> apellidoAutor >> nacionalidadAutor;
            Autor autorLibro(nombreAutor, apellidoAutor, nacionalidadAutor);
            cout << "Ingrese la fecha de publicacion (dd mm aaaa): ";
            int dia, mes, anio;
            cin >> dia >> mes >> anio;
            Fecha fechaPublicacion(dia, mes, anio);
            cout << "Ingrese el ISBN del libro: ";
            cin >> isbn;
            Libro nuevoLibro(titulo, autorLibro, fechaPublicacion, isbn);
            listaLibros.registrarLibro(nuevoLibro);
            cout << "Libro registrado exitosamente." << endl;
            break;
            }
        case 2:{
            op = search_menu.coursor("BUSQUEDA DE LIBROS");
            cout << "Ingrese el título del libro a buscar: ";
            cin.ignore();
            getline(cin, titulo);
            libroEncontrado = listaLibros.buscarLibroPorTitulo(titulo);
            if (libroEncontrado) {
                cout << "Libro encontrado:" << endl;
                cout << "Titulo: " << libroEncontrado->getTitulo() << endl;
                cout << "Autor: " << libroEncontrado->getAutor().getNombreCompleto() << endl;
                cout << "Fecha de publicacion: " << libroEncontrado->getFechaPublicacion().getFechaComoString() << endl;
                cout << "ISBN: " << libroEncontrado->getIsbn() << endl;
            } else {
                cout << "No se encontró el libro." << endl;
            }
            break;}
        case 3:{
            op = show_menu.coursor("IMPRESION DE DATOS");

            listaLibros.imprimirLibros();
            break;}
        case 4:{
            
            op = elimination_menu.coursor("ESCOJA UN LIBRO PARA ELIMINAR");
            cout << "Ingrese el titulo del libro a eliminar: ";
            cin.ignore();
            getline(cin, titulo);
            if (listaLibros.eliminarLibroPorTitulo(titulo)) {
                cout << "Libro eliminado exitosamente." << endl;
            } else {
                cout << "No se encontro un libro con ese titulo." << endl;
            }
            break;}
        }

    }while(op!=5);
}
#include "Menu.cpp"

using namespace std;

int main(){
    Menu main_menu;
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


    int op;
    do{  
        op = main_menu.coursor("REGISTRO Y CONSULTA DE LIBROS");
        cout<<op<<endl;

        switch (op)
        {
        case 1:{
            int op = book_entry_menu.coursor("INGRESO DE LIBROS");
            break;
            }
        case 2:{
            op = search_menu.coursor("BUSQUEDA DE LIBROS");
            
            break;}
        case 3:{
            op = show_menu.coursor("IMPRESION DE DATOS");
            
            break;}
        case 4:{
            
            op = elimination_menu.coursor("ESCOJA UN LIBRO PARA ELIMINAR");
            break;}
        }

    }while(op!=5);
    

}

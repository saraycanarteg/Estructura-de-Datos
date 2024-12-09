#include "Menu.cpp"

using namespace std;

int main(){
    Menu menu;

    menu.set_menu("1. Opcion 1");
    menu.set_menu("2. Opcion 2");
    menu.set_menu("3. Opcion 3");
    menu.set_menu("4. Opcion 4");

    int op = menu.coursor("TITULO");
      
    cout<< op;

    

}

#include "Menu.cpp"

int main(){
    Menu menu;
    menu.set_menu("1 op");
    menu.set_menu("2 op");
    menu.set_menu("3 op");
    int op = menu.coursor("menu");
    cout << op;
}
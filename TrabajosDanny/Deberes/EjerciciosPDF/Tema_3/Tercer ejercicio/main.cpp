#include <iostream>
#include "BuscadorArray.cpp"

int main(){
    std::cout<<std::endl<<std::endl;
    
    int a[] = {0, -5, 2, 2, 4, 3, 4, 7, 4, -3, 10};
    int n = sizeof(a) / sizeof(a[0]);
    
    BuscadorArray buscador(a, n);
    int retorno = buscador.buscarElementoPosicion(0, n - 1);
    
    if (retorno == -1){
        std::cout << "No se ha encontrado ningun elemento que coincida con su posicion" << std::endl;
    }else{
        std::cout << "El elemento en la posicion a[" << retorno << "] es igual a " << buscador.obtenerElemento(retorno) << std::endl;
    }
    
    std::cout<<std::endl<<std::endl;
    return 0;
}
#include "Nodo.h"

using namespace std;

template<typename T>
class Lista_Circular {
private:
    Nodo<T>* cabeza;
public:
    Lista_Circular();
    void Insertar_cabeza(T);
    void Buscar(T);
    void Eliminar(T);
    void Mostrar();
};

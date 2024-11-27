#include "Nodo.h"

template<typename T>
class Lista_Doble {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola; // Nuevo puntero para rastrear el final de la lista
public:
    Lista_Doble();
    void Insertar_cabeza(T);
    void Insertar_cola(T);
    void Buscar(T);
    void Eliminar(T);
    void Mostrar();
    void MostrarReversa(); // Nueva función para mostrar en orden inverso
};

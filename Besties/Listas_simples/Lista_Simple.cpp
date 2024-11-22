
#include "Lista_Simple.h"

using namespace std;


template <typename T>
Lista_Simple<T>::Lista_Simple()
{
    cabeza = NULL;
}

template <typename T>
void Lista_Simple<T>::Insertar_cabeza(T _dato)
{
    Nodo<T>* nuevo = new Nodo<T>(_dato);
    if (cabeza == NULL) {
        cabeza = nuevo;
    }
    else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != NULL) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
    }
}

/*template<typename T> 
 void Lista_Simple<T>::Insertar_cola(T _dato) {
    Nodo<T>* nuevo = new Nodo(_dato);
    if (cabeza == NULL) {
        cabeza = nuevo;
    }
    else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != NULL) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
    }
}*/

template<typename T> 
 void Lista_Simple<T>::Buscar(T _dato) {
    Nodo<T>* aux = cabeza;
    while (aux != NULL) {
        if (aux->getDato() == _dato) {
            cout << "El dato " << _dato << " si se encuentra en la lista" << endl;
            return;
        }
        aux = aux->getSiguiente();
    }
    cout << "El dato " << _dato << " no se encuentra en la lista" << endl;
}

template<typename T> 
 void Lista_Simple<T>::Eliminar(T _dato) {
    Nodo<T>* aux = cabeza;
    Nodo<T>* anterior = NULL;
    while (aux != NULL) {
        if (aux->getDato() == _dato) {
            if (anterior == NULL) {
                cabeza = aux->getSiguiente();
            }
            else {
                anterior->setSiguiente(aux->getSiguiente());
            }
            delete aux;
            cout << "El dato " << _dato << " se ha eliminado de la lista" << endl;
            return;
        }
        anterior = aux;
        aux = aux->getSiguiente();
    }
    cout << "El dato " << _dato << " no se encuentra en la lista" << endl;
}

template<typename T> 
 void Lista_Simple<T>::Mostrar() {
    Nodo<T>* aux = cabeza;
    while (aux != NULL) {
        cout << aux->getDato() << " -> ";
        aux = aux->getSiguiente();
    }
    cout << "NULL" << endl;
}
template <typename T>
Lista_Simple<T>* Lista_Simple<T>::EliminarCaracter(char caracter) {
    Lista_Simple<T>* nuevaLista = new Lista_Simple<T>();
    Nodo<T>* actual = cabeza;

    while (actual != NULL) {
        T datoOriginal = actual->getDato();
        T datoModificado = datoOriginal; // Copia inicial del dato

        // Manejo para cadenas (std::string)
        if (typeid(T) == typeid(std::string)) {
            // Eliminación manual del carácter
            std::string strDato = datoOriginal;
            std::string strModificado;
            for (char c : strDato) {
                if (c != caracter) {
                    strModificado += c;
                }
            }
            datoModificado = strModificado; // Asignar el valor modificado
        }
        // Manejo para Persona
        else if (typeid(T) == typeid(Persona)) {
            Persona personaOriginal = datoOriginal; // Copia del objeto Persona
            std::string nombreModificado, apellidoModificado;

            // Eliminar el carácter del nombre
            for (char c : personaOriginal.getNombre()) {
                if (c != caracter) {
                    nombreModificado += c;
                }
            }

            // Eliminar el carácter del apellido
            for (char c : personaOriginal.getApellido()) {
                if (c != caracter) {
                    apellidoModificado += c;
                }
            }

            // Crear una nueva instancia de Persona con los valores modificados
            datoModificado = Persona(personaOriginal.getCedula(), nombreModificado, apellidoModificado);
        }

        // Para otros tipos, no modificar el dato
        nuevaLista->Insertar_cabeza(datoModificado);
        actual = actual->getSiguiente();
    }

    return nuevaLista;
}

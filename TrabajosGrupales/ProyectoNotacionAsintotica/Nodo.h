#ifndef NODO_H
#define NODO_H

class Nodo {
private:
    int dato;
    Nodo* siguiente;
    
public:
    Nodo(int valor);
    int getDato() const;
    void setDato(int valor);
    Nodo* getSiguiente() const;
    void setSiguiente(Nodo* sig);
};

#endif
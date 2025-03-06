#ifndef NUMERO_H
#define NUMERO_H

class Numero {
private:
    int valor;
    Numero* siguiente;

public:
    Numero(int val);
    int getValor() const;
    void setSiguiente(Numero* num);
    Numero* getSiguiente() const;
};

#endif
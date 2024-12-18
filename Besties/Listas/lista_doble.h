#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H

#include "lista_base.h"

class ListaDoble : public ListaBase {
public:
    ListaDoble();

    void insertar(const Persona& p) override;
    bool eliminar(int id) override;
    Persona* buscar(int id) override;
    void mostrar() override;
    void ordenar() override;
};

#endif // LISTA_DOBLE_H
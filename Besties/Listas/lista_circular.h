#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H

#include "lista_base.h"

class ListaCircular : public ListaBase {
public:
    ListaCircular();

    void insertar(const Persona& p) override;
    bool eliminar(int id) override;
    Persona* buscar(int id) override;
    void mostrar() override;
    void ordenar() override;
    bool exportarACSV(const std::string& nombreArchivo) override;
};

#endif // LISTA_CIRCULAR_H
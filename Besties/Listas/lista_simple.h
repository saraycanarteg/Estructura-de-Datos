#ifndef LISTA_SIMPLE_H
#define LISTA_SIMPLE_H

#include "lista_base.h"
#include "persona.h"

class ListaSimple : public ListaBase {
public:
    ListaSimple();

    void insertar(const Persona& p) override;
    bool eliminar(int id) override;
    Persona* buscar(int id) override;
    void mostrar() override;
    void ordenar() override;
    bool exportarACSV(const std::string& nombreArchivo);
};

#endif // LISTA_SIMPLE_H
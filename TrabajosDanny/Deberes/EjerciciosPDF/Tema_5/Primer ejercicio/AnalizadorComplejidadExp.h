#ifndef ANALIZADOR_COMPLEJIDAD_EXP_H
#define ANALIZADOR_COMPLEJIDAD_EXP_H

class AnalizadorComplejidadExp {
private:
    int n;
    bool perteneceOGrande1(int n) const;
    bool perteneceOGrande2(int n) const;

public:
    AnalizadorComplejidadExp(int valor);
    void analizarComplejidad() const;
};

#endif
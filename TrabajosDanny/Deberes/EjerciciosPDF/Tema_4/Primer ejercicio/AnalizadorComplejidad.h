#ifndef ANALIZADOR_COMPLEJIDAD_H
#define ANALIZADOR_COMPLEJIDAD_H

class AnalizadorComplejidad {
private:
    double n;
    
    double f1(double n) const;  // log(n)^2
    double f2(double n) const;  // 5 log(n)
    double f3(double n) const;  // 10n
    double f4(double n) const;  // n log10(n)
    double f5(double n) const;  // n^(1+a) con 0 < a < 1
    double f6(double n) const;  // n^2
    double f7(double n) const;  // n^2 log(n)

public:
    AnalizadorComplejidad(double valor);
    void analizarComplejidad();
};

#endif
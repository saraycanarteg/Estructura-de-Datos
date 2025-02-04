#ifndef AUTOR_H
#define AUTOR_H

#include <string>
using namespace std;

class Autor {
private:
    string nombre;
    string apellido;

public:
    // Constructores
    Autor(); 
    Autor(string nombre, string apellido);

    // Getters
    string getNombre() const;
    string getApellido() const;
    string getNombreCompleto() const;

    // Setters
    void setNombre(string nombre);
    void setApellido(string apellido);
};

#endif
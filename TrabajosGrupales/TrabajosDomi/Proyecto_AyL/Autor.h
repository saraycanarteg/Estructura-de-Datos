#ifndef AUTOR_H
#define AUTOR_H

#include <string>
using namespace std;

class Autor {
private:
    string nombre;
    string apellido;
    string id; 
    string nacionalidad;
 // Asociación con libros

public:
    // Constructores
    Autor(); 
    Autor(string nombre, string apellido, string id, string nacionalidad);

    // Getters
    string getNombre() const;
    string getApellido() const;
    string getNombreCompleto() const;
    string getId() const;
    string getNacionalidad() const;

    // Setters
    void setNombre(string nombre);
    void setApellido(string apellido);
    void setId(string id);
    void setNacionalidad(string id);


};

#endif

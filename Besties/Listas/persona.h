#ifndef PERSONA_H
#define PERSONA_H

#include <string>

class Persona {
private:
    int id;
    std::string nombre;
    std::string apellido;

public:
    // Constructores
    Persona();
    Persona(int _id, std::string _nombre, std::string _apellido);

    // Getters
    int getId() const;
    std::string getNombre() const;
    std::string getApellido() const;

    // Setters
    void setId(int _id);
    void setNombre(std::string _nombre);
    void setApellido(std::string _apellido);

    // Método para mostrar información
    void mostrar() const;
};

#endif // PERSONA_H
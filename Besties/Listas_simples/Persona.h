#pragma once
#include <string>
#include <iostream>

class Persona {
private:
    std::string cedula;
    std::string nombre;
    std::string apellido;

public:
    Persona(std::string _cedula = "", std::string _nombre = "", std::string _apellido = "") {
        cedula = _cedula;
        nombre = _nombre;
        apellido = _apellido;
    }

    // Getters
    std::string getCedula() const { return cedula; }
    std::string getNombre() const { return nombre; }
    std::string getApellido() const { return apellido; }

    // Setters
    void setCedula(std::string _cedula) { cedula = _cedula; }
    void setNombre(std::string _nombre) { nombre = _nombre; }
    void setApellido(std::string _apellido) { apellido = _apellido; }

    // Operador de comparación
    bool operator==(const Persona& otra) const {
        return cedula == otra.cedula;
    }

    // Operador de inserción
    friend std::ostream& operator<<(std::ostream& os, const Persona& p) {
        os << "Cédula: " << p.cedula << " | Nombre: " << p.nombre << " | Apellido: " << p.apellido;
        return os;
    }
};
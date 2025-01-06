#include "Fecha.h"
#include <sstream>
#include <iomanip>

Fecha::Fecha() : dia(1), mes(1), anio(2024) {}

Fecha::Fecha(int dia, int mes, int anio) : dia(dia), mes(mes), anio(anio) {

}

// Getters
int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

// Setters
void Fecha::setDia(int dia) {
    if (dia > 0 && dia <= 31) {
        this->dia = dia;
    }
}

void Fecha::setMes(int mes) {
    if (mes > 0 && mes <= 12) {
        this->mes = mes;
    }
}

void Fecha::setAnio(int anio) {
    if (anio > 0) {
        this->anio = anio;
    }
}

std::string Fecha::getFechaComoString() const {
    std::stringstream ss;
    
    // Aseguramos que el día y mes tengan dos dígitos
    ss << std::setfill('0') 
       << std::setw(2) << dia << "/" 
       << std::setw(2) << mes << "/";

    // Verificamos si el año es de 2 dígitos, si es así, lo completamos a 4
    if (anio < 1000) {
        ss << "20" << std::setw(2) << std::setfill('0') << anio;
    } else {
        ss << anio;
    }

    return ss.str();
}

#include "Fecha.h"
#include <sstream>
#include <iomanip>

Fecha::Fecha() : dia(1), mes(1), anio(2024) {}

Fecha::Fecha(int dia, int mes, int anio) : dia(dia), mes(mes), anio(anio) {
    if (!esFechaValida()) {
        // Si la fecha no es válida, establecer una fecha por defecto
        this->dia = 1;
        this->mes = 1;
        this->anio = 2024;
    }
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

string Fecha::getFechaComoString() const {
    stringstream ss;
    ss << setfill('0') 
       << setw(2) << dia << "/"
       << setw(2) << mes << "/"
       << anio;
    return ss.str();
}

bool Fecha::esFechaValida() const {
    // Validaciones básicas
    if (mes < 1 || mes > 12) return false;
    if (dia < 1) return false;

    // Días por mes (simplificado, no considera años bisiestos)
    int diasEnMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Considerar años bisiestos (simplificado)
    if (mes == 2) {
        if (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0)) {
            return dia <= 29;
        }
        return dia <= 28;
    }

    return dia <= diasEnMes[mes];
}
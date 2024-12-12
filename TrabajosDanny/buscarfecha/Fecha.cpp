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

string Fecha::getFechaComoString() const {
    stringstream ss;
    ss << setfill('0') 
       << setw(2) << dia << "/"
       << setw(2) << mes << "/"
       << anio;

    cout<<ss.str()<<endl;
    return ss.str();
}

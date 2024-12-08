#include <iostream>
#include "Estudiante.h"

using namespace std;

Estudiante::Estudiante(){}

Estudiante::Estudiante(string _nombres, string _apellidos, string _cedula, string _correo){
    nombres = _nombres;
    apellidos = _apellidos;
    cedula = _cedula;
    correo = _correo;
}

void Estudiante::set_Nombres(string _nombres){
    nombres = _nombres;
}

void Estudiante::set_Apellidos(string _apellidos){
    apellidos = _apellidos;
}

void Estudiante::set_Cedula(string _cedula){
    cedula = _cedula;
}

void Estudiante::set_Correo(string _correo){
    correo = _correo;
}

string Estudiante::get_Nombres(){
    return nombres;
}

string Estudiante::get_Apellidos(){
    return apellidos;
}

string Estudiante::get_Cedula(){
    return cedula;
}

string Estudiante::get_Correo(){
    return correo;
}
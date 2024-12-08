#include <iostream>
#include <string>

using namespace std;

class Estudiante{

    private:
        string nombres;
        string apellidos;

        string cedula;
        string correo;

    public:

        Estudiante();
        Estudiante(string _nombres, string _apellidos, string _cedula, string _correo);

        void set_Nombres(string _nombres);
        void set_Apellidos(string _apellidos);
        void set_Cedula(string _cedula);
        void set_Correo(string _correo);

        string get_Nombres();
        string get_Apellidos();
        string get_Cedula();
        string get_Correo();
};
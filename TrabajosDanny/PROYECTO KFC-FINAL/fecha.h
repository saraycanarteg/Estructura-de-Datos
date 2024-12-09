#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;

struct Fecha {
 float dia, mes, anio;
};
Fecha actual;

string Convert2(float number){
    ostringstream buff;
    buff<<number;
    return buff.str();
}

Fecha hoy (){
  time_t t;
  t = time(NULL);
  struct tm*f;
  f= localtime(&t);
  Fecha aux;
  aux.anio = f -> tm_year +1900;
  aux.mes = f-> tm_mon +1;
  aux.dia = f-> tm_mday;
  return aux;
}

string mostrarfecha (Fecha f){
    string fecha, dia, mes, anio;
    dia= Convert2(f.dia);
    mes= Convert2(f.mes);
    anio= Convert2(f.anio);
    fecha="FECHA: \t"+ dia + "/"+ mes + "/"+ anio+"\n";
    return fecha;
}

string imprimirfecha(){
 Fecha actual;
 actual = hoy();
 string fecha = mostrarfecha(actual);
 return fecha;
}

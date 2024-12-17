#include <conio.h>
#include <iostream>
#include <iomanip>
#include <limits>
#include <windows.h>

using namespace std;

class Ayuda
{
public:
     static bool checkF1()
     {
          // Usar Windows API para detectar F1
          return (GetAsyncKeyState(VK_F1) & 0x8000) != 0;
     }

     static void mostrarAyuda()
     {
          system("cls"); // Limpiar pantalla

          cout << "\n===== SISTEMA DE AYUDA DEL REGISTRO DE LIBROS =====\n\n";

          cout << setw(25) << left << "OPCION" << "DESCRIPCION\n";
          cout << string(50, '-') << endl;

          cout << setw(25) << left << "1. Ingresar libro"
               << "Registra un nuevo libro en la biblioteca.\n";
          cout << "   Requiere:\n";
          cout << "   - Titulo del libro\n";
          cout << "   - Nombre y apellido del autor\n";
          cout << "   - Nacionalidad del autor\n";
          cout << "   - Fecha de publicaciin\n";
          cout << "   - ISBN\n\n";

          cout << setw(25) << left << "2. Buscar libro"
               << "Encuentra libros por titulo o ISBN.\n\n";

          cout << setw(25) << left << "3. Mostrar libreria"
               << "Lista todos los libros registrados.\n\n";

          cout << setw(25) << left << "4. Eliminar libro"
               << "Remueve un libro de la biblioteca por titulo o ISBN.\n\n";

          cout << setw(25) << left << "5. Salir"
               << "Cierra el programa.\n\n";

          cout << "CARACTERISTICAS ESPECIALES:\n";
          cout << "- Guardado automatico en ListaLibros.txt\n";
          cout << "- Archivos de backup con cada actualización de la lista en output\n";
          cout << "- Carga de libros al iniciar programa\n";
          cout << "- Presione F1 en cualquier momento para ver esta ayuda\n";

          cout << "\n===== FIN DE LA AYUDA =====\n";

          cout << "\nPresione Enter para continuar...";
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cin.get();
     }
};
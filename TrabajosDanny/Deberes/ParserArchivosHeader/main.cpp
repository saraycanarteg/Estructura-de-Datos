#include "HeaderParser.cpp"
#include <iostream>
#include <string>
#include <limits>

//----------------------------------------------------------
// ... existing includes ...
#include <conio.h>

void mostrarPrototipos(HeaderParser &parser, int seleccionado)
{
    system("cls");
    std::cout << "\nSeleccione una función con las flechas y presione Enter:\n"
              << std::endl;

    for (int i = 0; i < parser.getPrototypesCount(); i++)
    {
        if (i == seleccionado)
        {
            std::cout << "> ";
        }
        else
        {
            std::cout << "  ";
        }
        std::cout << parser.getPrototypeAt(i) << std::endl;
    }
}

void analizarComplejidad(const char* prototipo, const std::string& rutaH)
{
    if (!prototipo) return;
    
    // Buscar la última ocurrencia de "\" en la ruta
    size_t pos = rutaH.find_last_of("\\");
    std::string nombreArchivo;
    
    if (pos != std::string::npos) {
        nombreArchivo = rutaH.substr(pos + 1);
    } else {
        nombreArchivo = rutaH;
    }
    
    // Quitar la extensión .h y agregar .cpp
    nombreArchivo = nombreArchivo.substr(0, nombreArchivo.length() - 1) + "cpp";
    
    // Obtener el directorio actual
    std::string rutaCpp = rutaH.substr(0, pos + 1) + nombreArchivo;
    
    // Llamar al script de Python con los argumentos necesarios
    std::string comando = "python archivo.py \"" + rutaH + "\" \"" + std::string(prototipo) + "\" \"" + rutaCpp + "\"";
    system(comando.c_str());
}

//----------------------------------------------------------
void limpiarBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool verificarExtension(const std::string &ruta)
{
    size_t punto = ruta.find_last_of(".");
    if (punto == std::string::npos)
        return false;

    std::string extension = ruta.substr(punto);
    return extension == ".h";
}

int main()
{
    std::string ruta;
    bool rutaValida = false;

    do
    {
        std::cout << "\n=== Analizador de Archivos Header ===" << std::endl;
        std::cout << "Ingrese la ruta del archivo .h (o 'salir' para terminar): ";
        std::getline(std::cin, ruta);

        if (ruta == "salir")
        {
            std::cout << "Programa terminado." << std::endl;
            return 0;
        }

        if (!verificarExtension(ruta))
        {
            std::cout << "Error: El archivo debe tener extensión .h" << std::endl;
            continue;
        }

        HeaderParser parser(ruta.c_str());

        if (!parser.parseFile())
        {
            std::cout << "Error: No se pudo procesar el archivo." << std::endl;
            std::cout << "Verifique que la ruta sea correcta y que el archivo exista." << std::endl;
            continue;
        }

        std::cout << "\nPrototipos encontrados:" << std::endl;
        std::cout << "======================" << std::endl;
        parser.printPrototypes();
        system("pause");
        int seleccionado = 0;
        char tecla;
        
        do
        {
            mostrarPrototipos(parser, seleccionado);
            tecla = _getch();

            if (tecla == 72 && seleccionado > 0) // Flecha arriba
                seleccionado--;
            else if (tecla == 80 && seleccionado < parser.getPrototypesCount() - 1) // Flecha abajo
                seleccionado++;
            else if (tecla == 13)
            { // Enter
                char *prototipo = parser.getPrototypeAt(seleccionado);
                if (!prototipo)
                {
                    std::cout << "Error: No se pudo obtener el prototipo seleccionado" << std::endl;
                    system("pause");
                    continue;
                }

                std::cout << "\nPrototipo seleccionado: " << prototipo << std::endl;
                std::cout << "Analizando complejidad..." << std::endl;
                system("pause");
                
                analizarComplejidad(prototipo, ruta);

                std::cout << "Análisis completado." << std::endl;
                system("pause");
                break;
            }
        } while (true);

        std::cout << "\n¿Desea analizar otro archivo? (s/n): ";
        char respuesta;
        std::cin >> respuesta;
        limpiarBuffer();

        if (respuesta != 's' && respuesta != 'S')
        {
            std::cout << "Programa terminado." << std::endl;
            break;
        }

    } while (true);

    return 0;
}
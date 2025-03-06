#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

class Numero
{
private:
    int valor;
    Numero *siguiente;

public:
    Numero(int val) : valor(val), siguiente(nullptr) {}

    int getValor() const { return valor; }
    void setSiguiente(Numero *num) { siguiente = num; }
    Numero *getSiguiente() const { return siguiente; }
};

class Columna
{
private:
    Numero *cabeza;
    int altura;

public:
    Columna() : cabeza(nullptr), altura(0) {}

    void insertarNumero(int valor)
    {
        Numero *nuevoNumero = new Numero(valor);
        if (!cabeza)
        {
            cabeza = nuevoNumero;
        }
        else
        {
            Numero *actual = cabeza;
            while (actual->getSiguiente())
            {
                actual = actual->getSiguiente();
            }
            actual->setSiguiente(nuevoNumero);
        }
        altura++;
    }

    bool eliminarNumerosIguales()
    {
        bool seEliminaron = false;
        Numero *actual = cabeza;
        Numero *anterior = nullptr;

        while (actual && actual->getSiguiente())
        {
            if (actual->getValor() == actual->getSiguiente()->getValor())
            {
                Numero *aEliminar1 = actual;
                Numero *aEliminar2 = actual->getSiguiente();

                if (anterior)
                {
                    anterior->setSiguiente(aEliminar2->getSiguiente());
                }
                else
                {
                    cabeza = aEliminar2->getSiguiente();
                }

                delete aEliminar1;
                delete aEliminar2;
                altura -= 2;
                seEliminaron = true;

                if (anterior)
                {
                    actual = anterior->getSiguiente();
                }
                else
                {
                    actual = cabeza;
                }
            }
            else
            {
                anterior = actual;
                actual = actual->getSiguiente();
            }
        }
        return seEliminaron;
    }

    void alinearIzquierda()
{
    // Crear una lista temporal para guardar los números
    Numero* listaTemp = nullptr;
    Numero* ultimoTemp = nullptr;

    // Extraer todos los números
    while (cabeza)
    {
        Numero* actual = cabeza;
        cabeza = cabeza->getSiguiente();
        actual->setSiguiente(nullptr);

        if (!listaTemp)
        {
            listaTemp = actual;
            ultimoTemp = actual;
        }
        else
        {
            ultimoTemp->setSiguiente(actual);
            ultimoTemp = actual;
        }
    }

    // Restablecer la cabeza con la lista reordenada
    cabeza = listaTemp;
    altura = 0;

    // Contar nueva altura
    Numero* actual = cabeza;
    while (actual)
    {
        altura++;
        actual = actual->getSiguiente();
    }
}

    int getAltura() const { return altura; }
    Numero *getCabeza() const { return cabeza; }
};

class Tablero
{
private:
    static const int ANCHO = 10;
    static const int ALTO = 20;
    Columna *columnas[ANCHO];
    int columnaActual;
    int numeroActual;
    int posicionCaida;
    bool requiereAlineacion;

public:
    Tablero() : columnaActual(ANCHO / 2), numeroActual(0),
                posicionCaida(ALTO - 1), requiereAlineacion(false)
    {
        for (int i = 0; i < ANCHO; ++i)
        {
            *(columnas + i) = new Columna();
        }
        srand(time(nullptr));
    }

    void generarNuevoNumero()
    {
        numeroActual = rand() % 9 + 1;
        columnaActual = ANCHO / 2;
        posicionCaida = ALTO - 1;
        requiereAlineacion = true;
    }

    void moverIzquierda()
    {
        if (columnaActual > 0)
            columnaActual--;
    }

    void moverDerecha()
    {
        if (columnaActual < ANCHO - 1)
            columnaActual++;
    }

    void soltarNumero()
    {
        (*(columnas + columnaActual))->insertarNumero(numeroActual);
        bool seEliminaron;
        do
        {
            seEliminaron = false;
            for (int i = 0; i < ANCHO; ++i)
            {
                if ((*(columnas + i))->eliminarNumerosIguales())
                {
                    seEliminaron = true;
                }
            }
            compactarTablero();
        } while (seEliminaron);
        generarNuevoNumero();
    }

    void compactarTablero()
    {
        // Alinear cada columna a la izquierda
        for (int i = 0; i < ANCHO; ++i)
        {
            (*(columnas + i))->alinearIzquierda();
        }

        // Mover columnas completamente hacia la izquierda si están vacías
        Columna *columnasActualizadas[ANCHO] = {nullptr};
        int indiceNuevo = 0;

        // Recoger solo las columnas no vacías
        for (int i = 0; i < ANCHO; ++i)
        {
            if ((*(columnas + i))->getAltura() > 0)
            {
                *(columnasActualizadas + indiceNuevo) = *(columnas + i);
                indiceNuevo++;
            }
            else
            {
                // Liberar memoria de columnas vacías
                delete *(columnas + i);
            }
        }

        // Rellenar el resto con columnas vacías
        while (indiceNuevo < ANCHO)
        {
            *(columnasActualizadas + indiceNuevo) = new Columna();
            indiceNuevo++;
        }

        // Copiar de vuelta al arreglo original
        for (int i = 0; i < ANCHO; ++i)
        {
            *(columnas + i) = *(columnasActualizadas + i);
        }
    }

    void dibujarTablero()
    {
        system("cls");
        for (int fila = ALTO - 1; fila >= 0; --fila)
        {
            std::cout << "|";
            for (int col = 0; col < ANCHO; ++col)
            {
                Numero *actual = (*(columnas + col))->getCabeza();
                int altura = 0;
                while (actual && altura < fila)
                {
                    actual = actual->getSiguiente();
                    altura++;
                }

                if (actual && altura == fila)
                {
                    std::cout << " " << actual->getValor() << " |";
                }
                else if (col == columnaActual && fila == posicionCaida)
                {
                    std::cout << " " << numeroActual << " |";
                }
                else
                {
                    std::cout << "   |";
                }
            }
            std::cout << std::endl;

            // Dibujar línea separadora
            std::cout << "|";
            for (int col = 0; col < ANCHO; ++col)
            {
                std::cout << "___" << "|";
            }
            std::cout << std::endl;
        }
    }

    void animarCaida()
    {
        if (posicionCaida > 0)
        {
            posicionCaida--;
        }
        else
        {
            soltarNumero();
        }
    }

    bool juegoTerminado()
    {
        for (int i = 0; i < ANCHO; ++i)
        {
            if ((*(columnas + i))->getAltura() >= ALTO)
                return true;
        }
        return false;
    }
};

int main()
{
    Tablero juego;
    juego.generarNuevoNumero();

    while (!juego.juegoTerminado())
    {
        juego.dibujarTablero();
        juego.animarCaida();

        if (_kbhit())
        {
            int tecla = _getch();
            switch (tecla)
            {
            case 75: // Flecha izquierda
                juego.moverIzquierda();
                break;
            case 77: // Flecha derecha
                juego.moverDerecha();
                break;
            case 32: // Espacio
                juego.soltarNumero();
                break;
            }
        }

        Sleep(200);
    }

    std::cout << "¡Juego Terminado!" << std::endl;
    return 0;
}
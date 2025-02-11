#include "grafo.h"
#include <iostream>
#include <graphics.h>

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    initwindow(800, 600, "Grafo");
    
    Grafo* grafo = nullptr;
    
    while(true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Crear grafo dirigido\n";
        std::cout << "2. Crear grafo no dirigido\n";
        std::cout << "3. Ver matriz de adyacencia\n";  
        std::cout << "4. Ver lista de adyacencia\n";  
        std::cout << "5. Ver grafo\n";
        std::cout << "6. Generar nuevo grafo aleatorio\n";
        std::cout << "7. Salir\n";
        std::cout << "Seleccione una opcion: ";
        
        int opcion;
        std::cin >> opcion;
        
        switch(opcion) {
            case 1:
                if(grafo) delete grafo;
                grafo = new Grafo(6, true);
                grafo->generarGrafoAleatorio();
                grafo->dibujarGrafo();
                break;
                
            case 2:
                if(grafo) delete grafo;
                grafo = new Grafo(6, false);
                grafo->generarGrafoAleatorio();
                grafo->dibujarGrafo();
                break;

                case 3:
                if(grafo) {
                    grafo->dibujarMatrizGrafica();
                    system("pause");
                }
                else std::cout << "Primero cree un grafo\n";
                break;
                
            case 4:
                if(grafo) {
                    grafo->dibujarListaGrafica(); 
                    system("pause"); 
                }
                else std::cout << "Primero cree un grafo\n";
                break;
                
            case 5:
                if(grafo) {
                    grafo->dibujarGrafo();
                    system("pause");
                }
                else std::cout << "Primero cree un grafo\n";
                break;
                
            case 6:
                if(grafo) {
                    grafo->generarGrafoAleatorio();
                    grafo->dibujarGrafo();
                }
                else std::cout << "Primero cree un grafo\n";
                break;
                
            case 7:
                if(grafo) delete grafo;
                closegraph();
                return 0;
                
            default:
                std::cout << "Opción inválida\n";
        }
    }
    
    return 0;
}
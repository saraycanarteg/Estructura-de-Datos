#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include "sistematour.cpp"



int main() {
    SistemaTours sistema;
    
    // Registrar puntos de interés con coordenadas (x,y) para el mapa
    sistema.registrarPuntoInteres("Plaza Mayor", "Plaza principal e histórica de la ciudad", 30, 400, 200);
    sistema.registrarPuntoInteres("Catedral", "Impresionante catedral gótica del siglo XVI", 45, 550, 180);
    sistema.registrarPuntoInteres("Museo de Arte", "Colección de arte antiguo y moderno", 60, 620, 300);
    sistema.registrarPuntoInteres("Parque Central", "Hermoso parque con jardines y fuentes", 25, 500, 400);
    sistema.registrarPuntoInteres("Mercado Local", "Mercado tradicional con productos locales", 40, 300, 350);
    
    // Crear una ruta
    sistema.crearRuta("Tour Centro Histórico");
    RutaTour* rutaCentro = sistema.buscarRuta("Tour Centro Histórico");
    
    // Agregar puntos a la ruta con distancias entre ellos
    rutaCentro->agregarPunto(sistema.buscarPuntoInteres("Plaza Mayor"), 500);
    rutaCentro->agregarPunto(sistema.buscarPuntoInteres("Catedral"), 300);
    rutaCentro->agregarPunto(sistema.buscarPuntoInteres("Museo de Arte"), 700);
    rutaCentro->agregarPunto(sistema.buscarPuntoInteres("Parque Central"), 400);
    rutaCentro->agregarPunto(sistema.buscarPuntoInteres("Mercado Local"), 0); // Último punto
    
    // Agregar un carrito
    sistema.agregarCarrito("Tour-01", 12, 15);
    
    std::cout << "==== Iniciando Simulación Gráfica de City Tour ====" << std::endl;
    sistema.iniciarSimulacionGrafica();
    
    return 0;
}
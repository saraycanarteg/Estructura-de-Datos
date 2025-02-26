//#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include "nodo.cpp"

class Carrito {
    private:
        std::string id;
        int capacidad;
        int velocidad; // km/h
        bool enMovimiento;
        sf::Vector2f posicion;
        sf::RectangleShape forma;
        float escalaVelocidad; // Factor para convertir velocidad real a píxeles por frame
    
    public:
        Carrito(std::string _id, int _capacidad, int _velocidad) {
            id = _id;
            capacidad = _capacidad;
            velocidad = _velocidad;
            enMovimiento = false;
            escalaVelocidad = 0.5; // Ajustar según necesidad para la simulación
            
            // Configurar forma visual
            forma.setSize(sf::Vector2f(30, 20));
            forma.setFillColor(sf::Color::Green);
            forma.setOutlineColor(sf::Color::White);
            forma.setOutlineThickness(2);
        }
    
        void setPosicion(sf::Vector2f pos) {
            posicion = pos;
            forma.setPosition(pos.x - 15, pos.y - 10);
        }
        
        sf::Vector2f getPosicion() {
            return posicion;
        }
        
        void dibujar(sf::RenderWindow& ventana) {
            ventana.draw(forma);
        }
    
        void iniciarRecorrido() {
            enMovimiento = true;
            std::cout << "Carrito " << id << " ha iniciado el recorrido." << std::endl;
        }
    
        void detenerRecorrido() {
            enMovimiento = false;
            std::cout << "Carrito " << id << " ha terminado el recorrido." << std::endl;
        }
    
        bool moverHacia(sf::Vector2f destino, sf::RenderWindow& ventana) {
            sf::Vector2f direccion = destino - posicion;
            float distancia = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);
            
            if (distancia < 2.0f) {
                // Hemos llegado al destino
                return true;
            }
            
            // Normalizar y escalar por velocidad
            direccion = direccion / (distancia * velocidad * escalaVelocidad);
            posicion += direccion;
            forma.setPosition(posicion.x - 15, posicion.y - 10);
            
            return false;
        }
    
        void visitarPunto(PuntoInteres* punto, sf::RenderWindow& ventana) {
            std::cout << "\nLlegando a: " << punto->getNombre() << std::endl;
            punto->mostrarInfo();
            
            // Simular tiempo de visita (cambiar color del carrito)
            forma.setFillColor(sf::Color::Yellow);
            ventana.draw(forma);
            ventana.display();
            
           std::this_thread::sleep_for(std::chrono::seconds(1));
            
            forma.setFillColor(sf::Color::Green);
        }
    
        int calcularTiempoViaje(int distanciaMetros) {
            // Convertir velocidad a metros por minuto
            float velocidadMpm = (velocidad * 1000) / 60.0;
            return static_cast<int>(distanciaMetros / velocidadMpm);
        }
    };
    
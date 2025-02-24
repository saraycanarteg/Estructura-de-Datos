#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include "nodo.cpp"

class RutaTour {
    private:
        Nodo* inicio;
        Nodo* fin;
        std::string nombre;
        int numPuntos;
        std::vector<sf::Vertex> lineasRuta;
    
    public:
        RutaTour(std::string _nombre) {
            inicio = nullptr;
            fin = nullptr;
            nombre = _nombre;
            numPuntos = 0;
        }
    
        std::string getNombre() { return nombre; }
    
        ~RutaTour() {
            Nodo* actual = inicio;
            while (actual != nullptr) {
                Nodo* temp = actual;
                actual = actual->getSiguiente();
                delete temp;
            }
        }
    
        void agregarPunto(PuntoInteres* punto, int distancia) {
            Nodo* nuevoNodo = new Nodo(punto, distancia);
            
            if (inicio == nullptr) {
                inicio = nuevoNodo;
                fin = nuevoNodo;
            } else {
                // Añadir línea para la representación gráfica
                sf::Vector2f pos1 = fin->getPunto()->getPosicion();
                sf::Vector2f pos2 = punto->getPosicion();
                
                lineasRuta.push_back(sf::Vertex(pos1, sf::Color(150, 150, 150)));
                lineasRuta.push_back(sf::Vertex(pos2, sf::Color(150, 150, 150)));
                
                fin->setSiguiente(nuevoNodo);
                fin = nuevoNodo;
            }
            
            numPuntos++;
        }
    
        void dibujar(sf::RenderWindow& ventana) {
            // Dibujar las líneas de la ruta
            if (lineasRuta.size() >= 2) {
                ventana.draw(&lineasRuta[0], lineasRuta.size(), sf::Lines);
            }
            
            // Dibujar los puntos de interés
            Nodo* actual = inicio;
            while (actual != nullptr) {
                actual->getPunto()->dibujar(ventana);
                actual = actual->getSiguiente();
            }
        }
    
        void mostrarRuta() {
            std::cout << "\n===== Ruta: " << nombre << " =====" << std::endl;
            std::cout << "Número de puntos de interés: " << numPuntos << std::endl;
            
            Nodo* actual = inicio;
            int contador = 1;
            
            while (actual != nullptr) {
                std::cout << "\n" << contador << ". " << actual->getPunto()->getNombre() << std::endl;
                if (actual->getSiguiente() != nullptr) {
                    std::cout << "   Distancia al siguiente punto: " << actual->getDistancia() << " metros" << std::endl;
                }
                contador++;
                actual = actual->getSiguiente();
            }
        }
    
        void realizarTourGrafico(Carrito* carrito, sf::RenderWindow& ventana, sf::Font& fuente) {
            if (inicio == nullptr) {
                std::cout << "No hay puntos en la ruta para realizar el tour." << std::endl;
                return;
            }
    
            sf::Text infoText;
            infoText.setFont(fuente);
            infoText.setCharacterSize(16);
            infoText.setFillColor(sf::Color::White);
            infoText.setPosition(10, 10);
    
            std::cout << "\n===== Iniciando Tour: " << nombre << " =====" << std::endl;
            carrito->iniciarRecorrido();
            
            // Posicionar el carrito en el primer punto
            carrito->setPosicion(inicio->getPunto()->getPosicion());
            
            Nodo* actual = inicio;
            Nodo* siguiente = nullptr;
            
            inicio->getPunto()->resaltar();
            
            while (actual != nullptr) {
                // Visitar el punto actual
                carrito->visitarPunto(actual->getPunto(), ventana);
                
                // Si hay un siguiente punto, moverse hacia él
                siguiente = actual->getSiguiente();
                if (siguiente != nullptr) {
                    int tiempoViaje = carrito->calcularTiempoViaje(actual->getDistancia());
                    std::cout << "\nViajando " << actual->getDistancia() << " metros hacia " 
                              << siguiente->getPunto()->getNombre() << std::endl;
                    std::cout << "Tiempo estimado de viaje: " << tiempoViaje << " minutos." << std::endl;
                    
                    infoText.setString("Viajando hacia: " + siguiente->getPunto()->getNombre() + 
                                     "\nDistancia: " + std::to_string(actual->getDistancia()) + "m" +
                                     "\nTiempo: " + std::to_string(tiempoViaje) + " min");
                    
                    // Desresaltar punto actual
                    actual->getPunto()->desresaltar();
                    // Resaltar siguiente punto
                    siguiente->getPunto()->resaltar();
                    
                    bool llegado = false;
                    while (!llegado) {
                        sf::Event evento;
                        while (ventana.pollEvent(evento)) {
                            if (evento.type == sf::Event::Closed)
                                ventana.close();
                        }
                        
                        // Limpiar ventana
                        ventana.clear(sf::Color(50, 50, 50));
                        
                        // Dibujar ruta
                        this->dibujar(ventana);
                        
                        // Actualizar posición del carrito
                        llegado = carrito->moverHacia(siguiente->getPunto()->getPosicion(), ventana);
                        
                        // Dibujar carrito
                        carrito->dibujar(ventana);
                        
                        // Dibujar texto informativo
                        ventana.draw(infoText);
                        
                        // Mostrar cambios
                        ventana.display();
                    }
                }
                
                actual = siguiente;
            }
            
            infoText.setString("Tour finalizado");
            ventana.clear(sf::Color(50, 50, 50));
            this->dibujar(ventana);
            carrito->dibujar(ventana);
            ventana.draw(infoText);
            ventana.display();
            
            std::this_thread::sleep_for(std::chrono::seconds(2));
            
            carrito->detenerRecorrido();
            std::cout << "===== Tour Finalizado =====" << std::endl;
        }
    
        Nodo* getInicio() { return inicio; }
    };
    
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include "nodo.cpp"
#include "ruta.cpp"
#include "carro.cpp"

class SistemaTours {
    private:
        std::vector<PuntoInteres*> puntosInteres;
        std::vector<RutaTour*> rutas;
        std::vector<Carrito*> carritos;
        sf::Font fuente;
    
    public:
        SistemaTours() {
            // Cargar fuente
            if (!fuente.loadFromFile("arial.ttf")) {
                std::cout << "Error al cargar la fuente. Usando fuente por defecto del sistema." << std::endl;
            }
        }
    
        ~SistemaTours() {
            // Liberar memoria
            for (auto punto : puntosInteres) delete punto;
            for (auto ruta : rutas) delete ruta;
            for (auto carrito : carritos) delete carrito;
        }
    
        sf::Font& getFuente() { return fuente; }
    
        void registrarPuntoInteres(std::string nombre, std::string descripcion, int tiempoVisita, float x, float y) {
            PuntoInteres* nuevoPunto = new PuntoInteres(nombre, descripcion, tiempoVisita, x, y, fuente);
            puntosInteres.push_back(nuevoPunto);
        }
    
        PuntoInteres* buscarPuntoInteres(std::string nombre) {
            for (auto punto : puntosInteres) {
                if (punto->getNombre() == nombre) {
                    return punto;
                }
            }
            return nullptr;
        }
    
        void crearRuta(std::string nombreRuta) {
            RutaTour* nuevaRuta = new RutaTour(nombreRuta);
            rutas.push_back(nuevaRuta);
        }
    
        RutaTour* buscarRuta(std::string nombre) {
            for (auto ruta : rutas) {
                if (ruta->getNombre() == nombre) {
                    return ruta;
                }
            }
            return nullptr;
        }
    
        void agregarCarrito(std::string id, int capacidad, int velocidad) {
            Carrito* nuevoCarrito = new Carrito(id, capacidad, velocidad);
            carritos.push_back(nuevoCarrito);
        }
    
        Carrito* buscarCarrito(std::string id) {
            for (auto carrito : carritos) {
                if (carrito->id == id) {
                    return carrito;
                }
            }
            return nullptr;
        }
    
        void iniciarSimulacionGrafica() {
            // Crear ventana
            sf::RenderWindow ventana(sf::VideoMode(800, 600), "City Tour - Simulación Gráfica");
            
            // Configurar la ventana
            ventana.setFramerateLimit(60);
            
            // Textos de interfaz
            sf::Text tituloText;
            tituloText.setFont(fuente);
            tituloText.setString("City Tour - Simulación Gráfica");
            tituloText.setCharacterSize(24);
            tituloText.setFillColor(sf::Color::White);
            tituloText.setPosition(10, 10);
            
            sf::Text instruccionesText;
            instruccionesText.setFont(fuente);
            instruccionesText.setString("Presiona espacio para iniciar el tour");
            instruccionesText.setCharacterSize(18);
            instruccionesText.setFillColor(sf::Color::White);
            instruccionesText.setPosition(10, 40);
            
            // Si no hay rutas, mostrar mensaje
            if (rutas.empty()) {
                std::cout << "No hay rutas definidas para la simulación." << std::endl;
                return;
            }
            
            // Usar la primera ruta disponible
            RutaTour* rutaActual = rutas[0];
            
            // Si no hay carritos, mostrar mensaje
            if (carritos.empty()) {
                std::cout << "No hay carritos definidos para la simulación." << std::endl;
                return;
            }
            
            // Usar el primer carrito disponible
            Carrito* carritoActual = carritos[0];
            
            // Inicio de simulación
            bool simulacionIniciada = false;
            
            // Loop principal
            while (ventana.isOpen()) {
                sf::Event evento;
                while (ventana.pollEvent(evento)) {
                    if (evento.type == sf::Event::Closed)
                        ventana.close();
                    
                    if (evento.type == sf::Event::KeyPressed) {
                        if (evento.key.code == sf::Keyboard::Space && !simulacionIniciada) {
                            simulacionIniciada = true;
                            std::thread tourThread([&]() {
                                rutaActual->realizarTourGrafico(carritoActual, ventana, fuente);
                            });
                            tourThread.detach();
                        }
                    }
                }
                
                // Limpiar ventana
                ventana.clear(sf::Color(50, 50, 50));
                
                if (!simulacionIniciada) {
                    // Dibujar interfaz inicial
                    ventana.draw(tituloText);
                    ventana.draw(instruccionesText);
                    
                    // Dibujar ruta
                    rutaActual->dibujar(ventana);
                }
                
                // Mostrar cambios
                ventana.display();
            }
        }
    };

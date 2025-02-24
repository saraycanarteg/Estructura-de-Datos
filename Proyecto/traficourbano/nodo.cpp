#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>

// Clase para representar un punto de interés en la ciudad
class PuntoInteres {
private:
    std::string nombre;
    std::string descripcion;
    int tiempoVisita; // tiempo en minutos
    sf::Vector2f posicion; // Posición en el mapa (x,y)
    sf::CircleShape forma;
    sf::Text texto;

public:
    PuntoInteres(std::string _nombre, std::string _descripcion, int _tiempoVisita, 
                 float x, float y, sf::Font& font) {
        nombre = _nombre;
        descripcion = _descripcion;
        tiempoVisita = _tiempoVisita;
        posicion = sf::Vector2f(x, y);
        
        // Configurar forma visual
        forma.setRadius(15);
        forma.setFillColor(sf::Color::Blue);
        forma.setPosition(x - 15, y - 15);
        forma.setOutlineColor(sf::Color::White);
        forma.setOutlineThickness(2);
        
        // Configurar texto
        texto.setFont(font);
        texto.setString(nombre);
        texto.setCharacterSize(12);
        texto.setFillColor(sf::Color::White);
        texto.setPosition(x - 15, y + 20);
    }

    std::string getNombre() { return nombre; }
    std::string getDescripcion() { return descripcion; }
    int getTiempoVisita() { return tiempoVisita; }
    sf::Vector2f getPosicion() { return posicion; }

    void mostrarInfo() {
        std::cout << "Punto de interés: " << nombre << std::endl;
        std::cout << "Descripción: " << descripcion << std::endl;
        std::cout << "Tiempo de visita: " << tiempoVisita << " minutos" << std::endl;
    }
    
    void dibujar(sf::RenderWindow& ventana) {
        ventana.draw(forma);
        ventana.draw(texto);
    }
    
    void resaltar() {
        forma.setFillColor(sf::Color::Red);
    }
    
    void desresaltar() {
        forma.setFillColor(sf::Color::Blue);
    }
};
class Nodo {
    private:
        PuntoInteres* punto;
        Nodo* siguiente;
        int distancia; // distancia al siguiente punto en metros
    
    public:
        Nodo(PuntoInteres* _punto, int _distancia = 0) {
            punto = _punto;
            siguiente = nullptr;
            distancia = _distancia;
        }
    
        PuntoInteres* getPunto() { return punto; }
        Nodo* getSiguiente() { return siguiente; }
        int getDistancia() { return distancia; }
    
        void setSiguiente(Nodo* _siguiente) { siguiente = _siguiente; }
        void setDistancia(int _distancia) { distancia = _distancia; }
    };
    
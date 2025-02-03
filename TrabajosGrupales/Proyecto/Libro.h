#ifndef LIBRO_H
#define LIBRO_H

#include <string>
#include "Autor.h"
#include "Fecha.h"

using namespace std;

class Libro {
private:
    string titulo;
    Autor autor;
    Fecha fecha_publicacion;
    string isbn;

public:
    // Constructores
    Libro(); 
    Libro(string titulo, Autor autor, Fecha fecha_publicacion, string isbn);

    // Getters
    string getTitulo() const;
    Autor getAutor() const;
    Fecha getFechaPublicacion() const;
    string getIsbn() const;

    // Setters
    void setTitulo(string titulo);
    void setAutor(Autor autor);
    void setFechaPublicacion(Fecha fecha_publicacion);
    void setIsbn(string isbn);
};

#endif
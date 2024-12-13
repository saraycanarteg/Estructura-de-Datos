#include <iostream>
#include "ListaLibros.h"
#include "Validation.cpp"
#include <fstream>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip>

// Constructor
ListaLibros::ListaLibros() : cabeza(nullptr), tamano(0) {}

NodoLibro::NodoLibro(const Libro &lib)
    : libro(lib), siguiente(nullptr), anterior(nullptr) {}

// Destructor
ListaLibros::~ListaLibros()
{
    // Eliminar todos los nodos de la lista
    while (cabeza != nullptr)
    {
        NodoLibro *temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

void ListaLibros::guardarLibrosEnArchivo() const
{
    std::ofstream archivo("libros.txt");
    if (!archivo.is_open())
    {
        std::cerr << "Error al abrir el archivo para guardar los libros." << std::endl;
        return;
    }

    NodoLibro *actual = cabeza;
    if (actual == nullptr)
    {
        archivo << "No hay libros en la biblioteca." << std::endl;
        archivo.close();
        return;
    }

    do
    {
        archivo << "Titulo: " << actual->libro.getTitulo() << "\n";
        archivo << "Autor: " << actual->libro.getAutor().getNombreCompleto() << "\n";
        archivo << "Fecha de publicacion: " << actual->libro.getFechaPublicacion().getFechaComoString() << "\n";
        archivo << "ISBN: " << actual->libro.getIsbn() << "\n";
        archivo << "---\n";
        actual = actual->siguiente;
    } while (actual != cabeza);

    archivo.close();
    std::cout << "\nArchivo actualizado: libros.txt" << std::endl;
}

// Registro de libros
void ListaLibros::registrarLibro(const Libro &libro)
{
    // Verificar si el libro ya existe
    std::vector<Libro> librosExistentes = cargarLibrosDesdeCSV();

    for (const auto &libroExistente : librosExistentes)
    {
        if (libroExistente.getIsbn() == libro.getIsbn())
        {
            std::cout << "El libro ya existe en la biblioteca." << std::endl;
            return;
        }
    }

    guardarAutorCSV(libro.getAutor());

    NodoLibro *nuevoNodo = new NodoLibro(libro);

    if (cabeza == nullptr)
    {
        // Primer libro
        cabeza = nuevoNodo;
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
    }
    else
    {
        // Agregar al final de la lista circular
        nuevoNodo->siguiente = cabeza;
        nuevoNodo->anterior = cabeza->anterior;
        cabeza->anterior->siguiente = nuevoNodo;
        cabeza->anterior = nuevoNodo;
    }

    tamano++;
    generarArchivoCSV();
    guardarLibrosDeAutor(libro.getAutor());
    generarBackup();
}

bool ListaLibros::modificarLibroPorTitulo(const string &titulo, const Libro &nuevoLibro)
{
    NodoLibro *actual = cabeza;
    if (actual == nullptr)
        return false;

    do
    {
        if (actual->libro.getTitulo() == titulo)
        {
            actual->libro = nuevoLibro;
            guardarLibrosEnArchivo(); // Actualizar archivo después de modificar
            return true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return false;
}

// Eliminación de libros
bool ListaLibros::eliminarLibroPorTitulo(const string &titulo)
{
    if (cabeza == nullptr)
        return false;

    NodoLibro *actual = cabeza;
    do
    {
        if (actual->libro.getTitulo() == titulo)
        {
            if (actual == cabeza)
            {
                cabeza = (cabeza->siguiente == cabeza) ? nullptr : cabeza->siguiente;
            }
            actual->anterior->siguiente = actual->siguiente;
            actual->siguiente->anterior = actual->anterior;
            delete actual;
            tamano--;

            guardarLibrosEnArchivo(); // <-- Llama a este método después de eliminar
            return true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return false;
}

bool ListaLibros::eliminarLibroPorIsbn(const string &isbn)
{
    if (cabeza == nullptr)
        return false;

    NodoLibro *actual = cabeza;
    do
    {
        if (actual->libro.getIsbn() == isbn)
        {
            if (actual == cabeza)
            {
                cabeza = (cabeza->siguiente == cabeza) ? nullptr : cabeza->siguiente;
            }
            actual->anterior->siguiente = actual->siguiente;
            actual->siguiente->anterior = actual->anterior;
            delete actual;
            tamano--;
            guardarLibrosEnArchivo(); // Actualizar archivo después de eliminar
            return true;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return false;
}

// Función para cargar libros desde CSV
std::vector<Libro> ListaLibros::cargarLibrosDesdeCSV() const
{
    std::vector<Libro> librosLeidos;
    std::ifstream archivoCSV("libros.csv");

    if (!archivoCSV.is_open())
    {
        std::cerr << "Error al abrir el archivo CSV de libros." << std::endl;
        return librosLeidos;
    }

    // Saltar la línea de encabezados
    std::string encabezados;
    std::getline(archivoCSV, encabezados);

    std::string linea;
    while (std::getline(archivoCSV, linea))
    {
        std::stringstream ss(linea);
        std::string titulo, nombreCompleto, fechaStr, isbn, editorial;

        // Leer cada campo, manejando comas dentro de los campos
        std::getline(ss, titulo, ',');
        std::getline(ss, nombreCompleto, ',');
        std::getline(ss, fechaStr, ',');
        std::getline(ss, isbn, ',');
        std::getline(ss, editorial);

        // Restaurar comas reemplazadas
        std::replace(titulo.begin(), titulo.end(), ';', ',');
        std::replace(nombreCompleto.begin(), nombreCompleto.end(), ';', ',');
        std::replace(fechaStr.begin(), fechaStr.end(), ';', ',');
        std::replace(editorial.begin(), editorial.end(), ';', ',');

        // Parsear nombre completo del autor
        std::string nombre, apellido;
        std::stringstream nombreSS(nombreCompleto);
        std::getline(nombreSS, nombre, ' ');
        std::getline(nombreSS, apellido);

        // Parsear fecha
        int dia, mes, anio;
        std::stringstream fechaSS(fechaStr);
        char delimiter;
        fechaSS >> dia >> delimiter >> mes >> delimiter >> anio;

        // Generar un ID de autor simple (puedes mejorarlo)
        std::string idAutor = nombre.substr(0, 1) + apellido.substr(0, 1);

        // Crear objetos con los datos
        Autor autor(nombre, apellido, idAutor, ""); // Nacionalidad en blanco por ahora
        Fecha fecha(dia, mes, anio);

        // Crear el libro
        Libro libro(titulo, autor, fecha, isbn, editorial);
        librosLeidos.push_back(libro);
    }

    archivoCSV.close();
    return librosLeidos;
}

// Impresión de libros
void ListaLibros::imprimirLibros() const
{
    std::vector<Libro> libros = cargarLibrosDesdeCSV();

    if (libros.empty())
    {
        cout << "No hay libros en la biblioteca." << endl;
        return;
    }

    cout << "Libros en la biblioteca:" << endl;
    for (const auto &libro : libros)
    {
        cout << "Titulo: " << libro.getTitulo() << endl;
        cout << "Autor: " << libro.getAutor().getNombre() << " " << libro.getAutor().getApellido() << endl;

        Fecha fecha = libro.getFechaPublicacion();
        cout << "Fecha de publicacion: "
             << fecha.getDia() << "/"
             << fecha.getMes() << "/"
             << fecha.getAnio() << endl;

        cout << "ISBN: " << libro.getIsbn() << endl;
        cout << "Editorial: " << libro.getEditorial() << endl;
        cout << "---" << endl;
    }
}

void ListaLibros::modificarLibroEnCSV(const std::string& identificador, const std::string& campoAModificar) {
    
    Validation<std::string> validador;
    std::vector<Libro> libros = cargarLibrosDesdeCSV();
    bool libroEncontrado = false;

    // Modificar el libro que coincide con el identificador (ISBN o Titulo)
    for (auto& libro : libros) {
        if (libro.getIsbn() == identificador || libro.getTitulo() == identificador) {
            libroEncontrado = true;
            

            if (campoAModificar == "Titulo") {
                cout<<"\nTitulo actual: "<<libro.getTitulo()<<endl;
                cout<<"\nIngrese titulo nuevo: ";
                std::string tituloValidado = validador.enter_a_char_or_string_with_may_and_nums(20);
                cout<<endl;
                libro.setTitulo(tituloValidado);
            } else if (campoAModificar == "Autor") {
                cout<<"\nNombre actual Autor: "<<libro.getAutor().getNombre()<<" "<<libro.getAutor().getApellido()<<endl;
                cout<<"\nIngrese los nombres del autor: ";
                string nombres = validador.enter_a_char_or_string_with_may(20);
                cout<<"\nIngrese los apellidos del autor: ";
                string apellidos = validador.enter_a_char_or_string_with_may(20);
                libro.setAutor(Autor(nombres, apellidos, libro.getAutor().getId(), libro.getAutor().getNacionalidad()));
                cout<<endl;

            } else if (campoAModificar == "Fecha de Publicacion") {
                cout<<"Fecha de publicacion actual: "<<libro.getFechaPublicacion().getFechaComoString()<<endl;
                cout<<"\nIngrese fecha de publicacion (DD MM AAAA): ";
                string fechaIngresada = validador.enter_date();
                cout<<endl;
                stringstream ss(fechaIngresada);
                int dia, mes, anio;
                char delimiter;
                ss >> dia >> delimiter >> mes >> delimiter >> anio;
                libro.setFechaPublicacion(Fecha(dia, mes, anio));
            } else if (campoAModificar == "ISBN") {
                cout<<"\nISBN actual: "<<libro.getIsbn()<<endl;
                cout<<"\nIngrese un ISBN: ";
                string isbn = validador.enter_a_char_or_string_only_nums(20);
                if (!validador.validate_isbn(isbn)) {
                    std::cerr << "\nEl ISBN proporcionado no es válido." << std::endl;
                    return;
                }
                cout<<endl;
                libro.setIsbn(isbn);
            } else if (campoAModificar == "Editorial") {
                cout<<"\nEditorial actual: "<< libro.getEditorial()<<endl;
                cout<<"\nIngrese una editorial: ";
                std::string editorialValidada = validador.enter_a_char_or_string_with_may(20);
                libro.setEditorial(editorialValidada);
            }
        }
    }

    if (!libroEncontrado) {
        std::cerr << "\nNo se encontró un libro con el identificador proporcionado: " << identificador << std::endl;
        system("pause");
        return;
    }

    // Guardar nuevamente todos los libros en el archivo CSV
    std::ofstream archivoCSV("libros.csv");
    if (!archivoCSV.is_open()) {
        std::cerr << "\nError al abrir el archivo CSV para escritura." << std::endl;
        return;
    }

    // Escribir encabezados
    archivoCSV << "\nTitulo,Autor,Fecha de Publicacion,ISBN,Editorial" << std::endl;

    // Escribir datos de los libros
    for (const auto& libro : libros) {
        archivoCSV << libro.getTitulo() << ","
                   << libro.getAutor().getNombre() << " " << libro.getAutor().getApellido() << ","
                   << libro.getFechaPublicacion().getFechaComoString() << ","
                   << libro.getIsbn() << ","
                   << libro.getEditorial() << std::endl;
    }

    archivoCSV.close();
    std::cout << "Libro actualizado correctamente." << std::endl;
}


Libro *ListaLibros::buscarLibroPorTitulo(const string &titulo)
{
    // Cargar libros desde CSV
    std::vector<Libro> libros = cargarLibrosDesdeCSV();

    // Buscar el libro por título
    for (auto &libro : libros)
    {
        if (libro.getTitulo() == titulo)
        {
            // Encontrado: devolver una copia dinámica
            return new Libro(libro);
        }
    }

    return nullptr;
}

// Métodos adicionales
int ListaLibros::obtenerTamano() const
{
    return tamano;
}

bool ListaLibros::estaVacia() const
{
    return cabeza == nullptr;
}

// Modificar el método generarBackup() en la clase ListaLibros
void ListaLibros::generarBackup() const
{
    if (cabeza == nullptr)
    {
        std::cout << "No hay libros para respaldar." << std::endl;
        return;
    }

    // Abrir el archivo de backup en modo append
    std::ofstream archivoBackup("libros_backup.txt", std::ios_base::app);
    if (!archivoBackup.is_open())
    {
        std::cerr << "Error al crear el archivo de respaldo." << std::endl;
        return;
    }

    // Obtener la fecha y hora actuales
    std::time_t ahora = std::time(nullptr);
    std::tm *fechaHora = std::localtime(&ahora);

    // Formatear la fecha y hora como "dd.MM.yyyy.HH.mm.ss"
    std::ostringstream fechaIngreso;
    fechaIngreso
        << std::setw(2) << std::setfill('0') << (fechaHora->tm_mday) << "."
        << std::setw(2) << std::setfill('0') << (fechaHora->tm_mon + 1) << "."
        << (fechaHora->tm_year + 1900) << "."
        << std::setw(2) << std::setfill('0') << (fechaHora->tm_hour) << "."
        << std::setw(2) << std::setfill('0') << (fechaHora->tm_min) << "."
        << std::setw(2) << std::setfill('0') << (fechaHora->tm_sec);

    // Escribir los datos de los libros en el archivo
    NodoLibro *actual = cabeza;
    do
    {
        archivoBackup << "Fecha Ingreso: " << fechaIngreso.str() << "\n";
        archivoBackup << "Titulo: " << actual->libro.getTitulo() << "\n";
        archivoBackup << "Autor: " << actual->libro.getAutor().getNombreCompleto() << "\n";
        archivoBackup << "Fecha de publicacion: " << actual->libro.getFechaPublicacion().getFechaComoString() << "\n";
        archivoBackup << "ISBN: " << actual->libro.getIsbn() << "\n";
        archivoBackup << "---\n";
        actual = actual->siguiente;
    } while (actual != cabeza);

    archivoBackup.close();
    std::cout << "\nRespaldo generado con éxito." << std::endl;
}

void ListaLibros::restaurarBackup(const string &fechaHora) const
{
    // Construir el nombre del archivo con prefijo backup_
    string nombreArchivo = "backup_" + fechaHora + ".txt";
    std::ifstream archivoBackup(nombreArchivo);

    if (!archivoBackup.is_open())
    {
        cout << "No se encontró un archivo de respaldo con la fecha y hora ingresada." << endl;
        return;
    }

    cout << "Restaurando libros desde el respaldo...\n";

    // Ignorar la primera línea de encabezado
    string linea;
    std::getline(archivoBackup, linea);

    // Variables para almacenar datos del libro
    string titulo, autor, fechaPublicacion, isbn;

    while (std::getline(archivoBackup, linea))
    {
        // Saltar línea de separación
        if (linea == "---")
            continue;

        if (linea.substr(0, 7) == "Titulo:")
        {
            titulo = linea.substr(8);
            std::getline(archivoBackup, linea);
            autor = linea.substr(7);
            std::getline(archivoBackup, linea);
            fechaPublicacion = linea.substr(22);
            std::getline(archivoBackup, linea);
            isbn = linea.substr(6);

            cout << "Titulo: " << titulo << endl;
            cout << "Autor: " << autor << endl;
            cout << "Fecha de publicacion: " << fechaPublicacion << endl;
            cout << "ISBN: " << isbn << endl;
            cout << "------" << endl;
        }
    }

    archivoBackup.close();
    cout << "\nRestauración completada con éxito." << endl;
}

void ListaLibros::buscarLibrosPorAutor(const string &idAutor, ListaLibros &resultados)
{
    // Cargar libros desde CSV
    std::vector<Libro> libros = cargarLibrosDesdeCSV();

    for (const auto &libro : libros)
    {
        if (libro.getAutor().getId() == idAutor)
        {
            resultados.registrarLibro(libro);
        }
    }
}

void ListaLibros::generarArchivoCSV() const
{
    std::ofstream archivoCSV("libros.csv", std::ios::app);

    if (!archivoCSV.is_open())
    {
        std::cerr << "\nError al abrir el archivo CSV para guardar los libros." << std::endl;
        return;
    }

    // Si es la primera vez que se abre el archivo, escribir los encabezados
    std::ifstream archivoExistente("libros.csv");
    if (archivoExistente.peek() == std::ifstream::traits_type::eof())
    {
        archivoCSV << "Titulo,Autor,Fecha de Publicacion,ISBN,Editorial\n";
    }
    archivoExistente.close();

    // Si la lista está vacía
    if (cabeza == nullptr)
    {
        archivoCSV.close();
        return;
    }

    // Recorrer la lista circular y escribir cada libro
    NodoLibro *actual = cabeza;
    do
    {
        std::string titulo = actual->libro.getTitulo();
        std::string nombreCompleto = actual->libro.getAutor().getNombre() + " " +
                                     actual->libro.getAutor().getApellido();
        std::string fechaPublicacion = actual->libro.getFechaPublicacion().getFechaComoString();
        std::string isbn = actual->libro.getIsbn();
        std::string editorial = actual->libro.getEditorial();

        // Reemplazar comas con punto y coma si existen
        std::replace(titulo.begin(), titulo.end(), ',', ';');
        std::replace(nombreCompleto.begin(), nombreCompleto.end(), ',', ';');
        std::replace(fechaPublicacion.begin(), fechaPublicacion.end(), ',', ';');
        std::replace(editorial.begin(), editorial.end(), ',', ';');

        // Agregar al final del archivo
        archivoCSV << titulo << ","
                   << nombreCompleto << ","
                   << fechaPublicacion << ","
                   << isbn << ","
                   << editorial << "\n";

        actual = actual->siguiente;
    } while (actual != cabeza);

    archivoCSV.close();
    std::cout << "\nLibro agregado al archivo CSV: libros.csv" << std::endl;
}

void ListaLibros::filtrarLibrosPorRangoDeAnios(int anioInicio, int anioFin) const
{
    std::vector<Libro> libros = cargarLibrosDesdeCSV();

    if (libros.empty())
    {
        std::cout << "\nNo hay libros disponibles para filtrar." << std::endl;
        return;
    }

    std::cout << "\nLibros publicados entre " << anioInicio << " y " << anioFin << ":" << std::endl;

    bool encontrado = false;

    std::for_each(libros.begin(), libros.end(), [&](const Libro &libro)
                  {
        int anioPublicacion = libro.getFechaPublicacion().getAnio();
        if (anioPublicacion >= anioInicio && anioPublicacion <= anioFin) {
            std::cout << "Titulo: " << libro.getTitulo() << std::endl;
            std::cout << "Autor: " << libro.getAutor().getNombreCompleto() << std::endl;
            std::cout << "Fecha de publicacion: "
                      << libro.getFechaPublicacion().getFechaComoString() << std::endl;
            std::cout << "ISBN: " << libro.getIsbn() << std::endl;
            std::cout << "Editorial: " << libro.getEditorial() << std::endl;
            std::cout << "------" << std::endl;
            encontrado = true;
        } });

    if (!encontrado)
    {
        std::cout << "No se encontraron libros publicados en el rango especificado." << std::endl;
    }
}

void ListaLibros::guardarAutorCSV(const Autor &autor)
{
    // Abrir el archivo de autores en modo append
    std::ofstream archivoAutores("autores.csv", std::ios::app);

    if (!archivoAutores.is_open())
    {
        std::cerr << "Error al abrir el archivo de autores." << std::endl;
        return;
    }

    // Verificar si el archivo está vacío para agregar encabezados
    std::ifstream archivoExistente("autores.csv");
    if (archivoExistente.peek() == std::ifstream::traits_type::eof())
    {
        archivoAutores << "ID,Nombre,Apellido,Nacionalidad\n";
    }
    archivoExistente.close();

    // Verificar si el autor ya existe antes de agregarlo
    std::vector<Autor> autoresExistentes = cargarAutoresDesdeCSV();
    for (const auto &autorExistente : autoresExistentes)
    {
        if (autorExistente.getId() == autor.getId())
        {
            archivoAutores.close();
            return; // El autor ya existe
        }
    }

    // Reemplazar comas con punto y coma para evitar problemas de parseo
    std::string nombre = autor.getNombre();
    std::string apellido = autor.getApellido();
    std::string nacionalidad = autor.getNacionalidad();

    std::replace(nombre.begin(), nombre.end(), ',', ';');
    std::replace(apellido.begin(), apellido.end(), ',', ';');
    std::replace(nacionalidad.begin(), nacionalidad.end(), ',', ';');

    // Guardar autor en el CSV
    archivoAutores << autor.getId() << ","
                   << nombre << ","
                   << apellido << ","
                   << nacionalidad << "\n";

    archivoAutores.close();
    std::cout << "\nAutor guardado: " << nombre << " " << apellido << std::endl;
}

std::vector<Autor> ListaLibros::cargarAutoresDesdeCSV()
{
    std::vector<Autor> autoresLeidos;
    std::ifstream archivoCSV("autores.csv");

    if (!archivoCSV.is_open())
    {
        std::cerr << "Error al abrir el archivo CSV de autores." << std::endl;
        return autoresLeidos;
    }

    // Saltar la línea de encabezados
    std::string encabezados;
    std::getline(archivoCSV, encabezados);

    std::string linea;
    while (std::getline(archivoCSV, linea))
    {
        std::stringstream ss(linea);
        std::string id, nombre, apellido, nacionalidad;

        // Leer cada campo
        std::getline(ss, id, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, apellido, ',');
        std::getline(ss, nacionalidad);

        // Restaurar comas reemplazadas
        std::replace(nombre.begin(), nombre.end(), ';', ',');
        std::replace(apellido.begin(), apellido.end(), ';', ',');
        std::replace(nacionalidad.begin(), nacionalidad.end(), ';', ',');

        // Crear objeto Autor
        Autor autor(nombre, apellido, id, nacionalidad);
        autoresLeidos.push_back(autor);
    }

    archivoCSV.close();
    return autoresLeidos;
}

void ListaLibros::guardarLibrosDeAutor(const Autor &autor)
{
    std::ofstream archivoLibrosAutor("libros_" + autor.getId() + ".csv", std::ios::app);

    if (!archivoLibrosAutor.is_open())
    {
        std::cerr << "Error al abrir el archivo de libros del autor." << std::endl;
        return;
    }

    // Verificar si el archivo está vacío para agregar encabezados
    std::ifstream archivoExistente("libros_" + autor.getId() + ".csv");
    if (archivoExistente.peek() == std::ifstream::traits_type::eof())
    {
        archivoLibrosAutor << "Titulo,Fecha de Publicacion,ISBN,Editorial\n";
    }
    archivoExistente.close();

    // Cargar libros existentes para evitar duplicados
    std::vector<Libro> librosDelAutor = cargarLibrosDeAutor(autor);

    // Recorrer la lista de libros y guardar solo los del autor actual
    NodoLibro *actual = cabeza;

    // Protección contra lista vacía
    if (actual == nullptr)
    {
        archivoLibrosAutor.close();
        return;
    }

    do
    {
        if (actual->libro.getAutor().getId() == autor.getId())
        {
            // Verificar si el libro ya existe en el archivo
            bool libroExiste = std::any_of(librosDelAutor.begin(), librosDelAutor.end(),
                                           [&](const Libro &libro)
                                           {
                                               return libro.getIsbn() == actual->libro.getIsbn();
                                           });

            if (!libroExiste)
            {
                std::string titulo = actual->libro.getTitulo();
                std::string fechaPublicacion =
                    std::to_string(actual->libro.getFechaPublicacion().getDia()) + "/" +
                    std::to_string(actual->libro.getFechaPublicacion().getMes()) + "/" +
                    std::to_string(actual->libro.getFechaPublicacion().getAnio());
                std::string isbn = actual->libro.getIsbn();
                std::string editorial = actual->libro.getEditorial();

                // Reemplazar comas con punto y coma
                std::replace(titulo.begin(), titulo.end(), ',', ';');
                std::replace(fechaPublicacion.begin(), fechaPublicacion.end(), ',', ';');
                std::replace(editorial.begin(), editorial.end(), ',', ';');

                archivoLibrosAutor << titulo << ","
                                   << fechaPublicacion << ","
                                   << isbn << ","
                                   << editorial << "\n";

                std::cout << "Libro guardado para el autor: " << titulo << std::endl;
            }
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    archivoLibrosAutor.close();
}

std::vector<Libro> ListaLibros::cargarLibrosDeAutor(const Autor &autor)
{
    std::vector<Libro> librosDelAutor;
    std::ifstream archivoLibrosAutor("libros_" + autor.getId() + ".csv");

    if (!archivoLibrosAutor.is_open())
    {
        // No es un error crítico si no existe el archivo aún
        return librosDelAutor;
    }

    // Saltar la línea de encabezados
    std::string encabezados;
    std::getline(archivoLibrosAutor, encabezados);

    std::string linea;
    while (std::getline(archivoLibrosAutor, linea))
    {
        std::stringstream ss(linea);
        std::string titulo, fechaStr, isbn, editorial;

        std::getline(ss, titulo, ',');
        std::getline(ss, fechaStr, ',');
        std::getline(ss, isbn, ',');
        std::getline(ss, editorial);

        // Restaurar comas
        std::replace(titulo.begin(), titulo.end(), ';', ',');
        std::replace(fechaStr.begin(), fechaStr.end(), ';', ',');
        std::replace(editorial.begin(), editorial.end(), ';', ',');

        // Parsear fecha
        int dia, mes, anio;
        std::stringstream fechaSS(fechaStr);
        char delimiter;
        fechaSS >> dia >> delimiter >> mes >> delimiter >> anio;

        // Crear libro (nota: necesitarás pasar el autor completo)
        Libro libro(titulo, autor, Fecha(dia, mes, anio), isbn, editorial);
        librosDelAutor.push_back(libro);
    }

    archivoLibrosAutor.close();
    return librosDelAutor;
}

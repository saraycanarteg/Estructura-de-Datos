#include "Generador_Pdf.cpp"

int main() {
    try {
        GeneradorPdf generador;
        
        // Crear un nuevo PDF
        generador.crearNuevoPdf("ejemplo.pdf");
        
        // Agregar texto
        generador.agregarTexto(50, 750, "Hola, este es un PDF generado con libharu");
        
        // Agregar una tabla (opcional)
        std::vector<std::vector<std::string>> datos = {
            {"Nombre", "Edad", "Ciudad"},
            {"Juan", "25", "Madrid"},
            {"María", "30", "Barcelona"}
        };
        generador.agregarTabla(datos, 50, 700, 100, 20);
        
        // Guardar PDF
        generador.guardarPdf();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
#ifndef GENERADOR_PDF_H
#define GENERADOR_PDF_H

#include <iostream>
#include <string>
#include <vector>
#include <hpdf.h>

class GeneradorPdf {
private:
    HPDF_Doc pdf;
    HPDF_Page page;
    std::string rutaArchivo;

public:
    GeneradorPdf();
    ~GeneradorPdf();

    // Método para crear un nuevo PDF
    bool crearNuevoPdf(const std::string& nombreArchivo);

    // Método para agregar texto en una posición específica
    void agregarTexto(float x, float y, const std::string& texto, float tamanoLetra = 12.0);

    // Método para agregar una imagen
    void agregarImagen(const std::string& rutaImagen, float x, float y, float ancho, float alto);

    // Método para agregar una tabla
    void agregarTabla(const std::vector<std::vector<std::string>>& datos, 
                      float x, float y, float anchoColumna, float altoFila);

    // Método para guardar el PDF
    bool guardarPdf();

    // Método para manejar errores de libharu
    void manejarError(HPDF_STATUS error, HPDF_STATUS detailedError);
};

#endif // GENERADOR_PDF_H

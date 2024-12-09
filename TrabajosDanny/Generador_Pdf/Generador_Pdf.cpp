#include "Generador_Pdf.h"
#include <iostream>
#include <stdexcept>

GeneradorPdf::GeneradorPdf() {
    pdf = HPDF_New(NULL, NULL);
    if (!pdf) {
        throw std::runtime_error("No se pudo crear el documento PDF");
    }
}

GeneradorPdf::~GeneradorPdf() {
    if (pdf) {
        HPDF_Free(pdf);
    }
}

bool GeneradorPdf::crearNuevoPdf(const std::string& nombreArchivo) {
    rutaArchivo = nombreArchivo;
    
    // Crear una nueva página
    page = HPDF_AddPage(pdf);
    if (!page) {
        manejarError(HPDF_GetError(pdf), 0);
        return false;
    }

    // Establecer tamaño de página (A4)
    HPDF_Page_SetWidth(page, 595);
    HPDF_Page_SetHeight(page, 842);

    return true;
}

void GeneradorPdf::agregarTexto(float x, float y, const std::string& texto, float tamanoLetra) {
    if (!page) {
        throw std::runtime_error("No se ha creado una página");
    }

    // Crear fuente
    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
    
    // Configurar página para escribir texto
    HPDF_Page_SetFontAndSize(page, font, tamanoLetra);
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, x, y, texto.c_str());
    HPDF_Page_EndText(page);
}

void GeneradorPdf::agregarImagen(const std::string& rutaImagen, float x, float y, float ancho, float alto) {
    if (!page) {
        throw std::runtime_error("No se ha creado una página");
    }

    // Cargar imagen
    HPDF_Image imagen = HPDF_LoadJPEGImageFromFile(pdf, rutaImagen.c_str());
    if (!imagen) {
        throw std::runtime_error("No se pudo cargar la imagen");
    }

    // Dibujar imagen
    HPDF_Page_DrawImage(page, imagen, x, y, ancho, alto);
}

void GeneradorPdf::agregarTabla(const std::vector<std::vector<std::string>>& datos, 
                                 float x, float y, float anchoColumna, float altoFila) {
    if (!page) {
        throw std::runtime_error("No se ha creado una página");
    }

    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
    HPDF_Page_SetFontAndSize(page, font, 10);

    for (size_t fila = 0; fila < datos.size(); ++fila) {
        for (size_t col = 0; col < datos[fila].size(); ++col) {
            float posX = x + (col * anchoColumna);
            float posY = y - (fila * altoFila);

            // Dibujar borde de celda
            HPDF_Page_Rectangle(page, posX, posY, anchoColumna, altoFila);
            HPDF_Page_Stroke(page);

            // Agregar texto de celda
            HPDF_Page_BeginText(page);
            HPDF_Page_TextOut(page, posX + 2, posY + 2, datos[fila][col].c_str());
            HPDF_Page_EndText(page);
        }
    }
}

bool GeneradorPdf::guardarPdf() {
    if (!pdf) {
        return false;
    }

    // Guardar el PDF
    HPDF_SaveToFile(pdf, rutaArchivo.c_str());
    return true;
}

void GeneradorPdf::manejarError(HPDF_STATUS error, HPDF_STATUS detailedError) {
    std::cerr << "Error en libharu: " << error << std::endl;
}
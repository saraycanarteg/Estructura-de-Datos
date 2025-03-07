#include "pdf_generator.h"
#include "hpdf.h"
#include <iostream>
#include <ctime>

void createGameRecordsPDF(const std::vector<GameRecord>& records, const std::string& outputFile) {
    HPDF_Doc pdf = HPDF_New(NULL, NULL);
    if (!pdf) {
        std::cerr << "Error al crear el PDF" << std::endl;
        return;
    }

    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica-Bold", NULL);
    HPDF_Font regularFont = HPDF_GetFont(pdf, "Helvetica", NULL);

    // Título
    HPDF_Page_SetFontAndSize(page, font, 24);
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, 200, 800, "Records de Tráfico Urbano");
    HPDF_Page_EndText(page);

    // Encabezados
    HPDF_Page_SetFontAndSize(page, font, 12);
    float yPos = 750;
    float xPos = 50;

    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, xPos, yPos, "Jugador");
    HPDF_Page_TextOut(page, xPos + 200, yPos, "Puntaje");
    HPDF_Page_TextOut(page, xPos + 300, yPos, "Fecha");
    HPDF_Page_EndText(page);

    // Línea separadora
    yPos -= 10;
    HPDF_Page_MoveTo(page, xPos, yPos);
    HPDF_Page_LineTo(page, xPos + 500, yPos);
    HPDF_Page_Stroke(page);

    // Registros
    HPDF_Page_SetFontAndSize(page, regularFont, 12);
    for (const auto& record : records) {
        yPos -= 30;
        
        if (yPos < 50) {  // Nueva página si no hay espacio
            page = HPDF_AddPage(pdf);
            HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
            yPos = 750;
        }

        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, xPos, yPos, record.playerName.c_str());
        
        // Convertir score a string
        std::string scoreStr = std::to_string(record.score);
        HPDF_Page_TextOut(page, xPos + 200, yPos, scoreStr.c_str());
        
        HPDF_Page_TextOut(page, xPos + 300, yPos, record.date.c_str());
        HPDF_Page_EndText(page);
    }

    HPDF_SaveToFile(pdf, outputFile.c_str());
    HPDF_Free(pdf);
    std::cout << "PDF de records generado exitosamente: " << outputFile << std::endl;
}
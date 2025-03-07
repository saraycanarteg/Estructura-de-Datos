#include "pdf_generator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "hpdf.h"

// Clase para manejar tokens de manera dinámica
class Token {
public:
    std::string value;
    Token* next;
    Token(std::string v) : value(v), next(nullptr) {}
};

// Función auxiliar para dividir string por delimitador
Token* splitString(std::string& str, char delim) {
    Token* head = nullptr;
    Token* current = nullptr;
    std::string temp;
    
    for(char& c : str) {
        if(c == delim) {
            if(!temp.empty()) {
                Token* newToken = new Token(temp);
                if(!head) {
                    head = newToken;
                    current = head;
                } else {
                    current->next = newToken;
                    current = newToken;
                }
                temp.clear();
            }
        } else {
            temp += c;
        }
    }
    
    if(!temp.empty()) {
        Token* newToken = new Token(temp);
        if(!head) {
            head = newToken;
        } else {
            current->next = newToken;
        }
    }
    
    return head;
}

void createPDF(const char* inputFile) {
    HPDF_Doc pdf;
    HPDF_Page page;
    HPDF_Font font;
    
    try {
        pdf = HPDF_New(NULL, NULL);
        
        // Configurar PDF
        HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);
        page = HPDF_AddPage(pdf);
        HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
        font = HPDF_GetFont(pdf, "Helvetica", NULL);
        
        // Configurar texto
        HPDF_Page_SetFontAndSize(page, font, 12);
        
        // Título
        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, 200, 800, "Registro de Puntajes - Trafico Urbano");
        HPDF_Page_EndText(page);
        
        // Leer archivo de records
        std::ifstream inFile(inputFile);
        std::string line;
        float y = 750;
        
        // Encabezados
        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, 50, y, "Posición");
        HPDF_Page_TextOut(page, 150, y, "Jugador");
        HPDF_Page_TextOut(page, 300, y, "Puntaje");
        HPDF_Page_TextOut(page, 400, y, "Fecha");
        HPDF_Page_EndText(page);
        
        y -= 20;
        
        // Línea separadora
        HPDF_Page_MoveTo(page, 50, y);
        HPDF_Page_LineTo(page, 550, y);
        HPDF_Page_Stroke(page);
        
        y -= 20;
        int position = 1;
        
        // Saltar la primera línea (encabezados)
        std::getline(inFile, line);
        
        while(std::getline(inFile, line)) {
            Token* tokens = splitString(line, ';');
            Token* current = tokens;
            int count = 0;
            
            HPDF_Page_BeginText(page);
            while(current != nullptr) {
                switch(count) {
                    case 0: // Jugador
                        HPDF_Page_TextOut(page, 150, y, current->value.c_str());
                        break;
                    case 1: // Puntaje
                        HPDF_Page_TextOut(page, 300, y, current->value.c_str());
                        break;
                    case 2: // Fecha
                        HPDF_Page_TextOut(page, 400, y, current->value.c_str());
                        break;
                }
                current = current->next;
                count++;
            }
            // Posición
            std::string pos = std::to_string(position);
            HPDF_Page_TextOut(page, 50, y, pos.c_str());
            
            HPDF_Page_EndText(page);
            
            // Limpiar memoria de tokens
            while(tokens != nullptr) {
                Token* temp = tokens;
                tokens = tokens->next;
                delete temp;
            }
            
            y -= 20;
            position++;
        }
        
        // Guardar PDF
        HPDF_SaveToFile(pdf, "records.pdf");
        HPDF_Free(pdf);
        
    } catch (...) {
        HPDF_Free(pdf);
        std::cerr << "Error generando PDF" << std::endl;
    }
}
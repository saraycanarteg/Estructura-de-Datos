#include "scanner.h"
#include <dirent.h>
#include <ctype.h>

// Function declarations
int contarCaracter(const char* str, char c);

// Variables globales
#define MAX_FILES 100
OpcionMenu menuPrincipal[] = {
    {"Escanear prototipos de archivo .h", escanearArchivo},
    {"Graficar funcion", graficarFuncion},
    {"Salir", NULL}
};

typedef struct {
    char nombre[256];
    char rutaCompleta[MAX_PATH];
} Archivo;

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limpiarPantalla() {
    system("cls");
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int listarArchivosH(const char* ruta, Archivo archivos[]) {
    DIR *dir;
    struct dirent *ent;
    int numArchivos = 0;
    char rutaCompleta[MAX_PATH];
    
    dir = opendir(ruta);
    if (dir == NULL) {
        printf("\nError al abrir el directorio: %s\n", ruta);
        return 0;
    }
    
    while ((ent = readdir(dir)) != NULL && numArchivos < MAX_FILES) {
        if (strstr(ent->d_name, ".h") != NULL) {
            snprintf(archivos[numArchivos].nombre, sizeof(archivos[numArchivos].nombre), "%s", ent->d_name);
            snprintf(archivos[numArchivos].rutaCompleta, sizeof(archivos[numArchivos].rutaCompleta), 
                    "%s\\%s", ruta, ent->d_name);
            numArchivos++;
        }
    }
    
    closedir(dir);
    return numArchivos;
}

// Función para seleccionar un archivo de la lista
char* seleccionarArchivo(Archivo archivos[], int numArchivos) {
    int seleccionActual = 0;
    
    while (1) {
        limpiarPantalla();
        printf("\nArchivos .h disponibles:\n");
        printf("=====================\n\n");
        
        for (int i = 0; i < numArchivos; i++) {
            if (i == seleccionActual) {
                printf("-> ");
            } else {
                printf("   ");
            }
            printf("%s\n", archivos[i].nombre);
        }
        
        int tecla = getch();
        if (tecla == 0 || tecla == 224) {
            tecla = getch();
            switch (tecla) {
                case ARROW_UP:
                    seleccionActual = (seleccionActual - 1 + numArchivos) % numArchivos;
                    break;
                case ARROW_DOWN:
                    seleccionActual = (seleccionActual + 1) % numArchivos;
                    break;
            }
        } else if (tecla == ENTER) {
            return archivos[seleccionActual].rutaCompleta;
        }
    }
}

void leerRuta(char* ruta) {
    printf("Ingrese la ruta del directorio: ");
    if (fgets(ruta, MAX_PATH, stdin) != NULL) {
        ruta[strcspn(ruta, "\n")] = 0;
        // Eliminar la barra final si existe
        int len = strlen(ruta);
        if (len > 0 && (ruta[len-1] == '\\' || ruta[len-1] == '/')) {
            ruta[len-1] = '\0';
        }
    }
}

void leerPrototipos(const char* ruta) {
    FILE* archivo;
    char linea[MAX_LINE];
    
    archivo = fopen(ruta, "r");
    if (archivo == NULL) {
        printf("\nError al abrir el archivo en la ruta: %s\n", ruta);
        printf("Presione cualquier tecla para continuar...");
        getch();
        return;
    }
    
    printf("\nPrototipos encontrados en el archivo:\n");
    printf("----------------------------------------\n");
    
    while (fgets(linea, MAX_LINE, archivo) != NULL) {
        if (strstr(linea, ";") != NULL) {
            if (strstr(linea, "#include") == NULL && strstr(linea, "#define") == NULL) {
                linea[strcspn(linea, "\n")] = 0;
                printf("%s\n", linea);
            }
        }
    }
    
    fclose(archivo);
    printf("\nPresione cualquier tecla para continuar...");
    getch();
}

void escanearArchivo() {
    char ruta[MAX_PATH];
    Archivo archivos[MAX_FILES];
    
    limpiarPantalla();
    fflush(stdin);
    leerRuta(ruta);
    
    int numArchivos = listarArchivosH(ruta, archivos);
    if (numArchivos == 0) {
        printf("\nNo se encontraron archivos .h en el directorio.\n");
        printf("Presione cualquier tecla para continuar...");
        getch();
        return;
    }
    
    char* archivoSeleccionado = seleccionarArchivo(archivos, numArchivos);
    leerPrototipos(archivoSeleccionado);
}

void extraerCodigoFuncion(const char* nombreFuncion, const char* rutaArchivoCpp, char* codigoFuncion, size_t maxLen) {
    FILE* archivo = fopen(rutaArchivoCpp, "r");
    if (!archivo) {
        printf("Error: No se encontró el archivo %s\n", rutaArchivoCpp);
        return;
    }

    printf("Buscando función: '%s'\n", nombreFuncion);
    
    char linea[MAX_LINE];
    bool dentroDeFuncion = false;
    int llaves = 0;
    *codigoFuncion = '\0';
    char bufferTemporal[MAX_LINE * 100] = "";  // Buffer más grande para acumular líneas
    
    // Buscar patrones comunes de declaración de función
    char patronesBusqueda[3][MAX_LINE];
    snprintf(patronesBusqueda[0], MAX_LINE, "void %s", nombreFuncion);
    snprintf(patronesBusqueda[1], MAX_LINE, "int %s", nombreFuncion);
    snprintf(patronesBusqueda[2], MAX_LINE, "%s", nombreFuncion);

    while (fgets(linea, sizeof(linea), archivo)) {
        if (!dentroDeFuncion) {
            // Buscar cualquiera de los patrones
            for (int i = 0; i < 3; i++) {
                if (strstr(linea, patronesBusqueda[i]) != NULL) {
                    // Verificar que es realmente una definición de función
                    if (strstr(linea, "(") != NULL && !strstr(linea, ";")) {
                        dentroDeFuncion = true;
                        strcat(bufferTemporal, linea);
                        llaves += contarCaracter(linea, '{');
                        break;
                    }
                }
            }
        } else {
            strcat(bufferTemporal, linea);
            llaves += contarCaracter(linea, '{') - contarCaracter(linea, '}');
            
            // Si encontramos el final de la función
            if (llaves == 0) {
                if (strlen(bufferTemporal) < maxLen) {
                    strcpy(codigoFuncion, bufferTemporal);
                    printf("Función encontrada y extraída correctamente.\n");
                    fclose(archivo);
                    return;
                } else {
                    printf("Error: El código de la función es demasiado largo para el buffer\n");
                    fclose(archivo);
                    return;
                }
            }
        }
    }

    fclose(archivo);
    
    if (strlen(codigoFuncion) == 0) {
        printf("Error: No se pudo encontrar la función '%s' en el archivo\n", nombreFuncion);
        // Mostrar las primeras líneas del archivo para debug
        printf("\nPrimeras líneas del archivo para verificación:\n");
        archivo = fopen(rutaArchivoCpp, "r");
        int lineasMostradas = 0;
        while (fgets(linea, sizeof(linea), archivo) && lineasMostradas < 5) {
            printf("%s", linea);
            lineasMostradas++;
        }
        fclose(archivo);
    }
}

// Función auxiliar para contar caracteres en una línea
int contarCaracter(const char* str, char c) {
    int count = 0;
    while (*str) {
        if (*str == c) count++;
        str++;
    }
    return count;
}


int count(const char* str, char c) {
    int count = 0;
    while (*str) if (*str++ == c) count++;
    return count;
}

void analizarComplejidad(const char* nombreFuncion, const char* rutaArchivoCpp) {
    char comando[1024];
    char codigoFuncion[4096] = "";

    printf("Buscando función '%s' en archivo: %s\n", nombreFuncion, rutaArchivoCpp);
    
    extraerCodigoFuncion(nombreFuncion, rutaArchivoCpp, codigoFuncion, sizeof(codigoFuncion));
    
    if (strlen(codigoFuncion) == 0) {
        printf("Error: No se pudo encontrar la función %s en el archivo %s\n", 
               nombreFuncion, rutaArchivoCpp);
        printf("Presione cualquier tecla para continuar...");
        getch();
        return;
    }

    // Guardar el código en un archivo temporal
    FILE* tempFile = fopen("temp_code.txt", "w");
    if (!tempFile) {
        printf("Error al crear el archivo temporal\n");
        return;
    }
    fprintf(tempFile, "%s", codigoFuncion);
    fclose(tempFile);

    // Llamar al analizador Python
    snprintf(comando, sizeof(comando), "python analyzer.py \"%s\" temp_code.txt", nombreFuncion);
    
    int resultado = system(comando);
    printf("\nResultado del análisis: %d\n", resultado);
    printf("Se ha generado el gráfico 'complexity_analysis.png'\n");
    printf("Presione cualquier tecla para continuar...");
    getch();
}

void seleccionarFuncion(const char* rutaH) {
    FILE* archivo;
    char linea[MAX_LINE];
    char funciones[50][MAX_LINE];
    char nombresFunciones[50][MAX_LINE];
    int numFunciones = 0;
    int seleccionActual = 0;
    
    // Obtener la ruta del archivo .cpp correspondiente
    char rutaCpp[MAX_PATH];
    strncpy(rutaCpp, rutaH, MAX_PATH);
    char* extension = strstr(rutaCpp, ".h");
    if (extension) {
        strcpy(extension, ".cpp");
    }
    
    archivo = fopen(rutaH, "r");
    if (archivo == NULL) {
        printf("\nError al abrir el archivo en la ruta: %s\n", rutaH);
        printf("Presione cualquier tecla para continuar...");
        getch();
        return;
    }
    
    while (fgets(linea, MAX_LINE, archivo) != NULL && numFunciones < 50) {
        if (strstr(linea, ";") != NULL && 
            strstr(linea, "#include") == NULL && 
            strstr(linea, "#define") == NULL &&
            strstr(linea, "typedef") == NULL &&
            strstr(linea, "extern") == NULL) {
            
            char* ptr = linea;
            while (*ptr == ' ' || *ptr == '\t') ptr++;
            strcpy(funciones[numFunciones], ptr);
            
            char nombreFuncion[MAX_LINE];
            char* inicio = strchr(ptr, ' ');
            char* fin = strchr(ptr, '(');
            
            if (inicio && fin && fin > inicio) {
                strncpy(nombreFuncion, inicio + 1, fin - inicio - 1);
                nombreFuncion[fin - inicio - 1] = '\0';
                // Eliminar espacios en blanco al final del nombre
                char* end = nombreFuncion + strlen(nombreFuncion) - 1;
                while (end > nombreFuncion && isspace((unsigned char)*end)) {
                    *end = '\0';
                    end--;
                }
                strcpy(nombresFunciones[numFunciones], nombreFuncion);
                numFunciones++;
            }
        }
    }
    fclose(archivo);
    
    if (numFunciones == 0) {
        printf("\nNo se encontraron declaraciones de funciones en el archivo.\n");
        printf("Presione cualquier tecla para continuar...");
        getch();
        return;
    }
    
    while (1) {
        limpiarPantalla();
        printf("\nSeleccione una función para analizar:\n");
        printf("=====================================\n\n");
        
        for (int i = 0; i < numFunciones; i++) {
            if (i == seleccionActual) {
                printf("-> ");
            } else {
                printf("   ");
            }
            printf("%s\n", funciones[i]);
        }
        
        int tecla = getch();
        if (tecla == 0 || tecla == 224) {
            tecla = getch();
            switch (tecla) {
                case ARROW_UP:
                    seleccionActual = (seleccionActual - 1 + numFunciones) % numFunciones;
                    break;
                case ARROW_DOWN:
                    seleccionActual = (seleccionActual + 1) % numFunciones;
                    break;
            }
        } else if (tecla == ENTER) {
            printf("\nAnalizando función: %s\n", nombresFunciones[seleccionActual]);
            printf("En archivo: %s\n", rutaCpp);
            analizarComplejidad(nombresFunciones[seleccionActual], rutaCpp);
            break;
        }
    }
}

void graficarFuncion() {
    char ruta[MAX_PATH];
    Archivo archivos[MAX_FILES];
    
    limpiarPantalla();
    fflush(stdin);
    leerRuta(ruta);
    
    int numArchivos = listarArchivosH(ruta, archivos);
    if (numArchivos == 0) {
        printf("\nNo se encontraron archivos .h en el directorio.\n");
        printf("Presione cualquier tecla para continuar...");
        getch();
        return;
    }
    
    char* archivoSeleccionado = seleccionarArchivo(archivos, numArchivos);
    seleccionarFuncion(archivoSeleccionado);
}

void mostrarMenu(OpcionMenu opciones[], int numOpciones) {
    int seleccionActual = 0;
    int tecla;
    
    while (1) {
        limpiarPantalla();
        printf("\nMenú Principal\n");
        printf("=============\n\n");
        
        for (int i = 0; i < numOpciones; i++) {
            if (i == seleccionActual) {
                printf("-> ");
            } else {
                printf("   ");
            }
            printf("%s\n", opciones[i].titulo);
        }
        
        tecla = getch();
        if (tecla == 0 || tecla == 224) {
            tecla = getch();
            switch (tecla) {
                case ARROW_UP:
                    seleccionActual = (seleccionActual - 1 + numOpciones) % numOpciones;
                    break;
                case ARROW_DOWN:
                    seleccionActual = (seleccionActual + 1) % numOpciones;
                    break;
            }
        } else if (tecla == ENTER) {
            if (opciones[seleccionActual].funcion == NULL) {
                return;
            }
            opciones[seleccionActual].funcion();
        }
    }
}

int main() {
    int numOpciones = sizeof(menuPrincipal) / sizeof(menuPrincipal[0]);
    mostrarMenu(menuPrincipal, numOpciones);
    return 0;
}
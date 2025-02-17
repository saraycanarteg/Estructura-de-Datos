#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

// Constantes
const int MAX_ARRAY = 20;
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 700;
const int BAR_WIDTH = WINDOW_WIDTH / MAX_ARRAY;
const int TEXT_SIZE = 2;  
const int TITLE_SIZE = 3;

// Estructura para medir tiempo
struct Temporizador {
    clock_t inicio;
    clock_t fin;
};

// Estructura para pasos de la animación
struct AnimacionPaso {
    char codigo[100];
    char complejidad[20];
    char explicacion[100];
    char costoAcumulado[50];
    bool mostrado;
};

// Estructura para análisis final
struct AnalisisFinal {
    char texto[100];
    bool mostrado;
};

// Variables globales para la animación
AnimacionPaso pasos[] = {
    {
        "void mergeSort(int arr[], int l, int r) {",
        "1",
        "Declaracion de funcion",
        "1",
        false
    },
    {
        "    if (l < r) {",
        "1",
        "Comparacion simple",
        "2",
        false
    },
    {
        "        int m = l + (r - l) / 2;",
        "1",
        "Calculo del punto medio",
        "3",
        false
    },
    {
        "        mergeSort(arr, l, m);",
        "T(n/2)",
        "Primera llamada recursiva con mitad del array",
        "T(n/2) + 3",
        false
    },
    {
        "        mergeSort(arr, m + 1, r);",
        "T(n/2)",
        "Segunda llamada recursiva con mitad del array",
        "2T(n/2) + 3",
        false
    },
    {
        "        merge(arr, l, m, r);",
        "n",
        "Fusion de subarrays - recorre n elementos",
        "2T(n/2) + n + 3",
        false
    }
};

AnalisisFinal analisis_final[] = {
    {"Analisis de la Recurrencia:", false},
    {"T(n) = 2T(n/2) + n + 3", false},
    {"T(n/2) = 2T(n/4) + n/2 + 3", false},
    {"...", false},
    {"Por el Teorema Maestro:", false},
    {"a=2, b=2, f(n)=n", false},
    {"log_b(a) = log_2(2) = 1", false},
    {"f(n) = n = n^1", false},
    {"Caso 2: f(n) = Θ(n^log_b(a))", false},
    {"Por lo tanto: T(n) = Θ(n log n)", false}
};

// Prototipos de funciones
void iniciar_tiempo(Temporizador& t);
double detener_tiempo(Temporizador& t);
void dibujar_array(int arr[], int n, int i, int j);
void mostrar_complejidad(const char* algoritmo, double tiempo);
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
void mostrar_analisis_codigo(int pagina);
void ejecutar_mergesort(int arr[]);
void reiniciar_estados();

// Implementación de funciones
void iniciar_tiempo(Temporizador& t) {
    t.inicio = clock();
}

double detener_tiempo(Temporizador& t) {
    t.fin = clock();
    return ((double)(t.fin - t.inicio)) / CLOCKS_PER_SEC;
}

void dibujar_array(int arr[], int n, int i, int j) {
    cleardevice();
    // Dibujar marco para el gráfico
    setcolor(DARKGRAY);
    rectangle(50, 100, WINDOW_WIDTH - 50, WINDOW_HEIGHT - 50);
    
    for (int k = 0; k < n; k++) {
        int altura = arr[k] * (WINDOW_HEIGHT - 200) / 100;  // Ajustado para dejar espacio para texto
        int x = 50 + k * ((WINDOW_WIDTH - 100) / n);  
        int ancho_barra = ((WINDOW_WIDTH - 100) / n) - 5;  
        
        if (k == i || k == j)
            setfillstyle(SOLID_FILL, RED);
        else
            setfillstyle(SOLID_FILL, LIGHTBLUE);  
            
        bar(x, WINDOW_HEIGHT - 50 - altura, x + ancho_barra, WINDOW_HEIGHT - 50);
        
        // Mostrar valor numérico sobre cada barra
        char valor[10];
        sprintf(valor, "%d", arr[k]);
        setcolor(WHITE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        outtextxy(x + ancho_barra/2 - 10, WINDOW_HEIGHT - 40 - altura, valor);
    }
    delay(50);
}

void mostrar_complejidad(const char* algoritmo, double tiempo) {
    // Fondo para el texto de tiempo
    setfillstyle(SOLID_FILL, BLACK);
    bar(0, 0, WINDOW_WIDTH, 80);
    
    // Título del algoritmo
    settextstyle(DEFAULT_FONT, HORIZ_DIR, TITLE_SIZE);
    setcolor(YELLOW);
    outtextxy(50, 20, (char*)algoritmo);
    
    // Tiempo de ejecución
    char buffer[100];
    sprintf(buffer, "Tiempo: %.3f segundos", tiempo);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, TEXT_SIZE);
    setcolor(LIGHTGREEN);
    outtextxy(50, 50, buffer);
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    int* L = new int[n1];
    int* R = new int[n2];
    
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
        
    i = 0;
    j = 0;
    k = l;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
        dibujar_array(arr, MAX_ARRAY, k, -1);
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        dibujar_array(arr, MAX_ARRAY, k, -1);
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        dibujar_array(arr, MAX_ARRAY, k, -1);
    }
    
    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void reiniciar_estados() {
    for (int i = 0; i < 6; i++) {
        pasos[i].mostrado = false;
    }
    for (int i = 0; i < 10; i++) {
        analisis_final[i].mostrado = false;
    }
}

void mostrar_analisis_codigo(int pagina) {
    cleardevice();
    setbkcolor(BLACK);
    cleardevice();

    // Título principal con nuevo tamaño
    settextstyle(DEFAULT_FONT, HORIZ_DIR, TITLE_SIZE);
    setcolor(WHITE);
    outtextxy(50, 30, "Analisis de MergeSort - Calculo de Complejidad");

    // Ajustar tamaño de texto para el contenido
    settextstyle(DEFAULT_FONT, HORIZ_DIR, TEXT_SIZE);

    if (pagina == 1) {
        int y = 100;  // Aumentado el espacio inicial
        bool todos_mostrados = true;
        
        for (int i = 0; i < 6; i++) {
            if (pasos[i].mostrado) {
                setcolor(CYAN);
                outtextxy(50, y, pasos[i].codigo);
                
                setcolor(YELLOW);
                char comp[80];
                sprintf(comp, "Complejidad: %s", pasos[i].complejidad);
                outtextxy(600, y, comp);  // Ajustado posición X
                
                // Explicación
                setcolor(GREEN);
                outtextxy(50, y + 25, pasos[i].explicacion);
                
                // Costo acumulado
                setcolor(MAGENTA);
                char costo[80];
                sprintf(costo, "Acumulado: %s", pasos[i].costoAcumulado);
                outtextxy(600, y + 25, costo);  // Ajustado posición X
            }
            else {
                todos_mostrados = false;
            }
            y += 70;  
        }
        
        setcolor(WHITE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, TEXT_SIZE);
        if (todos_mostrados) {
            outtextxy(50, WINDOW_HEIGHT - 100, "Presione ESPACIO para ver el analisis final");
        }
        else {
            outtextxy(50, WINDOW_HEIGHT - 100, "Presione ENTER para mostrar siguiente paso");
        }
    }
    else {
        int y = 100;
        bool todos_mostrados = true;
        setcolor(WHITE);
        
        for (int i = 0; i < 10; i++) {
            if (analisis_final[i].mostrado) {
                outtextxy(50, y, analisis_final[i].texto);
            }
            else {
                todos_mostrados = false;
            }
            y += 45; 
        }
        
        settextstyle(DEFAULT_FONT, HORIZ_DIR, TEXT_SIZE);
        if (todos_mostrados) {
            outtextxy(50, WINDOW_HEIGHT - 100, "Presione ESPACIO para ver la visualizacion");
        }
        else {
            outtextxy(50, WINDOW_HEIGHT - 100, "Presione ENTER para mostrar siguiente paso");
        }
    }
}

void ejecutar_mergesort(int arr[]) {
    int pagina_actual = 1;
    bool mostrar_ordenamiento = false;
    int paso_actual = 0;
    Temporizador t;
    
    setbkcolor(BLACK);
    cleardevice();
    
    while (true) {
        if (!mostrar_ordenamiento) {
            mostrar_analisis_codigo(pagina_actual);
            char tecla = getch();
            
            if (tecla == 27) { // ESC
                break;
            }
            else if (tecla == 32) { // ESPACIO
                if ((pagina_actual == 1 && paso_actual >= 6) || 
                    (pagina_actual == 2 && paso_actual >= 10)) {
                    if (pagina_actual == 2) {
                        mostrar_ordenamiento = true;
                        iniciar_tiempo(t);
                    } else {
                        pagina_actual = 2;
                        paso_actual = 0;
                        reiniciar_estados();
                    }
                }
            }
            else if (tecla == 13) { // ENTER
                if (pagina_actual == 1 && paso_actual < 6) {
                    pasos[paso_actual].mostrado = true;
                    paso_actual++;
                }
                else if (pagina_actual == 2 && paso_actual < 10) {
                    analisis_final[paso_actual].mostrado = true;
                    paso_actual++;
                }
            }
        }
        else {
            dibujar_array(arr, MAX_ARRAY, -1, -1);
            delay(1000);
            mergeSort(arr, 0, MAX_ARRAY - 1);
            double tiempo = detener_tiempo(t);
            mostrar_complejidad("Merge Sort", tiempo);
            getch();
            break;
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MergeSort Visualization");
    
    int arr[MAX_ARRAY];
    // Inicializar array con números aleatorios
    srand(time(NULL));
    for (int i = 0; i < MAX_ARRAY; i++) {
        arr[i] = rand() % 100 + 1;
    }
    
    // Inicializar modo gráfico
    //initgraph(&gd, &gm, "");
    
    // Ejecutar la visualización
    ejecutar_mergesort(arr);
    
    // Cerrar modo gráfico
    closegraph();
    
    return 0;
}
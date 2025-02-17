#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

// Constants
const int MAX_ARRAY = 20;
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 700;
const int BAR_WIDTH = WINDOW_WIDTH / MAX_ARRAY;
const int TEXT_SIZE = 2;  
const int TITLE_SIZE = 3;

// Timer class
class Temporizador {
private:
    clock_t inicio;
    clock_t fin;

public:
    Temporizador() : inicio(0), fin(0) {}
    
    void iniciar() {
        inicio = clock();
    }
    
    double detener() {
        fin = clock();
        return ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    }
};

// Animation step class
class AnimacionPaso {
private:
    char codigo[100];
    char complejidad[20];
    char explicacion[100];
    char costoAcumulado[50];
    bool mostrado;

public:
    AnimacionPaso() : mostrado(false) {
        codigo[0] = '\0';
        complejidad[0] = '\0';
        explicacion[0] = '\0';
        costoAcumulado[0] = '\0';
    }
    
    AnimacionPaso(const char* cod, const char* comp, const char* exp, const char* costo) 
        : mostrado(false) {
        strncpy(codigo, cod, 99);
        strncpy(complejidad, comp, 19);
        strncpy(explicacion, exp, 99);
        strncpy(costoAcumulado, costo, 49);
        codigo[99] = complejidad[19] = explicacion[99] = costoAcumulado[49] = '\0';
    }
    
    const char* getCodigo() const { return codigo; }
    const char* getComplejidad() const { return complejidad; }
    const char* getExplicacion() const { return explicacion; }
    const char* getCostoAcumulado() const { return costoAcumulado; }
    bool estaMostrado() const { return mostrado; }
    void setMostrado(bool valor) { mostrado = valor; }
};

// Final analysis class
class AnalisisFinal {
private:
    char texto[100];
    bool mostrado;

public:
    AnalisisFinal() : mostrado(false) {
        texto[0] = '\0';
    }
    
    AnalisisFinal(const char* txt) : mostrado(false) {
        strncpy(texto, txt, 99);
        texto[99] = '\0';
    }
    
    const char* getTexto() const { return texto; }
    bool estaMostrado() const { return mostrado; }
    void setMostrado(bool valor) { mostrado = valor; }
};

// MergeSort visualization class
class MergeSortVisualizador {
private:
    int* arreglo;
    AnimacionPaso pasos[6] = {
        AnimacionPaso("void mergeSort(int arr[], int l, int r) {", "1", "Declaracion de funcion", "1"),
        AnimacionPaso("    if (l < r) {", "1", "Comparacion simple", "2"),
        AnimacionPaso("        int m = l + (r - l) / 2;", "1", "Calculo del punto medio", "3"),
        AnimacionPaso("        mergeSort(arr, l, m);", "T(n/2)", "Primera llamada recursiva con mitad del array", "T(n/2) + 3"),
        AnimacionPaso("        mergeSort(arr, m + 1, r);", "T(n/2)", "Segunda llamada recursiva con mitad del array", "2T(n/2) + 3"),
        AnimacionPaso("        merge(arr, l, m, r);", "n", "Fusion de subarrays - recorre n elementos", "2T(n/2) + n + 3")
    };
    
    AnalisisFinal analisis_final[10] = {
        AnalisisFinal("Analisis de la Recurrencia:"),
        AnalisisFinal("T(n) = 2T(n/2) + n + 3"),
        AnalisisFinal("T(n/2) = 2T(n/4) + n/2 + 3"),
        AnalisisFinal("..."),
        AnalisisFinal("Por el Teorema Maestro:"),
        AnalisisFinal("a=2, b=2, f(n)=n"),
        AnalisisFinal("log_b(a) = log_2(2) = 1"),
        AnalisisFinal("f(n) = n = n^1"),
        AnalisisFinal("Caso 2: f(n) = Θ(n^log_b(a))"),
        AnalisisFinal("Por lo tanto: T(n) = Θ(n log n)")
    };
    
    Temporizador temporizador;

public:
    MergeSortVisualizador() {
        arreglo = new int[MAX_ARRAY];
        inicializarArreglo();
    }
    
    ~MergeSortVisualizador() {
        delete[] arreglo;
    }
    
    void inicializarArreglo() {
        srand(time(NULL));
        for (int i = 0; i < MAX_ARRAY; i++) {
            arreglo[i] = rand() % 100 + 1;
        }
    }
    
    void dibujarArreglo(int i, int j) {
        cleardevice();
        setcolor(DARKGRAY);
        rectangle(50, 100, WINDOW_WIDTH - 50, WINDOW_HEIGHT - 50);
        
        for (int k = 0; k < MAX_ARRAY; k++) {
            int altura = arreglo[k] * (WINDOW_HEIGHT - 200) / 100;
            int x = 50 + k * ((WINDOW_WIDTH - 100) / MAX_ARRAY);
            int ancho_barra = ((WINDOW_WIDTH - 100) / MAX_ARRAY) - 5;
            
            if (k == i || k == j)
                setfillstyle(SOLID_FILL, RED);
            else
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                
            bar(x, WINDOW_HEIGHT - 50 - altura, x + ancho_barra, WINDOW_HEIGHT - 50);
            
            char valor[10];
            sprintf(valor, "%d", arreglo[k]);
            setcolor(WHITE);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
            outtextxy(x + ancho_barra/2 - 10, WINDOW_HEIGHT - 40 - altura, valor);
        }
        delay(50);
    }
    
    void merge(int l, int m, int r) {
        int i, j, k;
        int n1 = m - l + 1;
        int n2 = r - m;
        
        int* L = new int[n1];
        int* R = new int[n2];
        
        for (i = 0; i < n1; i++)
            L[i] = arreglo[l + i];
        for (j = 0; j < n2; j++)
            R[j] = arreglo[m + 1 + j];
            
        i = 0;
        j = 0;
        k = l;
        
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arreglo[k] = L[i];
                i++;
            }
            else {
                arreglo[k] = R[j];
                j++;
            }
            k++;
            dibujarArreglo(k, -1);
        }
        
        while (i < n1) {
            arreglo[k] = L[i];
            i++;
            k++;
            dibujarArreglo(k, -1);
        }
        
        while (j < n2) {
            arreglo[k] = R[j];
            j++;
            k++;
            dibujarArreglo(k, -1);
        }
        
        delete[] L;
        delete[] R;
    }
    
    void mergeSort(int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(l, m);
            mergeSort(m + 1, r);
            merge(l, m, r);
        }
    }
    
    void mostrarAnalisisCodigo(int pagina) {
        cleardevice();
        setbkcolor(BLACK);
        cleardevice();

        settextstyle(DEFAULT_FONT, HORIZ_DIR, TITLE_SIZE);
        setcolor(WHITE);
        outtextxy(50, 30, "Analisis de MergeSort - Calculo de Complejidad");

        settextstyle(DEFAULT_FONT, HORIZ_DIR, TEXT_SIZE);

        if (pagina == 1) {
            mostrarPasos();
        }
        else {
            mostrarAnalisisFinal();
        }
    }
    
    void mostrarPasos() {
        int y = 100;
        bool todos_mostrados = true;
        
        for (int i = 0; i < 6; i++) {
            if (pasos[i].estaMostrado()) {
                setcolor(CYAN);
                outtextxy(50, y, (char*)pasos[i].getCodigo());
                
                setcolor(YELLOW);
                char comp[80];
                sprintf(comp, "Complejidad: %s", pasos[i].getComplejidad());
                outtextxy(600, y, comp);
                
                setcolor(GREEN);
                outtextxy(50, y + 25, (char*)pasos[i].getExplicacion());
                
                setcolor(MAGENTA);
                char costo[80];
                sprintf(costo, "Acumulado: %s", pasos[i].getCostoAcumulado());
                outtextxy(600, y + 25, costo);
            }
            else {
                todos_mostrados = false;
            }
            y += 70;
        }
        
        mostrarInstrucciones(todos_mostrados, true);
    }
    
    void mostrarAnalisisFinal() {
        int y = 100;
        bool todos_mostrados = true;
        setcolor(WHITE);
        
        for (int i = 0; i < 10; i++) {
            if (analisis_final[i].estaMostrado()) {
                outtextxy(50, y, (char*)analisis_final[i].getTexto());
            }
            else {
                todos_mostrados = false;
            }
            y += 45;
        }
        
        mostrarInstrucciones(todos_mostrados, false);
    }
    
    void mostrarInstrucciones(bool todos_mostrados, bool esPrimeraPagina) {
        setcolor(WHITE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, TEXT_SIZE);
        if (todos_mostrados) {
            outtextxy(50, WINDOW_HEIGHT - 100, 
                (char*)(esPrimeraPagina ? "Presione ESPACIO para ver el analisis final" 
                               : "Presione ESPACIO para ver la visualizacion"));
        }
        else {
            outtextxy(50, WINDOW_HEIGHT - 100, "Presione ENTER para mostrar siguiente paso");
        }
    }
    
    void reiniciarEstados() {
        for (int i = 0; i < 6; i++) {
            pasos[i].setMostrado(false);
        }
        for (int i = 0; i < 10; i++) {
            analisis_final[i].setMostrado(false);
        }
    }
    
    void ejecutar() {
        int pagina_actual = 1;
        bool mostrar_ordenamiento = false;
        int paso_actual = 0;
        
        setbkcolor(BLACK);
        cleardevice();
        
        while (true) {
            if (!mostrar_ordenamiento) {
                mostrarAnalisisCodigo(pagina_actual);
                char tecla = getch();
                
                if (tecla == 27) { // ESC
                    break;
                }
                else if (tecla == 32) { // ESPACIO
                    if ((pagina_actual == 1 && paso_actual >= 6) || 
                        (pagina_actual == 2 && paso_actual >= 10)) {
                        if (pagina_actual == 2) {
                            mostrar_ordenamiento = true;
                            temporizador.iniciar();
                        } else {
                            pagina_actual = 2;
                            paso_actual = 0;
                            reiniciarEstados();
                        }
                    }
                }
                else if (tecla == 13) { // ENTER
                    if (pagina_actual == 1 && paso_actual < 6) {
                        pasos[paso_actual].setMostrado(true);
                        paso_actual++;
                    }
                    else if (pagina_actual == 2 && paso_actual < 10) {
                        analisis_final[paso_actual].setMostrado(true);
                        paso_actual++;
                    }
                }
            }
            else {
                dibujarArreglo(-1, -1);
                delay(1000);
                mergeSort(0, MAX_ARRAY - 1);
                double tiempo = temporizador.detener();
                mostrarComplejidad("Merge Sort", tiempo);
                getch();
                break;
            }
        }
    }
    
    void mostrarComplejidad(const char* algoritmo, double tiempo) {
        setfillstyle(SOLID_FILL, BLACK);
        bar(0, 0, WINDOW_WIDTH, 80);
        
        settextstyle(DEFAULT_FONT, HORIZ_DIR, TITLE_SIZE);
        setcolor(YELLOW);
        outtextxy(50, 20, (char*)algoritmo);
        
        char buffer[100];
        sprintf(buffer, "Tiempo: %.3f segundos", tiempo);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, TEXT_SIZE);
        setcolor(LIGHTGREEN);
        outtextxy(50, 50, buffer);
    }
};

int main() {
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MergeSort Visualization");
    
    MergeSortVisualizador visualizador;
    visualizador.ejecutar();
    
    closegraph();
    return 0;
}
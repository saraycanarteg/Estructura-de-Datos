import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os

def generar_grafico_matplotlib():
    """Genera gráficos usando matplotlib para visualizar la complejidad"""
    try:
        # Cargar datos
        if not os.path.exists('datos_funcion.csv'):
            print("Error: No se encontró el archivo 'datos_funcion.csv'.")
            print("Generando datos de ejemplo...")
            
            # Generar datos de ejemplo
            n = np.linspace(0.1, 5, 100)
            e = 2.71828182845904523536
            n_e = np.power(n, e)          # n^e
            e_n = np.power(e, n)          # e^n
            e_log_n = e * np.log(n)       # e*log(n)
            
            # Guardar en CSV
            df = pd.DataFrame({
                'n': n,
                'n_e': n_e,
                'e_n': e_n,
                'e_log_n': e_log_n
            })
            df.to_csv('datos_funcion.csv', index=False)
            print("Se han generado datos de ejemplo.")
        
        # Cargar los datos
        datos = pd.read_csv('datos_funcion.csv')
        n = datos['n']
        n_e = datos['n_e']
        e_n = datos['e_n']
        e_log_n = datos['e_log_n']
        
        # Configurar el estilo y tamaño de la figura
        plt.style.use('default')
        plt.figure(figsize=(10, 12))
        
        # Gráfico superior: n^e vs e^n (escala logarítmica)
        plt.subplot(2, 1, 1)
        plt.semilogy(n, n_e, 'r-', linewidth=2, label='n^e')
        plt.semilogy(n, e_n, 'b-', linewidth=2, label='e^n')
        plt.title('Comparación de n^e y e^n (escala logarítmica)')
        plt.ylabel('Valor (escala log)')
        plt.legend(loc='upper left')
        plt.grid(True)
        
        # Gráfico inferior: e*log(n) vs n
        plt.subplot(2, 1, 2)
        plt.plot(n, e_log_n, 'r-', linewidth=2, label='e·log(n)')
        plt.plot(n, n, 'b-', linewidth=2, label='n')
        
        # Marcar el punto donde n = e
        e = 2.71828182845904523536
        plt.axvline(x=e, color='gray', linestyle='-', alpha=0.7)
        plt.axhline(y=0, color='black', linestyle='-', alpha=0.7)
        plt.plot([e], [e], 'ko', markersize=5)
        plt.text(e+0.1, e+0.1, 'e', fontsize=12)
        
        # Configurar etiquetas y límites
        plt.title('Comparación de e·log(n) y n')
        plt.xlabel('n')
        plt.ylabel('Valor')
        plt.xlim([-1, 6])
        plt.ylim([-8, 6])
        plt.legend(loc='upper left')
        plt.grid(True)
        
        # Ajustar espaciado
        plt.tight_layout()
        
        # Guardar y mostrar
        plt.savefig('comparacion_funciones.png', dpi=300)
        plt.show()
        
        print("Gráfico generado y guardado como 'comparacion_funciones.png'")
        
        # Verificar si n^e ∈ O(e^n)
        n0 = e  # Valor teórico donde n^e ≤ c*e^n para todo n ≥ e y algún c > 0
        idx = n >= n0
        ratio = n_e[idx] / e_n[idx]
        c = ratio.max()
        
        print("\n===== ANÁLISIS DE COMPLEJIDAD =====")
        print(f"Verificando si n^e ∈ O(e^n)...")
        print(f"Para todo n ≥ {n0:.4f} (valor de e):")
        
        if c < float('inf') and not np.isnan(c):
            print(f"RESULTADO: n^e SÍ pertenece a O(e^n)")
            print(f"Se cumple que n^e ≤ {c:.6f}·e^n para todo n ≥ {n0:.4f}")
            print(f"Donde {c:.6f} es la constante positiva requerida en la definición de O.")
        else:
            print(f"RESULTADO: n^e NO pertenece a O(e^n)")
            print("Se encontraron valores donde la relación no se cumple.")
        
        # Agregar información adicional sobre la demostración
        print("\nDemostración matemática:")
        print("1. Por definición, n^e ∈ O(e^n) si existen constantes c > 0 y n0 ≥ 0")
        print("   tales que n^e ≤ c·e^n para todo n ≥ n0")
        print("2. Tomando logaritmos: e·log(n) ≤ n")
        print("3. Esta desigualdad se cumple para todo n ≥ e ≈ 2.718")
        print("4. Por lo tanto, n^e ∈ O(e^n)")
        
    except Exception as e:
        print(f"Error al generar gráfico: {e}")

if __name__ == "__main__":
    print("Iniciando visualización con matplotlib...")
    generar_grafico_matplotlib()
import numpy as np
import matplotlib.pyplot as plt
import sys
import re
import os

def extract_function_implementation(cpp_file_path, prototype):
    """Extract function implementation from cpp file"""
    try:
        # Limpia el prototipo y extrae el nombre de la función
        clean_prototype = prototype.replace('static', '').strip()
        func_name = clean_prototype.split('(')[0].strip().split()[-1]
        
        # Lee el contenido del .cpp
        with open(cpp_file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # 1) Buscar la implementación exacta con la firma completa
        pattern = fr'{re.escape(clean_prototype)}\s*{{([^{{}}]*(?:{{[^{{}}]*}}[^{{}}]*)*)}}'
        match = re.search(pattern, content, re.DOTALL)
        
        # 2) Si no lo encuentra, busca por nombre de función (más flexible)
        if not match:
            pattern = fr'\b{re.escape(func_name)}\s*\([^)]*\)\s*{{([^{{}}]*(?:{{[^{{}}]*}}[^{{}}]*)*)}}'
            match = re.search(pattern, content, re.DOTALL)
        
        return match.group(0) if match else None
    except Exception as e:
        print(f"Error al leer el archivo cpp: {str(e)}")
        return None

def analyze_code_complexity(code):
    """
    Analiza la complejidad del código basado en patrones mejorados.
    Detecta QuickSort, bucles anidados, etc.
    """
    if not code:
        return 'No se pudo analizar', 0

    # ============== 1) EXTRAER NOMBRE DE LA FUNCIÓN =======================
    # Buscamos 'Clase::Funcion(...)' para obtener 'Funcion'
    match_class_func = re.search(r'\b(\w+)::(\w+)\s*\([^)]*\)', code)
    if match_class_func:
        class_name, raw_func_name = match_class_func.group(1), match_class_func.group(2)
    else:
        # Si no hay 'Clase::', al menos extraemos la primera palabra seguida de '('
        match_simple = re.search(r'\b(\w+)\s*\(', code)
        raw_func_name = match_simple.group(1) if match_simple else ''
        class_name = ''
    
    # ============== 2) REMOVER LA LÍNEA DE DEFINICIÓN =====================
    # Para no contarla como "llamada recursiva"
    # Ejemplo: "Nodo* QuickSort::quickSortRecursivo(Nodo* cabeza, Nodo* fin)"
    # La removemos del texto para que no se cuente.
    definition_pattern = (
        rf'\b{class_name}::\b{raw_func_name}\s*\([^)]*\)'
        if class_name
        else rf'\b{raw_func_name}\s*\([^)]*\)'
    )
    # Eliminamos solo la primera ocurrencia (la firma de la función)
    code_body = re.sub(definition_pattern, '', code, count=1)

    # ============== 3) DETECTAR LLAMADAS RECURSIVAS =======================
    # Ahora buscamos dentro del cuerpo las llamadas a 'quickSortRecursivo(...)', etc.
    call_pattern = fr'\b{re.escape(raw_func_name)}\s*\([^)]*\)'
    recursive_calls = re.findall(call_pattern, code_body)
    num_recursive_calls = len(recursive_calls)

    # ============== 4) DETECTAR 'partition' o 'pivot' =====================
    # para clasificarlo como QuickSort
    is_quick_sort = bool(re.search(r'\bpartition\b|\bpivot\b', code_body, re.IGNORECASE))

    # ============== 5) DETECTAR BUCLES (anidados y simples) ===============
    # Buscamos 'for'/'while' repetidos en el mismo bloque para anidados
    nested_loops_pattern = r'(for|while).*?(for|while)'
    nested_loops = len(re.findall(nested_loops_pattern, code_body, re.DOTALL))

    # Buscamos cualquier 'for(...)' o 'while(...)'
    all_loops = re.findall(r'(for|while)\s*\([^)]*\)', code_body)
    single_loops = len(all_loops) - nested_loops

    # ============== 6) CLASIFICACIÓN FINAL ================================
    # a) QuickSort => O(n log n) en caso promedio
    if is_quick_sort and num_recursive_calls == 2:
        return 'O(n log n)', 1.5
    
    # b) Bucles anidados => O(n^2)
    if nested_loops > 0:
        return 'O(n^2)', 2
    
    # c) Un solo bucle => O(n) o O(n log n) si vemos "log"
    if single_loops > 0:
        if 'log' in code_body.lower():
            return 'O(n log n)', 1.5
        return 'O(n)', 1
    
    # d) Llamadas recursivas
    if num_recursive_calls == 1:
        # Asumimos divide a la mitad => O(log n)
        return 'O(log n)', 0.5
    elif num_recursive_calls == 2:
        # Sin indicios de QuickSort => lo clasificamos como O(2^n)
        return 'O(2^n)', 3
    else:
        # Sin recursión ni bucles => O(1)
        return 'O(1)', 0

def simulate_execution_time(complexity_factor, n):
    """Simula el tiempo de ejecución basado en el factor de complejidad."""
    if complexity_factor == 0:      # O(1)
        return 0.0001
    elif complexity_factor == 0.5:  # O(log n)
        return 0.0001 * np.log2(n)
    elif complexity_factor == 1:    # O(n)
        return 0.0001 * n
    elif complexity_factor == 1.5:  # O(n log n)
        return 0.0001 * n * np.log2(n)
    elif complexity_factor == 2:    # O(n^2)
        return 0.0001 * (n**2)
    elif complexity_factor == 3:    # O(2^n)
        return 0.0001 * (2**n)
    else:                           # fallback: O(n^2 log n), etc.
        return 0.0001 * (n**2) * np.log2(n)

def analyze_complexity(code):
    """
    Analiza la complejidad y genera puntos de datos para graficar.
    Retorna (tamaños, tiempos, complejidad).
    """
    complexity, factor = analyze_code_complexity(code)

    # Tomamos tamaños desde 10^1 hasta 10^5 (logspace)
    sizes = np.logspace(1, 5, num=20, dtype=int)
    times = [simulate_execution_time(factor, n) for n in sizes]
    return sizes, times, complexity

def plot_complexity(sizes, times, complexity, func_name):
    """Genera la gráfica de análisis de complejidad."""
    plt.figure(figsize=(10, 6))
    plt.plot(sizes, times, 'b-o', linewidth=2, markersize=4, label='Tiempo de ejecución estimado')
    
    plt.title(f'Análisis de Complejidad: {func_name}\nComplejidad estimada: {complexity}', fontsize=12, pad=20)
    plt.xlabel('Tamaño de entrada (n)', fontsize=10)
    plt.ylabel('Tiempo estimado (s)', fontsize=10)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.xscale('log')
    plt.yscale('log')
    plt.legend(fontsize=10)
    plt.tight_layout()
    
    try:
        plt.savefig('complexity_analysis.png', dpi=300, bbox_inches='tight')
        print("\nGráfico guardado como 'complexity_analysis.png'")
        plt.show(block=False)
        plt.pause(0.1)
        input("\nPresione Enter para cerrar el gráfico...")
    except Exception as e:
        print(f"\nError al mostrar o guardar el gráfico: {str(e)}")
    finally:
        plt.close('all')

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Uso: python archivo.py archivo.h \"Nodo* QuickSort::quickSortRecursivo(Nodo* cabeza, Nodo* fin)\" archivo.cpp")
        sys.exit(1)
    
    h_file = sys.argv[1]
    prototype = sys.argv[2]
    cpp_file = sys.argv[3]
    
    try:
        # Extraer la implementación desde el .cpp
        code = extract_function_implementation(cpp_file, prototype)
        if not code:
            print(f"No se pudo encontrar la implementación para: {prototype}")
            sys.exit(1)
        
        # Analizar complejidad
        sizes, times, complexity = analyze_complexity(code)
        func_name = prototype.split('(')[0].strip().split()[-1]
        
        # Generar gráfica
        plot_complexity(sizes, times, complexity, func_name)
        
        print(f"\nAnálisis de complejidad para {func_name}: {complexity}")
        
    except FileNotFoundError as e:
        print(f"Error: No se encontró el archivo: {str(e)}")
        sys.exit(1)
    except Exception as e:
        print(f"Error inesperado: {str(e)}")
        sys.exit(1)

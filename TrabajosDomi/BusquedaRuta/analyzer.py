import sys
import re
import matplotlib.pyplot as plt
import numpy as np

def extract_loops_and_recursion(code):
    # Contadores para bucles anidados
    max_nesting = 0
    current_nesting = 0
    brackets_stack = []
    
    # Análisis línea por línea para bucles
    lines = code.split('\n')
    for line in lines:
        # Contar llaves abiertas y cerradas
        brackets_stack.extend(['{'] * line.count('{'))
        for _ in range(line.count('}')):
            if brackets_stack:
                brackets_stack.pop()
        
        # Detectar bucles considerando el contexto
        if ('for' in line or 'while' in line) and '{' in line:
            current_nesting = len(brackets_stack)
            max_nesting = max(max_nesting, current_nesting)

    # Extraer nombre de la función
    function_match = re.search(r'[\w:]+\s+([\w:]+)\s*\(', code)
    function_name = function_match.group(1) if function_match else None
    
    # Detectar recursión buscando el nombre de la función en el cuerpo
    has_recursion = False
    if function_name:
        # Remover el nombre de la clase si existe
        clean_name = function_name.split('::')[-1]
        # Buscar llamadas recursivas en el cuerpo de la función
        body_start = code.find('{')
        if body_start != -1:
            function_body = code[body_start:]
            has_recursion = clean_name in function_body
    
    return max_nesting, has_recursion

# Usar una lambda para el análisis de complejidad
complexity_analyzer = lambda code, max_nesting, has_recursion: (
    "O(n log n)" if has_recursion and "partition" in code.lower() else  # Quicksort case
    "O(2^n)" if has_recursion and max_nesting == 0 else  # Pure recursion
    "O(n log n)" if has_recursion and max_nesting == 1 else  # Recursive with loop
    f"O(n^{max_nesting})" if max_nesting > 1 else  # Nested loops
    "O(n)" if max_nesting == 1 else  # Single loop
    "O(1)"  # Constant time
)

def generate_complexity_values(complexity, n_points=10):
    x = np.linspace(1, n_points, n_points)
    if complexity == "O(n log n)":
        return x * np.log(x)
    elif complexity == "O(2^n)":
        return 2**x
    elif complexity.startswith("O(n^"):
        power = int(complexity[4])
        return x**power
    elif complexity == "O(n)":
        return x
    else:  # O(1)
        return np.ones_like(x)

def analyze_complexity(code, func_name):
    max_nesting, has_recursion = extract_loops_and_recursion(code)
    
    # Usar la lambda para determinar la complejidad
    complexity = complexity_analyzer(code, max_nesting, has_recursion)
    
    # Generar valores para el gráfico
    complexity_values = generate_complexity_values(complexity)
    
    # Crear gráfico
    plt.figure(figsize=(10, 6))
    x = np.linspace(1, 10, 10)
    plt.plot(x, complexity_values, 'b-', label=complexity)
    plt.title(f'Análisis de Complejidad: {func_name}')
    plt.xlabel('Tamaño de entrada (n)')
    plt.ylabel('Tiempo de ejecución')
    plt.grid(True)
    plt.legend()
    plt.savefig('complexity_analysis.png')
    plt.close()

    print(f"\nAnálisis de complejidad para {func_name}:")
    print(f"Nivel máximo de anidación: {max_nesting}")
    print(f"Recursión detectada: {'Sí' if has_recursion else 'No'}")
    print(f"Complejidad estimada: {complexity}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Uso: python analyzer.py <nombre_funcion> <archivo_codigo>")
        sys.exit(1)

    func_name = sys.argv[1]
    file_path = sys.argv[2]

    try:
        with open(file_path, "r") as f:
            func_code = f.read()
    except Exception as e:
        print(f"Error al leer el archivo: {e}")
        sys.exit(1)

    if not func_code.strip():
        print("Error: No se proporcionó código para analizar")
        sys.exit(1)

    print("Código recibido para analizar:")
    print(func_code)
    analyze_complexity(func_code, func_name)
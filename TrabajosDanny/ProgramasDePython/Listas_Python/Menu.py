import os
import msvcrt

class Menu:
    def __init__(self, titulo, opciones):
        """
        Inicializa el menú con un título y una lista de opciones.
        """
        self.titulo = titulo
        self.opciones = opciones
        self.seleccion = 0

    def mostrar(self):
        """
        Muestra el menú en pantalla, destacando la opción seleccionada.
        """
        os.system("cls" if os.name == "nt" else "clear")
        print(self.titulo)
        print("-" * len(self.titulo))
        for i, opcion in enumerate(self.opciones):
            if i == self.seleccion:
                print(f"> {opcion}")
            else:
                print(f"  {opcion}")

    def leer_tecla(self):
        """
        Lee una tecla y devuelve su código.
        """
        tecla = msvcrt.getch()
        if tecla == b'\xe0':  # Detectar teclas especiales
            tecla = msvcrt.getch()
        return tecla

    def ejecutar(self):
        """
        Ejecuta el menú y retorna la opción seleccionada.
        """
        while True:
            self.mostrar()
            tecla = self.leer_tecla()

            if tecla == b'H':  # Flecha hacia arriba
                self.seleccion = (self.seleccion - 1) % len(self.opciones)
            elif tecla == b'P':  # Flecha hacia abajo
                self.seleccion = (self.seleccion + 1) % len(self.opciones)
            elif tecla == b'\r':  # Enter
                return self.seleccion




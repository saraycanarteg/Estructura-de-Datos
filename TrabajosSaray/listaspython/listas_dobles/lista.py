import sys
import os

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
from nodo import Nodo
from correo import GeneradorCorreo
from persona import Persona

class Lista:
    def __init__(self):
        self.cabeza = None
        self.cola = None
        self.generador_correo = GeneradorCorreo()
        self.cedulas_registradas = set()

    def validar_cedula_duplicada(self, cedula):
        return cedula not in self.cedulas_registradas

    def insertar_por_cabeza(self, persona):
        if not self.validar_cedula_duplicada(persona.cedula):
            print(f"\nError: La cédula {persona.cedula} ya está registrada en el sistema.")
            return False
            
        nuevo = Nodo(persona)
        if not self.cabeza:
            self.cabeza = self.cola = nuevo
        else:
            nuevo.siguiente = self.cabeza
            self.cabeza.anterior = nuevo
            self.cabeza = nuevo
        
        self.cedulas_registradas.add(persona.cedula)
        return True

    def insertar_por_cola(self, persona):
        if not self.validar_cedula_duplicada(persona.cedula):
            print(f"\nError: La cédula {persona.cedula} ya está registrada en el sistema.")
            return False
            
        nuevo = Nodo(persona)
        if not self.cola:
            self.cabeza = self.cola = nuevo
        else:
            nuevo.anterior = self.cola
            self.cola.siguiente = nuevo
            self.cola = nuevo
        
        self.cedulas_registradas.add(persona.cedula)
        return True

    def eliminar_por_cedula(self, cedula):
        if not self.cabeza:
            return False

        actual = self.cabeza
        while actual:
            if actual.data.cedula == cedula:
                if actual == self.cabeza:
                    self.cabeza = actual.siguiente
                    if self.cabeza:
                        self.cabeza.anterior = None
                    else:
                        self.cola = None
                elif actual == self.cola:
                    self.cola = actual.anterior
                    self.cola.siguiente = None
                else:
                    actual.anterior.siguiente = actual.siguiente
                    actual.siguiente.anterior = actual.anterior
                
                self.cedulas_registradas.remove(cedula)
                print(f"\nPersona con cédula {cedula} eliminada exitosamente")
                return True
            actual = actual.siguiente
        
        print(f"\nNo se encontró ninguna persona con la cédula {cedula}")
        return False

    def mostrar_lista(self):
        if not self.cabeza:
            print("\nLista vacía")
            return

        actual = self.cabeza
        while actual:
            print(f"Cédula:   {actual.data.cedula}")
            print(f"Nombre:    {actual.data.nombre}")
            print(f"Apellido:  {actual.data.apellido}")
            print(f"Correo:    {actual.data.correo}")
            print("-" * 40)
            actual = actual.siguiente

    def copiar_lista(lista_origen, lista_destino):
        lista_destino.cabeza = None
        lista_destino.cola = None
        lista_destino.cedulas_registradas.clear()
        
        actual = lista_origen.cabeza
        while actual:
            nueva_persona = Persona(
                actual.data.cedula,
                actual.data.apellido,
                actual.data.nombre,
                actual.data.correo
            )
            lista_destino.insertar_por_cola(nueva_persona)
            actual = actual.siguiente

    def eliminar_caracter(self, c):
        actual = self.cabeza
        while actual:
            actual.data.cedula = actual.data.cedula.replace(c, '')
            actual.data.nombre = actual.data.nombre.replace(c, '')
            actual.data.apellido = actual.data.apellido.replace(c, '')
            actual.data.correo = self.generador_correo.generar_correo(
                actual.data.nombre, 
                actual.data.apellido
            )
            actual = actual.siguiente

    def reemplazar_caracter(self, original, reemplazo):
        actual = self.cabeza
        while actual:
            actual.data.cedula = actual.data.cedula.replace(original, reemplazo)
            actual.data.nombre = actual.data.nombre.replace(original, reemplazo)
            actual.data.apellido = actual.data.apellido.replace(original, reemplazo)
            actual.data.correo = self.generador_correo.generar_correo(
                actual.data.nombre, 
                actual.data.apellido
            )
            actual = actual.siguiente

    def buscar_por_cedula(self, cedula):
        actual = self.cabeza
        while actual:
            if actual.data.cedula == cedula:
                return actual.data
            actual = actual.siguiente
        return None
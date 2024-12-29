class Nodo:
    def __init__(self, dato):
        self.dato = dato
        self.siguiente = None

class ListaSimple:
    def __init__(self):
        self.cabeza = None

    def crear(self, dato):
        nuevo_nodo = Nodo(dato)
        if not self.cabeza:
            self.cabeza = nuevo_nodo
        else:
            actual = self.cabeza
            while actual.siguiente:
                actual = actual.siguiente
            actual.siguiente = nuevo_nodo

    def buscar(self, dato):
        actual = self.cabeza
        while actual:
            if actual.dato == dato:
                return True
            actual = actual.siguiente
        return False

    def eliminar(self, dato):
        if not self.cabeza:
            return False
        if self.cabeza.dato == dato:
            self.cabeza = self.cabeza.siguiente
            return True
        actual = self.cabeza
        while actual.siguiente:
            if actual.siguiente.dato == dato:
                actual.siguiente = actual.siguiente.siguiente
                return True
            actual = actual.siguiente
        return False

    def mostrar(self):
        elementos = []
        actual = self.cabeza
        while actual:
            print(actual.dato)
            elementos.append(actual.dato)
            actual = actual.siguiente
        return elementos

    def buscar_por_cedula(self, cedula):
        persona = []
        actual = self.cabeza
        while actual:
            if actual.dato==cedula:
                persona.append(actual.dato)
                actual = actual.siguiente
                persona.append(actual.dato)
                actual = actual.siguiente
                persona.append(actual.dato)
                return persona
            else:
                actual = actual.siguiente
                actual = actual.siguiente
                if actual.siguiente:
                    actual = actual.siguiente
                else:
                    return None

    def buscar_por_nombres(self, nombre, apellido):
        persona = []
        actual = self.cabeza
        aux = self.cabeza
        while actual:
            aux = actual
            actual = actual.siguiente

            if actual.dato == nombre:
                persona.append(aux.dato)
                persona.append(actual.dato)
                actual = actual.siguiente
                if actual.dato == apellido:
                    persona.append(actual.dato)
                    return persona
            else:
                actual = actual.siguiente
                if actual.siguiente:
                    actual = actual.siguiente
                else:
                    return None

class Persona:
    def __init__(self, cedula, apellido, nombre, correo=None):
        self._cedula = cedula
        self._apellido = apellido
        self._nombre = nombre
        self._correo = correo

    @property
    def cedula(self):
        return self._cedula

    @property
    def apellido(self):
        return self._apellido

    @property
    def nombre(self):
        return self._nombre

    @property
    def correo(self):
        return self._correo

    @cedula.setter
    def cedula(self, value):
        self._cedula = value

    @apellido.setter
    def apellido(self, value):
        self._apellido = value

    @nombre.setter
    def nombre(self, value):
        self._nombre = value

    @correo.setter
    def correo(self, value):
        self._correo = value
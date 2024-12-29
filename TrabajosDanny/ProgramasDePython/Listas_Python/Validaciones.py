class Validaciones:
    @staticmethod
    def input_numero(mensaje):
        """Solicita al usuario un número entero y valida la entrada."""
        while True:
            try:
                valor = int(input(mensaje))
                return valor
            except ValueError:
                print("Error: Debes ingresar un número válido.")

    @staticmethod
    def input_cadena(mensaje):
        """Solicita al usuario una cadena de texto sin números y valida la entrada."""
        while True:
            valor = input(mensaje)
            if valor.isalpha():
                return valor
            else:
                print("Error: Solo se permiten letras.")
    @staticmethod
    def input_cedula(mensaje):
        """Solicita al usuario una cédula válida de 10 dígitos y valida la entrada."""
        while True:
            cedula = input(mensaje)
            if cedula.isdigit() and len(cedula) == 10:
                return cedula
            else:
                print("Error: La cédula debe tener exactamente 10 dígitos numéricos.")

    @staticmethod
    def sys_pause():
        print("\nPresiones enter para continuar...")
        input()
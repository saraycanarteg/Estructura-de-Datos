class Validaciones:
    @staticmethod
    def validar_cedula(cedula):
        if not cedula or not cedula.isdigit() or len(cedula) != 10:
            return False
        
        # Validación específica para cédula ecuatoriana
        provincia = int(cedula[:2])
        if provincia < 1 or provincia > 24:
            return False
            
        # Algoritmo de validación
        coeficientes = [2, 1, 2, 1, 2, 1, 2, 1, 2]
        total = 0
        
        for i in range(9):
            valor = int(cedula[i]) * coeficientes[i]
            if valor > 9:
                valor -= 9
            total += valor
            
        verificador = 10 - (total % 10)
        if verificador == 10:
            verificador = 0
            
        return verificador == int(cedula[-1])

    @staticmethod
    def validar_texto(texto):
        return bool(texto.strip()) and all(c.isalpha() or c.isspace() for c in texto)

    @staticmethod
    def capitalizar_nombre(texto):
        return ' '.join(palabra.capitalize() for palabra in texto.split())
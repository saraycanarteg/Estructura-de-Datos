class GeneradorCorreo:
    def __init__(self):
        self.correos_usados = {}  

    def generar_correo(self, nombre, apellido):
        nombres = nombre.lower().split()
        base_correo = f"{nombres[0][0]}{nombres[1][0] if len(nombres) > 1 else ''}{apellido.lower()}"
        nombre_completo = f"{nombre.lower()} {apellido.lower()}"  

        if nombre_completo not in self.correos_usados:
            self.correos_usados[nombre_completo] = [base_correo]
            return f"{base_correo}@espe.edu.ec"
        else:
            
            correo_base = f"{base_correo}{len(self.correos_usados[nombre_completo])}@espe.edu.ec"
            self.correos_usados[nombre_completo].append(correo_base)
            return correo_base
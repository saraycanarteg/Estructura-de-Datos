import sys
import os

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
from lista import Lista
from validaciones import Validaciones
from persona import Persona
from entrada import EntradaControlada

def limpiar_pantalla():
    import os
    os.system('cls' if os.name == 'nt' else 'clear')
def main():
    lista = Lista()
    lista_modificada = Lista() 
    validador = Validaciones()
    entrada = EntradaControlada()

    while True:
        limpiar_pantalla()
        print("\n=== Sistema de Gestión de Personas ===")
        print("1. Insertar por cabeza")
        print("2. Insertar por cola")
        print("3. Mostrar lista original")
        print("4. Mostrar lista modificada")
        print("5. Eliminar caracter")
        print("6. Reemplazar caracter")
        print("7. Buscar persona")
        print("8. Eliminar persona")
        print("9. Salir")
        
        try:
            opcion = int(input("\nSeleccione una opción: "))
        except ValueError:
            input("\nOpción inválida. Presione Enter para continuar...")
            continue

        if opcion == 1 or opcion == 2:
            while True:
                limpiar_pantalla()
                print("\n============= Ingreso nueva persona ============= ")
                print("0. Regresar al menú principal")
                print("1. Ingresar persona")
                
                try:
                    sub_opcion = int(input("\nSeleccione una opción: "))
                    if sub_opcion == 0:
                        break
                    elif sub_opcion == 1:
                        cedula = entrada.input_numerico("Cédula (10 dígitos): ", 10)
                        if not validador.validar_cedula(cedula):
                            input("\nCédula inválida. Presione Enter para continuar...")
                            continue

                        apellido = entrada.input_texto("Apellido: ")
                        if not validador.validar_texto(apellido):
                            input("\nApellido inválido. Presione Enter para continuar...")
                            continue
                        apellido = validador.capitalizar_nombre(apellido)

                        nombre = entrada.input_texto("Nombres: ")
                        if not validador.validar_texto(nombre):
                            input("\nNombre inválido. Presione Enter para continuar...")
                            continue
                        nombre = validador.capitalizar_nombre(nombre)

                        correo = lista.generador_correo.generar_correo(nombre, apellido)
                        persona = Persona(cedula, apellido, nombre, correo)
                        print("\n========================================")
                        exito = lista.insertar_por_cabeza(persona) if opcion == 1 else lista.insertar_por_cola(persona)
                        if exito:
                            print("\nPersona registrada exitosamente")
                        input("\nPresione Enter para continuar...")
                        break
                except ValueError:
                    input("\nOpción inválida. Presione Enter para continuar...")

        elif opcion == 3:
            while True:
                limpiar_pantalla()
                print("\n============= Listado de Personas Original ============= ")

                print("\nInformación de las Personas:")
                lista.mostrar_lista()
                input("\nPresione Enter para continuar...")
                break

        elif opcion == 4:
            while True:
                limpiar_pantalla()
                print("\n============= Listado de Personas Modificada ============= ")

                print("\nInformación de las Personas:")
                lista_modificada.mostrar_lista()
                input("\nPresione Enter para continuar...")
                break

        elif opcion == 5:
            while True:
                limpiar_pantalla()
                print("\n============= Eliminar Caracter ============= ")
                print("0. Regresar al menú principal")
                print("1. Eliminar caracter")
                
                try:
                    sub_opcion = int(input("\nSeleccione una opción: "))
                    if sub_opcion == 0:
                        break
                    elif sub_opcion == 1:
                        caracter = input("\nIngrese el caracter a eliminar: ")
                        if len(caracter) != 1:
                            print("\nDebe ingresar un solo caracter")
                            input("\nPresione Enter para continuar...")
                            continue

                        lista_modificada = Lista()
                        Lista.copiar_lista(lista, lista_modificada)
                        lista_modificada.eliminar_caracter(caracter)
                        print("\nCaracter eliminado en la lista modificada")
                        input("\nPresione Enter para continuar...")
                        break
                except ValueError:
                    input("\nOpción inválida. Presione Enter para continuar...")

        elif opcion == 6:
            while True:
                limpiar_pantalla()
                print("\n============= Reemplazar Caracter ============= ")
                print("0. Regresar al menú principal")
                print("1. Reemplazar caracter")
                
                try:
                    sub_opcion = int(input("\nSeleccione una opción: "))
                    if sub_opcion == 0:
                        break
                    elif sub_opcion == 1:
                        original = input("\nIngrese el caracter a reemplazar: ")
                        if len(original) != 1:
                            print("\nDebe ingresar un solo caracter")
                            input("\nPresione Enter para continuar...")
                            continue

                        reemplazo = input("Ingrese el caracter por el cual reemplazar: ")
                        if len(reemplazo) != 1:
                            print("\nDebe ingresar un solo caracter")
                            input("\nPresione Enter para continuar...")
                            continue

                        lista_modificada = Lista()
                        Lista.copiar_lista(lista, lista_modificada)
                        lista_modificada.reemplazar_caracter(original, reemplazo)
                        print("\nCaracter reemplazado en la lista modificada")
                        input("\nPresione Enter para continuar...")
                        break
                except ValueError:
                    input("\nOpción inválida. Presione Enter para continuar...")

        elif opcion == 7:
            while True:
                limpiar_pantalla()
                print("\n============= Buscar Persona ============= ")
                print("0. Regresar al menú principal")
                print("1. Buscar persona")
                
                try:
                    sub_opcion = int(input("\nSeleccione una opción: "))
                    if sub_opcion == 0:
                        break
                    elif sub_opcion == 1:
                        cedula = entrada.input_numerico("\nIngrese la cédula a buscar (10 dígitos): ", 10)
                        if validador.validar_cedula(cedula):
                            persona = lista.buscar_por_cedula(cedula)
                            if persona:
                                print("\nPersona encontrada:")
                                print(f"Cédula:   {persona.cedula}")
                                print(f"Nombre:    {persona.nombre}")
                                print(f"Apellido:  {persona.apellido}")
                                print(f"Correo:    {persona.correo}")
                            else:
                                print("\nPersona no encontrada")
                        else:
                            print("\nCédula inválida")
                        input("\nPresione Enter para continuar...")
                        break
                except ValueError:
                    input("\nOpción inválida. Presione Enter para continuar...")

        elif opcion == 8:
            while True:
                limpiar_pantalla()
                print("\n============= Eliminar Persona ============= ")
                print("0. Regresar al menú principal")
                print("1. Eliminar persona")
                
                try:
                    sub_opcion = int(input("\nSeleccione una opción: "))
                    if sub_opcion == 0:
                        break
                    elif sub_opcion == 1:
                        cedula = entrada.input_numerico("\nIngrese la cédula de la persona a eliminar (10 dígitos): ", 10)
                        if validador.validar_cedula(cedula):
                            lista.eliminar_por_cedula(cedula)
                        else:
                            print("\nCédula inválida")
                        input("\nPresione Enter para continuar...")
                        break
                except ValueError:
                    input("\nOpción inválida. Presione Enter para continuar...")

        elif opcion == 9:
            print("\nSaliendo del programa...")
            break

if __name__ == "__main__":
    main()
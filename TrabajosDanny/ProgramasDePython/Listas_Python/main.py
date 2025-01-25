"""Manejo de listas en python"""
from ListaSimple import ListaSimple
from ListaDoble import ListaDoble
from ListaCircular import ListaCircular
from Menu import Menu
from Validaciones import Validaciones

if __name__ == "__main__":    
    lista_simple = ListaSimple()
    lista_simple_modificada = ListaSimple()
    lista_doble = ListaDoble()
    lista_doble_modificada = ListaDoble()
    lista_circular = ListaCircular()
    lista_circular_modificada = ListaCircular()
    persona = []
    
    opciones = ["1. Crear", "2. Buscar", "3. Eliminar", "4. Mostrar", "5. Regresar"]
    op_busqueda = ["1. Por cédula", "2. Por nombre y apellido", "3. Regresar"]

    while True:
        menu = Menu("MANEJO DE LISTAS EN PYTHON", ["1. Lista Simple", "2. Lista Doble", "3. Lista Circular", "4. Salir"])
        seleccion = menu.ejecutar()
        if seleccion == 0:  # Lista Simple
            submenu = Menu("LISTA SIMPLE", opciones)
            print()
            while True:
                opcion = submenu.ejecutar()
                if opcion == 0:  # Crear
                    cedula = Validaciones.input_cedula("\nIngresa la cédula (10 dígitos): ")
                    nombre = Validaciones.input_cadena("Ingresa el nombre: ")
                    apellido = Validaciones.input_cadena("Ingresa el apellido: ")
                    correo = (nombre[0].lower()+nombre[1].lower())+(apellido.lower())+"@espe.edu.ec"
                    if not(lista_simple.buscar(cedula)):
                        lista_simple.crear(cedula)
                        lista_simple.crear(nombre.title())
                        lista_simple.crear(apellido.title())
                        lista_simple.crear(correo)
                        lista_simple_modificada.crear(cedula)
                        lista_simple_modificada.crear(nombre.title())
                        lista_simple_modificada.crear(apellido.title())
                        lista_simple_modificada.crear(correo)
                        print("Elemento añadido.")
                    else:
                        print("Elemento ya existente. Intente de nuevo...")
                    print("\nCorreo generado: ", correo)
                    Validaciones.sys_pause()
                elif opcion == 1:  # Buscar
                    sub_buscar = Menu("BUSCAR EN LISTA SIMPLE", op_busqueda)
                    print()
                    while True:
                        opcion_buscar = sub_buscar.ejecutar()
                        if opcion_buscar == 0:  # Por cédula
                            cedula = Validaciones.input_cedula("Ingresa la cédula a buscar: ")
                            persona = lista_simple.buscar_por_cedula(cedula)
                            print(persona if persona else "No encontrado.")
                            Validaciones.sys_pause()
                        elif opcion_buscar == 1:  # Por nombre y apellido
                            nombre = Validaciones.input_cadena("Ingresa el nombre: ")
                            apellido = Validaciones.input_cadena("Ingresa el apellido: ")
                            persona = lista_simple.buscar_por_nombres(nombre.title(), apellido.title())
                            print(persona if persona else "No encontrado.")
                            Validaciones.sys_pause()
                        elif opcion_buscar == 2:  # Regresar
                            break
                elif opcion == 2:  # Eliminar
                    
                    dato = Validaciones.input_cedula("Ingresa la cédula para eliminar: ")
                    persona = lista_simple_modificada.buscar_por_cedula(dato)
                    if persona:
                        lista_simple_modificada.eliminar(persona[0])
                        lista_simple_modificada.eliminar(persona[1].title())
                        lista_simple_modificada.eliminar(persona[2].title())
                        lista_simple_modificada.eliminar(persona[3])
                        print("\nLista original:\n", lista_simple.mostrar(), "\nLista modificada:")
                    print(lista_simple_modificada.mostrar() if persona else "Elemento no encontrado.")
                    Validaciones.sys_pause()
                elif opcion == 3:  # Mostrar
                    print("Lista: ", lista_simple.mostrar())
                    print("Lista modificada: ", lista_simple_modificada.mostrar())
                    Validaciones.sys_pause()
                elif opcion == 4:  # Regresar
                    break

        elif seleccion == 1:  # Lista Doble
            submenu = Menu("LISTA DOBLE", opciones)
            print()
            while True:
                opcion = submenu.ejecutar()
                if opcion == 0:  # Crear
                    cedula = Validaciones.input_cedula("Ingresa la cédula (10 dígitos): ")
                    nombre = Validaciones.input_cadena("Ingresa el nombre: ")
                    apellido = Validaciones.input_cadena("Ingresa el apellido: ")
                    correo = (nombre[0].lower()+nombre[1].lower())+(apellido.lower())+"@espe.edu.ec"
                    if not(lista_doble.buscar(cedula)):
                        lista_doble.crear(cedula)
                        lista_doble.crear(nombre.title())
                        lista_doble.crear(apellido.title())
                        lista_doble.crear(correo)
                        lista_doble_modificada.crear(cedula)
                        lista_doble_modificada.crear(nombre.title())
                        lista_doble_modificada.crear(apellido.title())
                        lista_doble_modificada.crear(correo)
                        print("Elemento añadido.")
                    else: 
                        print("Elemento ya existente. Intente de nuevo...")
                    print("\nCorreo generado: ", correo)
                    Validaciones.sys_pause()
                elif opcion == 1:  # Buscar
                    sub_buscar = Menu("BUSCAR EN LISTA DOBLE", op_busqueda)
                    while True:
                        opcion_buscar = sub_buscar.ejecutar()
                        if opcion_buscar == 0:  # Por cédula
                            cedula = Validaciones.input_cedula("Ingresa la cédula a buscar: ")
                            persona = lista_doble.buscar_por_cedula(cedula)
                            print(persona if persona else "No encontrado.")
                            Validaciones.sys_pause()
                        elif opcion_buscar == 1:  # Por nombre y apellido
                            nombre = Validaciones.input_cadena("Ingresa el nombre: ")
                            apellido = Validaciones.input_cadena("Ingresa el apellido: ")
                            persona = lista_doble.buscar_por_nombres(nombre.title(), apellido.title())
                            print(persona if persona else "No encontrado.")
                            Validaciones.sys_pause()
                        elif opcion_buscar == 2:  # Regresar
                            break
                        
                elif opcion == 2:  # Eliminar
                    dato = Validaciones.input_cedula("Ingresa la cédula para eliminar: ")
                    persona = lista_doble_modificada.buscar_por_cedula(dato)
                    lista_doble_modificada.eliminar(persona[0])
                    lista_doble_modificada.eliminar(persona[1].title())
                    lista_doble_modificada.eliminar(persona[2].title())
                    lista_doble_modificada.eliminar(persona[3])
                    print("\nLista original:\n", lista_doble.mostrar(), "\nLista modificada:\n")
                    print(lista_doble_modificada.mostrar() if persona else "Elemento no encontrado.")
                    Validaciones.sys_pause()
                elif opcion == 3:  # Mostrar
                    print("Lista: ", lista_doble.mostrar())
                    print("Lista modificada: ", lista_doble_modificada.mostrar())
                    Validaciones.sys_pause()
                elif opcion == 4:  # Regresar
                    break

        elif seleccion == 2:  # Lista Circular
            submenu = Menu("LISTA CIRCULAR", opciones)
            print()
            while True:
                opcion = submenu.ejecutar()
                if opcion == 0:  # Crear
                    cedula = Validaciones.input_cedula("Ingresa la cédula (10 dígitos): ")
                    nombre = Validaciones.input_cadena("Ingresa el nombre: ")
                    apellido = Validaciones.input_cadena("Ingresa el apellido: ")
                    correo = (nombre[0].lower()+nombre[1].lower())+(apellido.lower())+"@espe.edu.ec"

                    if not (lista_circular.buscar(cedula)):
                        lista_circular.crear(cedula)
                        lista_circular.crear(nombre.title())
                        lista_circular.crear(apellido.title())
                        lista_circular.crear(correo)
                        lista_circular_modificada.crear(cedula)
                        lista_circular_modificada.crear(nombre.title())
                        lista_circular_modificada.crear(apellido.title())
                        lista_circular_modificada.crear(correo)
                        print("Elemento añadido.")
                    else:
                        print("Elemento ya existente. Intente de nuevo...")
                    print("\nCorrego generado: ", correo)
                    Validaciones.sys_pause()
                elif opcion == 1:  # Buscar
                    sub_buscar = Menu("BUSCAR EN LISTA CIRCULAR", op_busqueda)
                    while True:
                        opcion_buscar = sub_buscar.ejecutar()
                        if opcion_buscar == 0:  # Por cédula
                            cedula = Validaciones.input_cedula("Ingresa la cédula a buscar: ")
                            persona = lista_circular.buscar_por_cedula(cedula)
                            print(persona if persona else "No encontrado.")
                            Validaciones.sys_pause()
                        elif opcion_buscar == 1:  # Por nombre y apellido
                            nombre = Validaciones.input_cadena("Ingresa el nombre: ")
                            apellido = Validaciones.input_cadena("Ingresa el apellido: ")
                            persona = lista_circular.buscar_por_nombres(nombre.title(), apellido.title())
                            print(persona if persona else "No encontrado.")
                        elif opcion_buscar == 2:  # Regresar
                            break
                elif opcion == 2:  # Eliminar
                    dato = Validaciones.input_cedula("Ingresa la cédula para eliminar: ")
                    persona = lista_circular_modificada.buscar_por_cedula(dato)
                    if persona:
                        lista_circular_modificada.eliminar(persona[0])
                        lista_circular_modificada.eliminar(persona[1].title())
                        lista_circular_modificada.eliminar(persona[2].title())
                        lista_circular_modificada.eliminar(persona[3])
                        print("Lista original:\n", lista_circular, "\nLista modificada:\n")

                    print(lista_circular_modificada.mostrar() if persona else "Elemento no encontrado.")
                    Validaciones.sys_pause()
                elif opcion == 3:  # Mostrar
                    print("\nLista: ", lista_circular.mostrar())
                    print("Lista modificada: ", lista_circular_modificada.mostrar())
                    Validaciones.sys_pause()
                elif opcion == 4:  # Regresar
                    break
        else:
            break

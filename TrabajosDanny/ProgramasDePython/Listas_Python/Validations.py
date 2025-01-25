# validation.py
import msvcrt
import time
from datetime import datetime
from typing import TypeVar, Generic, Union

T = TypeVar('T')

class Validation():
    def __init__(self):
        pass

    def enter_a_number(self, data_type: str) -> Union[int, float]:
        cad = []
        validation_decimal = False
        
        while True:
            c = msvcrt.getch().decode('utf-8')
            
            if c == '\r':
                break
                
            if c.isdigit():
                print(c, end='', flush=True)
                cad.append(c)
            elif c == '.' and not validation_decimal and data_type == "float":
                print(c, end='', flush=True)
                cad.append(c)
                validation_decimal = True
            elif c == '\b' and cad:
                print('\b \b', end='', flush=True)
                if cad.pop() == '.':
                    validation_decimal = False

        return self.data_conversion_to_number(''.join(cad), data_type)

    def enter_a_char_or_string(self, data_size: int) -> str:
        cad = []
        
        while True:
            c = msvcrt.getch().decode('utf-8')
            
            if c == '\r':
                break
                
            if c.isalpha() or c == ' ':
                print(c, end='', flush=True)
                cad.append(c)
            elif c == '\b' and cad:
                print('\b \b', end='', flush=True)
                cad.pop()
                
        return ''.join(cad)

    def enter_a_char_or_string_only_nums(self, data_size: int) -> str:
        cad = []
        
        while True:
            c = msvcrt.getch().decode('utf-8')
            
            if c == '\r':
                break
                
            if c.isdigit():
                print(c, end='', flush=True)
                cad.append(c)
            elif c == '\b' and cad:
                print('\b \b', end='', flush=True)
                cad.pop()
                
        return ''.join(cad)

    def enter_a_char_or_string_with_may_and_nums(self, data_size: int) -> str:
        cad = []
        
        while True:
            c = msvcrt.getch().decode('utf-8')
            
            if c == '\r':
                break
                
            if c.isalnum():
                if c.islower() and (not cad or cad[-1] == ' '):
                    c = c.upper()
                elif c.isupper() and cad and cad[-1] != ' ':
                    c = c.lower()
                print(c, end='', flush=True)
                cad.append(c)
            elif c == ' ':
                print(c, end='', flush=True)
                cad.append(c)
            elif c == '\b' and cad:
                print('\b \b', end='', flush=True)
                cad.pop()
                
        return ''.join(cad)

    def enter_a_char_or_string_with_may(self, data_size: int) -> str:
        cad = []
        
        while True:
            c = msvcrt.getch().decode('utf-8')
            
            if c == '\r':
                break
                
            if c.isalpha():
                if c.islower() and (not cad or cad[-1] == ' '):
                    c = c.upper()
                elif c.isupper() and cad and cad[-1] != ' ':
                    c = c.lower()
                print(c, end='', flush=True)
                cad.append(c)
            elif c == ' ':
                print(c, end='', flush=True)
                cad.append(c)
            elif c == '\b' and cad:
                print('\b \b', end='', flush=True)
                cad.pop()
                
        return ''.join(cad)

    def data_conversion_to_number(self, value: str, data_type: str) -> Union[int, float]:
        if data_type == "int":
            return int(value)
        elif data_type == "float":
            return float(value)
        return 0

    def validation_backup(self) -> str:
        cad = []
        
        while True:
            c = msvcrt.getch().decode('utf-8')
            
            if c == '\r':
                break
                
            if c.isdigit() or c == '.':
                print(c, end='', flush=True)
                cad.append(c)
            elif c == '\b' and cad:
                print('\b \b', end='', flush=True)
                cad.pop()
                
        return ''.join(cad)

    def validar_id_autor(self, id_autor: str) -> bool:
        if len(id_autor) != 4 or id_autor[0] != 'A':
            return False
        try:
            numeric_part = int(id_autor[1:])
            return numeric_part < 999
        except ValueError:
            return False

    def validate_isbn(self, isbn: str) -> bool:
        length = len(isbn)

        if length == 10:
            if not isbn[:9].isdigit():
                return False
            sum = 0
            for i in range(9):
                sum += int(isbn[i]) * (10 - i)
            last_char = isbn[9]
            if last_char != 'X' and not last_char.isdigit():
                return False
            sum += 10 if last_char == 'X' else int(last_char)
            return sum % 11 == 0

        elif length == 13:
            if not isbn.isdigit():
                return False
            sum = 0
            for i in range(13):
                digit = int(isbn[i])
                sum += digit if i % 2 == 0 else digit * 3
            return sum % 10 == 0

        return False

    def enter_date(self) -> str:
        print("\nIngrese la fecha (DD MM AAAA): ", end='', flush=True)
        cad = []
        esperando_espacio = False
        
        while True:
            c = msvcrt.getch().decode('utf-8')
            
            if c == '\r':
                break
                
            if c == '\b' and cad:
                print('\b \b', end='', flush=True)
                cad.pop()
                esperando_espacio = False
                continue
                
            if len(cad) < 10 and (c.isdigit() or c == ' '):
                if c == ' ' and (len(cad) == 2 or len(cad) == 5) and not esperando_espacio:
                    print(c, end='', flush=True)
                    cad.append(c)
                    esperando_espacio = True
                elif c.isdigit() and (not esperando_espacio or 
                                    (len(cad) > 2 and len(cad) < 5) or 
                                    (len(cad) > 5 and len(cad) < 10)):
                    print(c, end='', flush=True)
                    cad.append(c)
                    esperando_espacio = False

        fecha = ''.join(cad)
        if not self.validarFecha(fecha):
            print("\nFecha invalida. Intente de nuevo.")
            return self.enter_date()
        
        return fecha

    def validarFecha(self, fecha_str: str) -> bool:
        if len(fecha_str) != 10 or fecha_str[2] != ' ' or fecha_str[5] != ' ':
            return False

        try:
            dia = int(fecha_str[:2])
            mes = int(fecha_str[3:5])
            anio = int(fecha_str[6:])
        except ValueError:
            return False

        if dia < 1 or dia > 31 or mes < 1 or mes > 12 or anio < 1500 or anio > 9999:
            return False

        dias_en_mes = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        
        if mes == 2:
            dias_febrero = 29 if (anio % 4 == 0 and (anio % 100 != 0 or anio % 400 == 0)) else 28
            if dia > dias_febrero:
                return False
        elif dia > dias_en_mes[mes]:
            return False

        return not self.esFechaPosterior(dia, mes, anio)

    def esFechaPosterior(self, dia: int, mes: int, anio: int) -> bool:
        fecha_actual = datetime.now()
        
        if anio > fecha_actual.year:
            return True
        if anio < fecha_actual.year:
            return False
            
        if mes > fecha_actual.month:
            return True
        if mes < fecha_actual.month:
            return False
            
        return dia > fecha_actual.day

if __name__ == "__main__":   
    validation = Validation()
    print(validation)
    number = validation.enter_a_number("float")
    print(number)
    text = validation.enter_a_char_or_string(20)
    print(text)
    date = validation.enter_date()
    print(date)
import os
import sys

try:
    import msvcrt  # Para Windows
except ImportError:
    import termios  # Para Unix
    import tty

class EntradaControlada:
    @staticmethod
    def input_numerico(prompt, longitud):
        print(prompt, end='', flush=True)
        entrada = ''
        
        if sys.platform.startswith('win'):
            while True:
                if msvcrt.kbhit():
                    char = msvcrt.getwch()
                    if char == '\r':  # Enter
                        if len(entrada) == longitud:
                            print()
                            return entrada
                        continue
                    elif char == '\b':  # Backspace
                        if entrada:
                            entrada = entrada[:-1]
                            print('\b \b', end='', flush=True)
                    elif char.isdigit() and len(entrada) < longitud:
                        entrada += char
                        print(char, end='', flush=True)
        else:
            old_settings = termios.tcgetattr(sys.stdin)
            try:
                tty.setraw(sys.stdin.fileno())
                while True:
                    char = sys.stdin.read(1)
                    if char == '\r':  # Enter
                        if len(entrada) == longitud:
                            print()
                            return entrada
                        continue
                    elif char == '\x7f':  # Backspace
                        if entrada:
                            entrada = entrada[:-1]
                            print('\b \b', end='', flush=True)
                    elif char.isdigit() and len(entrada) < longitud:
                        entrada += char
                        print(char, end='', flush=True)
            finally:
                termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_settings)

    @staticmethod
    def input_texto(prompt):
        print(prompt, end='', flush=True)
        entrada = ''
        
        if sys.platform.startswith('win'):
            while True:
                if msvcrt.kbhit():
                    char = msvcrt.getwch()
                    if char == '\r':  # Enter
                        if entrada.strip():  # Verificar que no esté vacío
                            print()
                            return entrada
                        continue
                    elif char == '\b':  # Backspace
                        if entrada:
                            entrada = entrada[:-1]
                            print('\b \b', end='', flush=True)
                    elif char.isalpha() or char.isspace():
                        entrada += char
                        print(char, end='', flush=True)
        else:
            old_settings = termios.tcgetattr(sys.stdin)
            try:
                tty.setraw(sys.stdin.fileno())
                while True:
                    char = sys.stdin.read(1)
                    if char == '\r':  # Enter
                        if entrada.strip():  # Verificar que no esté vacío
                            print()
                            return entrada
                        continue
                    elif char == '\x7f':  # Backspace
                        if entrada:
                            entrada = entrada[:-1]
                            print('\b \b', end='', flush=True)
                    elif char.isalpha() or char.isspace():
                        entrada += char
                        print(char, end='', flush=True)
            finally:
                termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_settings)

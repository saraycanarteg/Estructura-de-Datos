#ifndef MY_DLL_H
#define MY_DLL_H

// Exportar las funciones usando macros para compatibilidad multiplataforma
#ifdef _WIN32
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT
#endif

extern "C" {
    DLL_EXPORT void set_value(int new_value);
    DLL_EXPORT int get_value();
}

#endif // MY_DLL_H

#include <iostream>
#include <conio.h>

using namespace std;

template<typename T>
class Validation
{
private:
    T data;
public:
    Validation();
    
    T enter_a_number(char *data_type);
    T enter_a_char_or_string(char *data_type);
    T data_convertion_to_number(char cad[], char *data_type);
    T data_convertion_to_string(char cad[], char *data_type);
};



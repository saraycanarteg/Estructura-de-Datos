#include <iostream>
#include <conio.h>
#include <ctime> 
#include <cstring>
#include <cstdlib> 

using namespace std;

template<typename T>
class Validation
{
private:
    T data;
public:
    Validation();
    
    T enter_a_number(char *data_type);
    T enter_a_char_or_string_with_may(int data_size);
    T enter_a_char_or_string(int data_size);
    T data_convertion_to_number(char *cad, char *data_type);
    T primera_letra_a_mayuscula();
    bool validate_isbn(const string &isbn);
};



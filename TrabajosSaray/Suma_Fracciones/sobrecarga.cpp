#include <iostream>
#include <limits> 
using namespace std;

int suma(int a, int b){
    return a+b;
}
float suma(float a, float b){
    return a+b;
}

int main() {

    int a = 2;

    //cout << suma(3, 7) << endl;         
    //cout << suma(3.987f, 1.545f) << endl;  
    //printf("%d", suma(3, 7));
    //printf("%f", suma(3.654, 1.545));

//Sobrecarga de operadores 

    printf("%d", a << +3);
    return 0;
}

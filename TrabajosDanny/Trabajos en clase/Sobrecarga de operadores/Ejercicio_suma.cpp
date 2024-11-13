#include <conio.h>
#include <iostream>

using namespace std;

int suma(int a, int b);
float suma(float a, float b);

int main(){

    int a = 2;
    cout<<a<<endl;

    printf("%d", a <<+2);

    return 1;
}

int suma(int a, int b){
    return a+b;
}
float suma(int a, float b){
    return a+b;
}

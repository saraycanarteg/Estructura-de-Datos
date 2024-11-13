#include <iostream>
using namespace std;

bool isEven(int n);
bool isOdd(int n);

bool isEven(int n) {
    if (n == 0)
        return true;
    else
        return isOdd(n - 1);
}

bool isOdd(int n) {
    if (n == 0)
        return false;
    else
        return isEven(n - 1);
}

int main() {
    cout << "6 es par? " << (isEven(6) ? "Si" : "No") << endl;
    return 0;
}

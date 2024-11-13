#include <iostream>
using namespace std;

int nestedRecursion(int n) {
    if (n > 100)
        return n - 10;
    else
        return nestedRecursion(nestedRecursion(n + 11));
}

int main() {
    cout << "Resultado de nestedRecursion(95): " << nestedRecursion(95) << endl;
    return 0;
}

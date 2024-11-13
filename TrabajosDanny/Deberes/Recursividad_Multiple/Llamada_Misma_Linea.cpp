#include <iostream>
using namespace std;

int multipleRecursion(int n) {
    if (n <= 1)
        return n;
    return multipleRecursion(n - 1) + multipleRecursion(n - 2);
}

int main() {
    cout << "Fibonacci de 5: " << multipleRecursion(5) << endl;
    return 0;
}

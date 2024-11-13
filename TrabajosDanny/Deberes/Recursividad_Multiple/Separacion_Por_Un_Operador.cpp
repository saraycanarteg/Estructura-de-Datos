#include <iostream>
using namespace std;

int multipleRecursionWithOperator(int n) {
    if (n <= 1)
        return n;
    int a = multipleRecursionWithOperator(n - 1);
    cout<<n<<": n"<<endl;
    cout<<a<<": a"<<endl;
    int b = multipleRecursionWithOperator(n - 2);
    cout<<b<<": b"<<endl;
    return a + b;
}

int main() {
    cout << "Fibonacci de 5: " << multipleRecursionWithOperator(5) << endl;
    return 0;
}

#include <iostream>

using namespace std;

int nonTailFactorial(int n) {
    if (n <= 1)
        return 1;
    int temp = nonTailFactorial(n - 1);
    cout<<temp<<endl<<endl;
    return n * temp;
}

int main() {
    cout << "Factorial de 5: " << nonTailFactorial(5) << endl;
    return 0;
}

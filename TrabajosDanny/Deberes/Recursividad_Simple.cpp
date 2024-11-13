#include <iostream>
using namespace std;

int factorial(int n) {
    cout<<n<<endl<<endl;
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
    cout << "Factorial de 5: " << factorial(5) << endl;
    return 0;
}

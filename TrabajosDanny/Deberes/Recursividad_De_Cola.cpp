#include <iostream>
using namespace std;

int tailFactorial(int n, int result = 1) {
    cout<<result<<endl<<endl;
    if (n <= 1)
        return result;
    return tailFactorial(n - 1, n * result);
}

int main() {
    cout << "Factorial de 5: " << tailFactorial(5) << endl;
    return 0;
}

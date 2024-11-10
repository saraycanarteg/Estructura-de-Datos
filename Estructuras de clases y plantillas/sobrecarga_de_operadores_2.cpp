#include <iostream>
using namespace std;

class Vector2D {
private:
    float x, y;
public:
    Vector2D(float x = 0, float y = 0) : x(x), y(y) {}

    // Sobrecarga del operador +
    Vector2D operator+(const Vector2D& otro) const {
        return Vector2D(this->x + otro.x, this->y + otro.y);
    }

    // Sobrecarga del operador +=
    Vector2D& operator+=(const Vector2D& otro) {
        *this = *this + otro; // Reutilizamos el operador +
        return *this;
    }

    void mostrar() const {
        cout << "Vector(" << x << ", " << y << ")" << endl;
    }
};

int main() {
    Vector2D v1(1.0, 2.0);
    Vector2D v2(3.0, 4.0);
    
    // Usando el operador +
    Vector2D v3 = v1 + v2;
    v3.mostrar(); // Vector(4.0, 6.0)

    // Usando el operador +=
    v1 += v2;
    v1.mostrar(); // Vector(4.0, 6.0)

    return 0;
}

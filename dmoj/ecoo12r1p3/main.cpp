#include <iostream>
#include <cmath>

class Vector {
public:
    double x, y;

    Vector(double x, double y) {
        this->x = x;
        this->y = y;
    }
};

Vector rotate(Vector v, double theta) {
    double x = v.x * cos(theta) - v.y * sin(theta);
    double y = v.x * sin(theta) + v.y * cos(theta);

    return {x, y};
}

Vector add(Vector a, Vector b) {
    return {a.x + b.x, a.y + b.y};
}

double rnd(double d) {
    return round(d * 10) / 10;
}

int main() {
    for (int i = 0; i < 5; i++) {
        double x, y;
        scanf("%lf%lf", &x, &y);

        Vector P(x, y);
        double delta = (M_PI / 3) - atan2(y, x);
        Vector pivot(hypot(x, y), 0);

        Vector p1 = rotate(pivot, M_PI - delta);
        Vector p2 = rotate(pivot, -delta);
        Vector p3 = add(rotate(pivot, (M_PI / 3 * 2) - delta), P);

        printf("(%.1lf,%.1lf) (%.1lf,%.1lf) (%.1lf,%.1lf)\n", rnd(p1.x), rnd(p1.y), rnd(p2.x), rnd(p2.y), rnd(p3.x), rnd(p3.y));
    }
    return 0;
}
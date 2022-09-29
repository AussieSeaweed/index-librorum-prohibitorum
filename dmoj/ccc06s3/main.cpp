#include <iostream>
#include <vector>

class Point {
public:
    int x, y;
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

int collinear(Point a, Point b, Point c) {
    int ab = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    int bc = (b.x - c.x) * (b.x - c.x) + (b.y - c.y) * (b.y - c.y);
    int ac = 1;

    return ab + bc == ac;
}

int orientation(Point a, Point b, Point c) {
    int val = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (val < 0)
        return -1;
    else if (val > 0)
        return 1;
    else
        return 0;
}

bool intersect(Point a, Point b, Point c, Point d) {
    int o1 = orientation(a,b,c);
    int o2 = orientation(a,b,d);
    int o3 = orientation(c,d,a);
    int o4 = orientation(c,d,b);

    if (o1 != o2 && o3 != o4) {
        return true;
    }

    if (!o1 && collinear(a,c,b))
        return true;
    if (!o2 && collinear(a,d,b))
        return true;
    if (!o3 && collinear(c,a,d))
        return true;
    if (!o4 && collinear(c,b,d))
        return true;

    return false;
}

std::vector<Point> vertices(33, {0,0});
int x1, y1, x2, y2;
int N;

int main() {
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    scanf("%d", &N);
    Point p1(x1, y1);
    Point p2(x2, y2);

    int count = 0;

    for (int i = 0; i < N; i++) {
        int n;
        scanf("%d", &n);
        int x, y;
        for (int j = 0; j < n; j++) {
            scanf("%d%d", &x, &y);
            vertices[j] = Point(x, y);
        }
        vertices[n] = vertices[0];

        for (int j = 0; j < n; j++) {
            if (intersect(p1, p2, vertices[j], vertices[j+1])) {
                count++;
                break;
            }
        }
    }

    printf("%d\n", count);
}
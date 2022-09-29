#include <bits/stdc++.h>

class Point {
public:
    double x, y;

    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
};

double dist(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}


bool collinear(Point a, Point b, Point c) {
    double o = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return o == 0;
}

bool isOrdered(Point a, Point b, Point c) {
    return dist(a, b) + dist(b, c) == dist(a, c);
}

int main() {
    for (int _ = 0; _ < 5; _++) {
        int N;
        scanf("%d", &N);

        std::vector<Point> pts;

        for (int i = 0; i < N; i++) {
            double x, y;
            scanf("%lf%lf", &x, &y);
            pts.emplace_back(x, y);
        }

        double x, y;
        scanf("%lf%lf", &x, &y);
        Point c(x, y);

        double min = INFINITY;
        for (int i = 0; i < N - 1; i++) {
            Point a = pts[i];
            Point b = pts[i + 1];

            if (collinear(a, b, c)) {
                if (isOrdered(a, c, b)) {
                    min = 0;
                } else {
                    min = std::min(min, std::min(dist(a, c), dist(b, c)));
                }
                continue;
            }

            double side_a = dist(b, c);
            double side_b = dist(a, c);
            double side_c = dist(a, b);
            double angle_A = acos((pow(side_b, 2) + pow(side_c, 2) - pow(side_a, 2)) / (2 * side_b * side_c));
            double angle_B = acos((pow(side_a, 2) + pow(side_c, 2) - pow(side_b, 2)) / (2 * side_a * side_c));

            if (angle_A >= M_PI_2) {
                min = std::min(min, side_b);
            } else if (angle_B >= M_PI_2) {
                min = std::min(min, side_a);
            } else {
                min = std::min(min, std::min(side_b * sin(angle_A), side_a * sin(angle_B)));
            }
        }

        if (N == 1) {
            min = dist(pts[0], c);
        }

        double ans = round(min * 100) / 100;
        printf("%.2lf\n", ans);
    }

    return 0;
}
#include <bits/stdc++.h>

class Point {
public:
    double x, y; int i;

    Point(double x, double y, int i) {
        this->x = x;
        this->y = y;
        this->i = i;
    }

    bool operator < (Point pt) const {
        if (y == pt.y) {
            return x < pt.x;
        } else {
            return y < pt.y;
        }
    }
};

double dist(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;

    return sqrt(dx * dx + dy * dy);
}

int orientation(Point a, Point b, Point c) {
    double o = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);

    if (o > 0) {
        return 1;
    } else if (o < 0) {
        return -1;
    } else {
        return 0;
    }
}

std::vector<Point> graham_scan(const std::set<Point> points) {
    if (points.size() <= 2) {
        return std::vector<Point>(points.begin(), points.end());
    }

    Point pivot = *points.begin();
    std::vector<Point> pts(points.begin(), points.end());

    std::sort(pts.begin()+1, pts.end(), [=] (Point a, Point b) -> bool {
        int o = orientation(pivot, a, b);
        if (o == 0) {
            return dist(pivot, a) < dist(pivot, b);
        } else {
            return o == 1;
        }
    });

    std::vector<Point> hull;

    hull.push_back(pts[0]);
    hull.push_back(pts[1]);

    for (int i = 2; i < pts.size(); i++) {
        Point middle = hull.back(); hull.pop_back();
        while (orientation(hull.back(), middle, pts[i]) != 1) {
            middle = hull.back();
            hull.pop_back();
        };
        hull.push_back(middle);
        hull.push_back(pts[i]);
    }

    return hull;
}

int main() {
    int _;
    scanf("%d", &_);

    while (_--) {
        int N;
        scanf("%d", &N);

        std::set<Point> points;
        for (int i = 1; i <= N; i++) {
            double x, y;
            scanf("%lf%lf", &x, &y);
            points.emplace(x, y, i);
        }

        std::vector<Point> hull = graham_scan(points);

        double total = 0;

        for (int i = 0; i < hull.size(); i++) {
            total += dist(hull[i], hull[(i+1) % hull.size()]);
        }

        printf("%.2lf\n", total);

        for (int i = 0; i < hull.size(); i++) {
            printf("%d ", hull[i].i);
        }

        printf("\n\n");
    }

    return 0;
}
#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

struct Point {
    int x, y;
    Point(int x, int y) : x{ x }, y{ y } {}
};

Point *pts[10000];
int N;

int orientation(Point *a, Point *b, Point *c) {
    return (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);
}

int sqr_dist(Point *a, Point *b) {
    int dx = a->x - b->x, dy = a->y - b->y;
    return dx * dx + dy * dy;
}

double convex_hull_area() {
    if (N <= 2) return 0;

    sort(pts, pts + N, [] (Point *a, Point *b) -> bool {
        return a->y < b->y;
    });

    sort(pts + 1, pts + N, [&] (Point *a, Point *b) -> bool {
        int o = orientation(pts[0], a, b);
        return o ? o > 0 : sqr_dist(pts[0], a) < sqr_dist(pts[0], b);
    });

    vector<Point *> hull {pts[0], pts[1]};

    for (int i = 2; i < N; i++) {
        while (orientation(hull[hull.size() - 2], hull.back(), pts[i]) <= 0)
            hull.pop_back();
        hull.push_back(pts[i]);
    }

    double area = 0;

    for (int i = 0; i < hull.size(); i++)
        area += hull[i]->x * hull[(i + 1) % hull.size()]->y - hull[i]->y * hull[(i + 1) % hull.size()]->x;

    return abs(area) / 2;
}

int main() {
    scan(N);

    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        pts[i] = new Point(x, y);
    }

    double area = convex_hull_area();

    printf("%d\n", (int) (area / 50));

    return 0;
}
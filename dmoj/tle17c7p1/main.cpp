#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Point {
    int x, y;

    Point(int x, int y) : x{ x }, y{ y } {}

    bool operator<(Point that) const {
        if (x == that.x) return y < that.y;
        else return x < that.x;
    }
};

vector<Point> pt {{0, 0}};
set<Point> pts {{0, 0}};
int N;

int main() {
    scanf("%d", &N);

    for (int i = 2; i <= N; i++) {
        int p, x, y;
        scanf("%d%d%d", &p, &x, &y);
        p--;
        x += pt[p].x;
        y += pt[p].y;
        pt.emplace_back(x, y);
        pts.emplace(x, y);
    }

    printf("%d", pts.size());
}
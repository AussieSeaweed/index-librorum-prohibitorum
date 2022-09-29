#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

struct Line {
    double x, y1, y2;
    Line(double x, double y1, double y2) : x{ x }, y1{ y1 }, y2{ y2 } {}
};

struct Point {
    double x, y;
    Point(double x, double y) : x{ x }, y{ y } {}
};

vector<Line> lines;
vector<Point> pts {{0, 0}, {0, 0}, {100, 0}, {100, 0}};
int G, ans;
double A, B;

int main() {
    scan(G);

    for (int i = 0; i < G; i++) {
        int x, y1, y2;
        scan(x);
        scan(y1);
        scan(y2);
        lines.emplace_back(x, y1, y2);
        pts.emplace_back(x, y1);
        pts.emplace_back(x, y2);
    }

    for (int i = 0; i < pts.size(); i++) {
        for (int j = i & 1 ? i + 1 : i + 2; j < pts.size(); j++) {
            double m = (pts[i].y - pts[j].y) / (pts[i].x - pts[j].x), curA = - m * pts[i].x + pts[i].y;
            double curB = m * 100 + curA;
            if (curB < 0 || curA < 0) continue;
            int cnt = 0;

            for (Line &line : lines) {
                double y = m * line.x + curA;

                if (line.y1 - 1e-6 <= y && y <= line.y2 + 1e-6) {
                    cnt++;
                }
            }

            if (cnt > ans || (cnt == ans && curA < A) || (cnt == ans && curA == A && curB < B)) {
                ans = cnt;
                A = curA;
                B = curB;
            }
        }
    }

    printf("%d\n%.5lf\n%.5lf\n", ans, A, B);

    return 0;
}
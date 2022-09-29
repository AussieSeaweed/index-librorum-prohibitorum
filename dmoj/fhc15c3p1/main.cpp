#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

bool equals(double a, double b) {
    return b - 1e-6 <= a && a <= b + 1e-6;
}

struct Point {
    double x, y;
    Point(double x, double y) : x{ x }, y{ y } {}
    bool operator==(const Point &that) const {
        return equals(x, that.x) && equals(y, that.y);
    }
} *pts[3000], *sorted[3000], *pt0;
int T, N, D;

inline double sqr_dist(Point *a, Point *b) {
    double dx = a->x - b->x, dy = a->y - b->y;
    return dx * dx + dy * dy;
}

inline double dist(Point *a, Point *b) {
    return sqrt(sqr_dist(a, b));
}

struct POLAR_ORDER {
    Point *pivot;
    POLAR_ORDER(Point *pivot) : pivot{ pivot } {}
    bool operator()(Point *a, Point *b) {
        double angle_a = atan2(a->y - pivot->y, a->x - pivot->x), angle_b = atan2(b->y - pivot->y, b->x - pivot->x);
        return angle_a == angle_b ? sqr_dist(pivot, a) < sqr_dist(pivot, b) : angle_a < angle_b;
    }
};

int solve() {
    sort(pts, pts + N, POLAR_ORDER(pt0));
    int ans = 0;

    for (int i = 0; i < N;) {
        int j = i++, k = i;

        while (k < N && equals(atan2(pts[k]->y - pt0->y, pts[k]->x - pt0->x),
                        atan2(pts[j]->y - pt0->y, pts[j]->x - pt0->x)) && dist(pt0, pts[k]) <= D + 1e-6) k++;
        while (i < N && equals(atan2(pts[i]->y - pt0->y, pts[i]->x - pt0->x),
                        atan2(pts[j]->y - pt0->y, pts[j]->x - pt0->x))) i++;

        if (dist(pt0, pts[j]) <= D + 1e-6) {
            int A = k - j, B = 0;
            double angle = atan2(pts[j]->y - pt0->y, pts[j]->x - pt0->x);
            Point *endpt = new Point(cos(angle) * D + pt0->x, sin(angle) * D + pt0->y);
            copy(pts, pts + N, sorted);

            if (*pts[k - 1] == *endpt) {
                swap(sorted[0], sorted[k - 1]);
                sort(sorted + 1, sorted + N, POLAR_ORDER(endpt));

                for (int l = 1; l < N;) {
                    int m = l++;
                    while (l < N && equals(atan2(sorted[m]->y - endpt->y, sorted[m]->x - endpt->x),
                                           atan2(sorted[l]->y - endpt->y, sorted[l]->x - endpt->x)))
                        l++;
                    B = max(B, l - m);
                }

                B++;
            } else {
                sort(sorted, sorted + N, POLAR_ORDER(endpt));

                for (int l = 0; l < N;) {
                    int m = l++;
                    while (l < N && equals(atan2(sorted[m]->y - endpt->y, sorted[m]->x - endpt->x),
                                           atan2(sorted[l]->y - endpt->y, sorted[l]->x - endpt->x)))
                        l++;
                    B = max(B, l - m);
                }
            }

            ans = max(ans, A * B);
        }
    }

    return ans;
}

int main() {
    scan(T);

    for (int t = 1; t <= T; t++) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        pt0 = new Point(x, y);

        scan(D);
        scan(N);

        for (int i = 0; i < N; i++) {
            scanf("%lf%lf", &x, &y);
            pts[i] = new Point(x, y);
        }

        printf("Case #%d: %d\n", t, solve());
    }

    return 0;
}
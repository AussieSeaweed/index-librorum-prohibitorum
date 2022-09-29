#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

struct Point {
    long long x, y;
    int advantage;

    Point(long long x, long long y, int advantage) : x{ x }, y{ y }, advantage{ advantage } {}
};

int N, P, T;
int weight[102][102], dp[102][102];
Point *points[102];

long long orientation(Point *a, Point *b, Point *c) {
    return (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);
}

long long sqr_dist(Point *a, Point *b) {
    long long dx = a->x - b->x, dy = a->y - b->y;
    return dx * dx + dy * dy;
}

int main() {
    scan(P);
    scan(T);
    N = 1;
    points[0] = new Point(0, 0, 0);

    for (int i = 0; i < P; i++) {
        long long x, y;
        scanf("%lld%lld", &x, &y);
        points[N++] = new Point(x, y, 1);
    }

    for (int i = 0; i < T; i++) {
        long long x, y;
        scanf("%lld%lld", &x, &y);
        points[N++] = new Point(x, y, -1);
    }

    points[N] = new Point(0, 0, 0);

    sort(points + 1, points + N, [&] (Point *a, Point *b) -> bool {
        long long o1 = orientation(points[0], a, b);
        return o1 == 0 ? sqr_dist(points[0], a) < sqr_dist(points[0], b) : o1 > 0;
    });

    for (int i = 0; i <= N; i++) {
        for (int j = i; j <= N; j++) {
            for (int k = i; k <= j; k++) {
                if (orientation(points[i], points[k], points[j]) <= 0) {
                    weight[i][j] += points[k]->advantage;
                }
            }
        }
    }

    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) dp[i][j] = -inf;
    dp[0][0] = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < i; j++) {
            for (int k = 0; k <= j; k++) {
                if (orientation(points[k], points[j], points[i]) >= 0) {
                    dp[i][j] = max(dp[i][j], dp[j][k] + weight[j][i] - points[j]->advantage);
                }
            }
        }
    }

    int ans = 0;

    for (int i = 0; i < N; i++) {
        ans = max(ans, dp[N][i]);
    }

    printf("%d\n", ans);

    return 0;
}
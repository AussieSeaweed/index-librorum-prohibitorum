#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

struct Point {
    long long x, y;
    Point *prev, *next;
    bool marked = false;

    Point(long long x, long long y) : x{ x }, y{ y }, prev{ nullptr }, next{ nullptr } {}
};

struct Pivot {
    double x, y;

    Pivot(double x, double y) : x{ x }, y{ y } {}
};

inline long long orientation(const Point *a, const Point *b, const Point *c) {
    return (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);
}

int N;
Point *pts[300000], *q[300000], *y_order[300000], *x_order[300000];
int qp = 0;
Pivot *pivot;
char instructions[300000];
long long area[300000];
bool is_odd[300000];

struct PIVOT_ORDER {
    inline bool operator()(const Point *a, const Point *b) {
        return atan2(a->y - pivot->y, a->x - pivot->x) < atan2(b->y - pivot->y, b->x - pivot->x);
    }
};

set<Point *, PIVOT_ORDER> hull;

template<typename Collection>
inline pair<long long, bool> get_area(const Collection &vertices) {
    long long ret = 0;

    for (int i = 0; i < vertices.size(); i++)
        ret += vertices[i]->x * vertices[(i + 1) % vertices.size()]->y - vertices[i]->y * vertices[(i + 1) % vertices.size()]->x;

    ret = abs(ret);

    return {ret / 2, ret & 1};
}

inline void build() {
    copy(pts, pts + N, y_order);
    copy(pts, pts + N, x_order);
    sort(y_order, y_order + N, [] (const Point *a, const Point *b) -> bool {
        return a->y < b->y;
    });
    sort(x_order, x_order + N, [] (const Point *a, const Point *b) -> bool {
        return a->x < b->x;
    });
    int xi = 0, xj = N - 1, yi = 0, yj = N - 1;

    for (int i = 0; i < N - 3; i++) {
        switch (instructions[i]) {
            case 'L': {
                while (x_order[xi]->marked) xi++;
                q[qp++] = x_order[xi];
                x_order[xi++]->marked = true;
            }
                break;
            case 'R': {
                while (x_order[xj]->marked) xj--;
                q[qp++] = x_order[xj];
                x_order[xj--]->marked = true;
            }
                break;
            case 'U': {
                while (y_order[yj]->marked) yj--;
                q[qp++] = y_order[yj];
                y_order[yj--]->marked = true;
            }
                break;
            case 'D': {
                while (y_order[yi]->marked) yi++;
                q[qp++] = y_order[yi];
                y_order[yi++]->marked = true;
            }
                break;
            default: break;
        }
    }

    long long sum_x = 0, sum_y = 0;

    for (int i = 0; i < N; i++)
        if (!pts[i]->marked) {
            sum_x += pts[i]->x;
            sum_y += pts[i]->y;
        }

    pivot = new Pivot(sum_x / 3., sum_y / 3.);

    for (int i = 0; i < N; i++)
        if (!pts[i]->marked)
            hull.insert(pts[i]);

    vector<Point *> pt_vec(hull.begin(), hull.end());

    for (int i = 0; i < 3; i++) {
        pt_vec[i]->next = pt_vec[(i + 1) % 3];
        pt_vec[(i + 1) % 3]->prev = pt_vec[i];
    }

    pair<long long, bool> query = get_area(pt_vec);
    area[N - 3] = query.first;
    is_odd[N - 3] = query.second;
}

inline void solve() {
    for (int i = N - 4; i >= 0; i--) {
        deque<Point *> delta;
        Point *pt = q[--qp];
        auto it = hull.lower_bound(pt);
        it = it == hull.end() ? hull.begin() : it;
        Point *after = *it, *before = after->prev;

        while (orientation(pt, after, after->next) < 0) {
            hull.erase(after);
            delta.push_front(after);
            after = after->next;
        }

        while (orientation(before->prev, before, pt) < 0) {
            hull.erase(before);
            delta.push_back(before);
            before = before->prev;
        }

        delta.push_front(after);
        delta.push_back(before);
        delta.push_back(pt);

        after->prev = pt;
        pt->next = after;
        before->next = pt;
        pt->prev = before;

        pair<long long, bool> query = get_area(delta);
        area[i] = area[i + 1] + query.first;

        if (is_odd[i + 1] && query.second) {
            area[i]++;
        } else if (is_odd[i + 1] || query.second) {
            is_odd[i] = true;
        }

        hull.insert(pt);
    }
}

int main() {
    scan(N);

    for (int i = 0; i < N; i++) {
        long long x, y;
        scan(x);
        scan(y);
        pts[i] = new Point(x, y);
    }

    scanf("%s", instructions);

    build();
    solve();

    for (int i = 0; i < N - 2; i++)
        if (is_odd[i])
            printf("%lld.5\n", area[i]);
        else
            printf("%lld.0\n", area[i]);

    return 0;
}
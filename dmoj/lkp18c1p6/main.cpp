#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
template<typename T>constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T>constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

struct Point {
    long long x, y, soln = INF;
    Point(long long x, long long y) : x{ x }, y{ y } {}
};

int N, M;
Point *coms[100000], *bunks[100000];
long long by[200001], xpy[200001], xmy[200001];
unordered_map<long long, int> segy;

void minbitupdate(int i, long long value, long long bit[]) {
    while (i <= 200000) {
        bit[i] = min(value, bit[i]);
        i += i & -i;
    }
}

long long minbitquery(int i, long long bit[]) {
    long long ret = INF;

    while (i) {
        ret = min(ret, bit[i]);
        i -= i & -i;
    }

    return ret;
}

void maxbitupdate(int i, long long value, long long bit[]) {
    while (i <= 200000) {
        bit[i] = max(bit[i], value);
        i += i & -i;
    }
}

long long maxbitquery(int i, long long bit[]) {
    long long ret = -INF;

    while (i) {
        ret = max(ret, bit[i]);
        i -= i & -i;
    }

    return ret;
}

int inv(int i) {
    return 200001 - i;
}

int main() {
    scan(N);

    for (int i = 0; i < N; i++) {
        long long x, y;
        scan(x);
        scan(y);
        x += 1000000001, y += 1000000001;
        coms[i] = new Point(x, y);
        by[i + 1] = y;
    }

    scan(M);

    for (int i = 0; i < M; i++) {
        long long x, y;
        scan(x);
        scan(y);
        x += 1000000001, y += 1000000001;
        bunks[i] = new Point(x, y);
        by[N + i + 1] = y;
    }

    sort(by + 1, by + M + N + 1);
    for (int i = 1; i <= M + N; i++)
        segy[by[i]] = i;

    sort(coms, coms + N, [] (Point *a, Point *b) -> bool { return a->x < b->x; });
    sort(bunks, bunks + M, [] (Point *a, Point *b) -> bool { return a->x < b->x; });
    fill(xpy, xpy + 200001, -INF);
    fill(xmy, xmy + 200001, -INF);

    for (int i = 0, j = 0; i < N; i++) {
        while (j < M && bunks[j]->x <= coms[i]->x) {
            maxbitupdate(segy[bunks[j]->y], bunks[j]->x + bunks[j]->y, xpy);
            maxbitupdate(inv(segy[bunks[j]->y]), bunks[j]->x - bunks[j]->y, xmy);
            j++;
        }

        long long x = coms[i]->x, y = coms[i]->y;
        int sy = segy[y];

        coms[i]->soln = min(coms[i]->soln, x - y - maxbitquery(inv(sy), xmy), x + y - maxbitquery(sy, xpy));
    }

    fill(xpy, xpy + 200001, INF);
    fill(xmy, xmy + 200001, INF);

    for (int i = N - 1, j = M - 1; i >= 0; i--) {
        while (j >= 0 && bunks[j]->x >= coms[i]->x) {
            minbitupdate(inv(segy[bunks[j]->y]), bunks[j]->x + bunks[j]->y, xpy);
            minbitupdate(segy[bunks[j]->y], bunks[j]->x - bunks[j]->y, xmy);
            j--;
        }

        long long x = coms[i]->x, y = coms[i]->y;
        int sy = segy[y];

        coms[i]->soln = min(coms[i]->soln, -x - y + minbitquery(inv(sy), xpy), -x + y + minbitquery(sy, xmy));
    }

    long long ans = 0;

    for (int i = 0; i < N; i++) {
        ans += coms[i]->soln;
    }

    printf("%lld\n", ans);

    return 0;
}
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
template<typename T> inline constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T> inline constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> inline constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> inline constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int mat[3001][3001];

bool exists(int R, int C, int H, int W, int Q[3001][3001], int mid) {
    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            mat[r + 1][c + 1] = Q[r][c] <= mid, mat[r + 1][c + 1] += mat[r + 1][c] + mat[r][c + 1] - mat[r][c];

    int threshold = H * W / 2 + 1;

    for (int r = H; r <= R; r++)
        for (int c = W; c <= C; c++)
            if (mat[r][c] - mat[r - H][c] - mat[r][c - W] + mat[r - H][c - W] >= threshold)
                return true;

    return false;
}

int rectangle(int R, int C, int H, int W, int Q[3001][3001]) {
    int lo = inf, hi = -inf;

    for (int r = 0; r < R; r++)
        for (int c = 0; c < C; c++)
            lo = min(lo, Q[r][c]), hi = max(hi, Q[r][c]);

    while (lo <= hi) {
        int mid = (lo + hi) / 2;

        if (exists(R, C, H, W, Q, mid)) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    return lo;
}

int main() {
    return 0;
}
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
template<typename T>constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T>constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int R, C;
vector<pair<int, pair<int, int>>> boundaries;
char str[1005];

int solve() {
    int rdir = (R - 1) & 1, ldir = !rdir, ans = 0;

    for (int i = boundaries.size() - 1; i > 0; i--) {
        int cdir = boundaries[i].first & 1, ndir = boundaries[i - 1].first & 1;
        ans += boundaries[i].second.second - boundaries[i].second.first;

        if (cdir == rdir && ndir == rdir) {
            ans += abs(boundaries[i].second.second - boundaries[i - 1].second.first);
        } else if (cdir == ldir && ndir == ldir) {
            ans += abs(boundaries[i].second.first - boundaries[i - 1].second.second);
        } else if (cdir == rdir && ndir == ldir) {
            ans += abs(boundaries[i].second.second - boundaries[i - 1].second.second);
        } else if (cdir == ldir && ndir == rdir) {
            ans += abs(boundaries[i].second.first - boundaries[i - 1].second.first);
        }
    }

    return ans + boundaries[0].second.second - boundaries[0].second.first + boundaries.back().first - boundaries.front().first;
}

int main() {
    scan(R);
    scan(C);

    int highest = inf;
    int p = -1;

    for (int r = 0; r < R; r++) {
        scanf("%s", str);
        int lo = inf, hi = -inf;
        bool exists = false;

        for (int c = 0; c < C; c++) {
            if (str[c] == 'J') {
                exists = true;
                lo = min(lo, c);
                hi = c;
            }
        }

        if (exists) {
            boundaries.push_back(make_pair(r, make_pair(lo, hi)));
        }
    }

    if (boundaries.back().first == R - 1) {
        boundaries.back().second.first = 0;
    } else {
        boundaries.push_back(make_pair(R - 1, make_pair(0, 0)));
    }

    printf("%d\n", solve());

    return 0;
}
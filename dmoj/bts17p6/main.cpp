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

int N, s[100001], bit[100001];
unordered_map<int, int> indices;

void update(int i, int v) {
    while (i <= 100000) {
        bit[i] += v;
        i += i & -i;
    }
}

int query(int i) {
    int ret = 0;
    while (i) {
        ret += bit[i];
        i -= i & -i;
    }
    return ret;
}

int main() {
    scan(N);

    for (int i = 1; i <= N; i++)
        scan(s[i]);

    for (int i = 1; i <= N; i++) {
        int o;
        scan(o);
        indices[o] = i;
    }

    for (int i = 1; i <= N; i++) {
        s[i] = indices[s[i]];
    }

    for (int i = 1; i <= N; i++) {
        indices[s[i]] = i;
    }

    pair<int, int> maximum, current { 0, 1 };

    for (int i = 1; i <= N; i++) {
        if (indices[i - 1] < indices[i]) {
            current.first++;
        } else {
            maximum = max(maximum, current);
            current = { 1, i };
        }
    }

    maximum = max(maximum, current);

    printf("%d\n", N - maximum.first);

    for (int i = maximum.second - 1; i >= 1; i--) {
        printf("F %d\n", indices[i] + query(indices[i]));
        update(1, 1);
        update(indices[i], -1);
    }

    for (int i = maximum.second + maximum.first; i <= N; i++) {
        printf("B %d\n", indices[i] + query(indices[i]));
        update(indices[i], -1);
    }

    return 0;
}
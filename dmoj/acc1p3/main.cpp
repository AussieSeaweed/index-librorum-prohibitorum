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
#define MOD 998244353
using namespace std;

__int128 a[100000], b[100000], N, T;

pair<__int128, __int128> required(__int128 val) {
    __int128 t = 0, total = 0;

    for (int i = 0; i < N; i++) {
        if (a[i] > val) {
            __int128 a = ::a[i], b = ::b[i];
            __int128 n = (a - val) / b;
            total = (total + n * (a + a - b * (n - 1)) / 2) % MOD;
            a -= b * n; // a after n times
            // while v > val, use
            if (a > val) {
                n++;
                total += a;
            }
            t += n;
        }
    }

    return {t, total};
}

__int128 strict(__int128 val) {
    __int128 total = 0;

    for (int i = 0; i < N && T; i++) {
        if (a[i] > val) {
            __int128 n = min(T, (a[i] - val) / b[i]);
            total = (total + n * (a[i] + a[i] - b[i] * (n - 1)) / 2) % MOD;
            a[i] -= b[i] * n;
            T -= n;
        }
    }

    sort(a, a + N, greater<__int128>());
    __int128 lim = min(N, T);
    for (int i = 0; i < lim; i++) {
        total = (total + a[i]) % MOD;
    }

    return total;
}

int main() {
    pscan(N);
    pscan(T);

    for (int i = 0; i < N; i++) {
        pscan(a[i]);
        pscan(b[i]);
    }
    
    __int128 lo = 0, hi = 1000000000000000000;

    while (lo <= hi) {
        __int128 mid = lo + (hi - lo) / 2;
        pair<__int128, __int128> query = required(mid);

        if (query.first <= T) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    __int128 query = strict(lo);

    char str[20], ptr = 0;

    while (query) {
        str[ptr++] = query % 10 + '0';
        query /= 10;
    }

    reverse(str, str + ptr);

    printf("%s\n", str);

    return 0;
}
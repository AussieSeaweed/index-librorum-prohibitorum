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

pair<int, int> a, b, c;

bool three_abrest() {
    for (int al = a.first, ah = a.second, i = 0; i < 2; i++, al = a.second, ah = a.first) {
        for (int bl = b.first, bh = b.second, j = 0; j < 2; j++, bl = b.second, bh = b.first) {
            for (int cl = c.first, ch = c.second, k = 0; k < 2; k++, cl = c.second, ch = c.first) {
                if (ah == bh == ch && ah == al + bl + cl) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool two_abrest(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
    for (int al = a.first, ah = a.second, i = 0; i < 2; i++, al = a.second, ah = a.first) {
        for (int bl = b.first, bh = b.second, j = 0; j < 2; j++, bl = b.second, bh = b.first) {
            for (int cl = c.first, ch = c.second, k = 0; k < 2; k++, cl = c.second, ch = c.first) {
                if (ah == ch + bh && bl + al == cl + al && ah == al + cl) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool possible() {
    return three_abrest() || two_abrest(a, b, c) || two_abrest(b, a, c) || two_abrest(c, a, b);
}

int main() {
    scan(a.first);
    scan(a.second);
    scan(b.first);
    scan(b.second);
    scan(c.first);
    scan(c.second);

    if (possible()) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}
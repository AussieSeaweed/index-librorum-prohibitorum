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

int N, tmp[100000], start[100000];
string str[100000];
string ans;

int main() {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    ans.reserve(1000000);
    cin >> N;

    for (int i = 0; i < N; i++) cin >> str[i];

    for (int c = 'z'; c >= 'a';) {
        bool found_all = true;

        for (int i = 0; i < N; i++) {
            tmp[i] = str[i].find(c, start[i]);
            if (tmp[i] == -1) {
                found_all = false;
                break;
            }
        }

        if (!found_all) {
            c--;
            continue;
        }

        ans.push_back(c);

        for (int i = 0; i < N; i++) {
            start[i] = tmp[i] + 1;
        }
    }

    if (ans.empty()) {
        cout << -1 << '\n';
    } else {
        cout << ans << '\n';
    }

    return 0;
}
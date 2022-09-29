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

int N;
string rows[] {
    "",
    "qwertyuiop",
    "asdfghjkl",
    "zxcvbnm"
};
unordered_map<char, int> row;

int main() {
    for (int i = 1; i <= 3; i++)
        for (char ch : rows[i])
            row[ch] = i;

    scan(N);
    int ans = 0;

    while (N--) {
        string str;
        cin >> str;

        bool valid = true;

        for (int i = 0; i < str.size() - 1 && valid; i++) {
            if (row[str[i]] != row[str[i + 1]]) {
                valid = false;
            }
        }

        if (valid)
            ans++;
    }

    printf("%d\n", ans);

    return 0;
}
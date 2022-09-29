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

string input, ans;

int main() {
    cin >> input;
    ans = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";

    for (int i = 1; i < input.size() - 1; i++)
        for (int j = i + 1; j < input.size(); j++) {
            string strlist[]{input.substr(0, i), input.substr(i, j - i), input.substr(j, input.size() - j)};
            for (int k = 0; k < 3; k++)
                reverse(strlist[k].begin(), strlist[k].end());
            ans = min(ans, strlist[0] + strlist[1] + strlist[2]);
        }

    cout << ans;
    return 0;
}
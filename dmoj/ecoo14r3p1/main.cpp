#include <bits/stdc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
using namespace std;
template<typename T> using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> using max_priority_queue = std::priority_queue<T>;
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x: y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) min(__VA_ARGS_)
#define max(...) max(__VA_ARGS_)
unordered_map<int, char> dict;
unordered_map<char, int> dict2;
string punc = " .,?";//63,64,65 and 66
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (char c = 'A'; c <= 'Z'; ++c) {
        dict[c - 'A' + 1] = c;
        dict2[c] = c - 'A' + 1;
    }
    for (char c = 'a'; c <= 'z'; ++c) {
        dict[c - 'a' + 27] = c;
        dict2[c] = c - 'a' + 27;
    }
    for (char c = '0'; c <= '9'; ++c) {
        dict[c - '0' + 53] = c;
        dict2[c] = c - '0' + 53;
    }
    int counter = 0;
    for (char c : punc) {
        dict[counter + 63] = c;
        dict2[c] = counter + 63;
        counter++;
    }
    string normal;
    string encrypt;
    string task;
    for (int test = 0; test < 10; ++test) {
        getline(cin, normal);
        getline(cin, encrypt);
        getline(cin, task);
        int new_id = dict2[encrypt[1]];
        int id = dict2[normal[1]];
        int key;
        for (int i = 2; i <= 66; ++i) {
            if (id == (new_id * i) % 67) {
                key = i;
                break;
            }
        }
        string ans = "";
        for (int i = 1; i < (int)task.length() - 1; ++i) {
            int o = (key * dict2[task[i]]) % 67;
            ans += dict[o];
        }
        cout << "*" << ans << "*\n";
    }
    return 0;
}
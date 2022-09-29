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
map<string, int> id;
map<int, string> id2;
vector<int> adj_go_up[1001];
vector<int> adj_go_down[1001];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    string s1, s2;
    int counter = 1;
    for (int i = 0; i < N; ++i) {
        cin >> s1 >> s2;
        if (id[s1] == 0) {
            id[s1] = counter++;
        }
        if (id[s2] == 0) {
            id[s2] = counter++;
        }
        adj_go_up[id[s2]].push_back(id[s1]);
        adj_go_down[id[s1]].push_back(id[s2]);
    }
//    cout << id["Jenna"];
//    cout << adj_go_down[0].size() << "\n";
    for (int i = 0; i < 10; ++i) {
        cin >> s1;
        int curr_id = id[s1];
        int cousins = 0;
        int sisters = 0;
        if (adj_go_up[curr_id].size()) {
            int mother = adj_go_up[curr_id].back();
            sisters = adj_go_down[mother].size() - 1;
            if (adj_go_up[mother].size()) {
                int mother2 = adj_go_up[mother].back();
                for (int m : adj_go_down[mother2]) {
                    if (m != mother) {
                        cousins += adj_go_down[m].size();
                    }
                }
            }
        }
        cout << "Cousins: " << cousins << ", " << "Sisters: " << sisters << "\n";
    }
}
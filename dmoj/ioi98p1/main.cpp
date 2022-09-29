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
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first); auto h2 = std::hash<T2>{}(p.second); return h1 ^ h2;
    }
};
using namespace std;

struct COMPARE {
    bool operator()(const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b) {
        return a.first == b.first ? (a.second.second == b.second.second ? a.second.first > b.second.first : a.second.second > b.second.second) : a.first > b.first;
    }
};

int N, A, B;
unordered_map<int, int> cnt[13];
vector<pair<int, pair<int, int>>> res;
string str;

void to_bin_str(pair<int, int> p) {
    int i = p.first, j = p.second;
    string ret;
    while (i) {
        ret += (i & 1) + '0';
        i >>= 1;
    }
    while (ret.size() < j) {
        ret += '0';
    }
    cout << string(ret.rbegin(), ret.rend()) << " ";
}

int main() {
    cin.sync_with_stdio(false), cin.tie(nullptr);
    cin >> A >> B >> N >> str;
    str.pop_back();

    for (int i = 0; i < str.size(); i++) {
        int val = 0;
        for (int j = 1; j < A && i + j - 1 < str.size(); j++) {
            val = (val << 1) + str[i + j - 1] - '0';
        }
        for (int j = A; j <= B && i + j - 1 < str.size(); j++) {
            val = (val << 1) + str[i + j - 1] - '0';
            cnt[j][val]++;
        }
    }

    int total = 0;
    for (int i = A; i <= B; i++) total += cnt[i].size();
    res.resize(total);
    int ptr = 0;

    for (int i = A; i <= B; i++) {
        for (const auto &p : cnt[i]) {
            res[ptr++] = {p.second, make_pair(p.first, i)};
        }
    }

    sort(res.begin(), res.end(), COMPARE());
    auto it = res.begin();
    int rank = 0, pr = inf;

    while (it != res.end()) {
        if (pr != it->first) {
            rank++;
            pr = it->first;
            if (rank > N) break;
            cout << "\n" << pr << " ";
        }

        to_bin_str(it->second);
        it++;
    }

    return 0;
}
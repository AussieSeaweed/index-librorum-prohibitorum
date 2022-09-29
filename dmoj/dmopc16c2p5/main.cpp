#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
template<typename T>constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T>constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, M, K, refcnt[200001], cnt[200001];
bitset<5000> *m[200001];
pair<char, int> instructions[200001];
priority_queue<pair<int, int>> prev_vals;

int main() {
    scan(N);
    scan(M);
    scan(K);

    for (int i = 1; i <= M; i++) {
        scanf(" %c", &instructions[i].first);

        if (instructions[i].first == 'R') {
            scan(instructions[i].second);
            refcnt[instructions[i].second]++;
        } else if (instructions[i].first == 'X') {
            refcnt[i - 1]++;
        } else {
            scan(instructions[i].second);
            refcnt[i - 1]++;
        }
    }

    m[0] = new bitset<5000>();
    prev_vals.emplace(0, 0);

    for (int i = 1; i <= M; i++) {
        while (prev_vals.top().second <= i - K) prev_vals.pop();

        switch (instructions[i].first) {
            case 'F': {
                m[i] = new bitset<5000>(*m[i - 1]);
                cnt[i] = cnt[i - 1];
                if (!m[i]->test(instructions[i].second - 1))
                    cnt[i]++;
                m[i]->set(instructions[i].second - 1);
                if (--refcnt[i - 1] == 0) delete m[i - 1];
            }
                break;
            case 'D': {
                m[i] = new bitset<5000>(*m[i - 1]);
                cnt[i] = cnt[i - 1];
                if (m[i]->test(instructions[i].second - 1)) cnt[i]--;
                m[i]->reset(instructions[i].second - 1);
                if (--refcnt[i - 1] == 0) delete m[i - 1];
            }
                break;
            case 'R': {
                m[i] = new bitset<5000>(*m[instructions[i].second]);
                cnt[i] = cnt[instructions[i].second];
                if (--refcnt[instructions[i].second] == 0) delete m[instructions[i].second];
            }
                break;
            case 'X': {
                m[i] = new bitset<5000>(*m[i - 1]);
                m[i]->flip();
                cnt[i] = N - cnt[i - 1];
                if (--refcnt[i - 1] == 0) delete m[i - 1];
            }
                break;
        }

        prev_vals.emplace(cnt[i], i);
        printf("%d %d\n", cnt[i], prev_vals.top().first);
        if (!refcnt[i]) delete m[i];
    }

    return 0;
}
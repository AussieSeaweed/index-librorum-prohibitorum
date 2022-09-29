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

int N, M, Q, block_size = 388, line_offset[150000], line_id[150000], block_ppl[388], inner_id[150000];
vector<int> stations[150000], cur[150000], critical_stations[150000];

int query(int l, int r) {
    int lb = l / block_size, rb = r / block_size;

    if (lb == rb) {
        int ret = 0;

        for (int i = l; i <= r; i++) {
            ret += cur[line_id[i]][((inner_id[i] + line_offset[line_id[i]]) % ((int) cur[line_id[i]].size()) + ((int) cur[line_id[i]].size())) % cur[line_id[i]].size()];
        }

        return ret;
    } else {
        int ret = 0;

        for (int i = l, lim = (lb + 1) * block_size; i < lim; i++) {
            ret += cur[line_id[i]][((inner_id[i] + line_offset[line_id[i]]) % ((int) cur[line_id[i]].size()) + ((int) cur[line_id[i]].size())) % cur[line_id[i]].size()];
        }

        for (int i = lb + 1; i < rb; i++) {
            ret += block_ppl[i];
        }

        for (int i = rb * block_size; i <= r; i++) {
            ret += cur[line_id[i]][((inner_id[i] + line_offset[line_id[i]]) % ((int) cur[line_id[i]].size()) + ((int) cur[line_id[i]].size())) % cur[line_id[i]].size()];
        }

        return ret;
    }
}

bool check(int block) {
    int cnt = 0;
    int lim = min(N, (block + 1) * block_size);
    for (int i = block * block_size; i < lim; i++) {
        cnt += cur[line_id[i]][((inner_id[i] + line_offset[line_id[i]]) % ((int) cur[line_id[i]].size()) + ((int) cur[line_id[i]].size())) % cur[line_id[i]].size()];
    }
    return block_ppl[block] == cnt;
}

void check() {
    int i = 0, b = 0;
    while (i < N) {
        assert(check(b));
        b++;
        i += block_size;
    }
}

void update_line(int x) {
    for (int s : critical_stations[x]) {
        int ns = stations[x][(inner_id[s] + 1) % stations[x].size()];
        int cur_block = s / block_size, next_block = ns / block_size;
        int cur_ppl = cur[x][((inner_id[s] + line_offset[x]) % ((int) cur[x].size()) + ((int) cur[x].size())) % cur[x].size()];
        block_ppl[cur_block] -= cur_ppl;
        block_ppl[next_block] += cur_ppl;
    }

    line_offset[x]--;
}

int main() {
    scan(N);
    scan(M);
    scan(Q);

    for (int i = 0; i < N; i++) {
        scan(line_id[i]);
        line_id[i]--;
        inner_id[i] = stations[line_id[i]].size();

        stations[line_id[i]].push_back(i);
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < stations[i].size(); j++) {
            if ((stations[i][j] / block_size) != (stations[i][(j + 1) % stations[i].size()] / block_size)) {
                critical_stations[i].push_back(stations[i][j]);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        int ppl;
        scan(ppl);
        cur[line_id[i]].push_back(ppl);
        block_ppl[i / block_size] += ppl;
    }

    while (Q--) {
        int t;
        scan(t);

        if (t == 1) {
            int l, r;
            scan(l);
            scan(r);
            l--, r--;
            printf("%d\n", query(l, r));
        } else {
            int x;
            scan(x);
            x--;
            update_line(x);
        }
    }

    return 0;
}
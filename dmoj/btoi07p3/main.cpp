#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, M, C;
int values[1000000];
deque<pair<int, int>> max_q, min_q;

int main() {
    scan(N);
    scan(M);
    scan(C);

    for (int i = 0; i < N; i++)
        scan(values[i]);

    for (int i = 0; i < M - 1; i++) {
        while (!max_q.empty() && max_q.back().first < values[i]) max_q.pop_back();
        while (!min_q.empty() && min_q.back().first > values[i]) min_q.pop_back();
        max_q.emplace_back(values[i], i);
        min_q.emplace_back(values[i], i);
    }

    bool exists = false;

    for (int i = M - 1; i < N; i++) {
        if (max_q.front().second <= i - M) max_q.pop_front();
        if (min_q.front().second <= i - M) min_q.pop_front();

        while (!max_q.empty() && max_q.back().first < values[i]) max_q.pop_back();
        while (!min_q.empty() && min_q.back().first > values[i]) min_q.pop_back();
        max_q.emplace_back(values[i], i);
        min_q.emplace_back(values[i], i);

        if (max_q.front().first - min_q.front().first <= C) {
            printf("%d\n", i - M + 2);
            exists = true;
        }
    }

    if (!exists) printf("NONE\n");

    return 0;
}
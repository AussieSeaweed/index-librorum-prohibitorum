#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

unordered_map<int, int> indices;
vector<pair<int, int>> pairs;

int main() {
    int Q, begin = 0, end = 1;
    scan(Q);

    while (Q--) {
        char t;
        scanf(" %c", &t);

        switch (t) {
            case 'F': {
                int x;
                scan(x);
                indices[x] = begin--;
            }
                break;
            case 'E': {
                int x;
                scan(x);
                indices[x] = end++;
            }
                break;
            default: {
                int x;
                scan(x);
                indices.erase(x);
            }
        }
    }

    pairs.reserve(100000);

    for (auto &p : indices) {
        pairs.emplace_back(p.second, p.first);
    }

    sort(pairs.begin(), pairs.end());

    for (auto &p : pairs)
        printf("%d\n", p.second);

    return 0;
}
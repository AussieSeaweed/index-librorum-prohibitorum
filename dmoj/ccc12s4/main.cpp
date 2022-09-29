#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

int add_top(int state, int val) {
    return state * 10 + val;
}

int get_top(int state) {
    return state % 10;
}

int pop_top(int state) {
    return state / 10;
}

bool in_order(vector<int>& coins, int N) {
    for (int i = 0; i < N; i++) {
        if (get_top(coins[i]) != i + 1) return false;
    }
    return true;
}

int bfs(vector<int>& coins, int N) {
    set<vector<int>> visited;
    queue<pair<vector<int>, int>> q;
    q.emplace(coins, 0);
    visited.insert(coins);

    while (!q.empty()) {
        pair<vector<int>, int> p = q.front(); q.pop();
        vector<int>& coins = p.first;
        int steps = p.second;
        if (in_order(coins, N)) return steps;
        for (int i = 0; i < N; i++) {
            if (coins[i]) {
                if (i > 0 && (!coins[i - 1] || get_top(coins[i - 1]) > get_top(coins[i]))) {
                    vector<int> ns = coins;
                    ns[i - 1] = add_top(ns[i - 1], get_top(coins[i]));
                    ns[i] = pop_top(coins[i]);
                    if (!visited.count(ns)) {
                        q.emplace(ns, steps + 1);
                        visited.insert(ns);
                    }
                }
                if (i < N - 1 && (!coins[i + 1] || get_top(coins[i + 1]) > get_top(coins[i]))) {
                    vector<int> ns = coins;
                    ns[i + 1] = add_top(ns[i + 1], get_top(coins[i]));
                    ns[i] = pop_top(coins[i]);
                    if (!visited.count(ns)) {
                        q.emplace(ns, steps + 1);
                        visited.insert(ns);
                    }
                }
            }
        }
    }
    return -1;
}

int main() {
    while (1) {
        int N;
        scanf("%d", &N);
        if (!N) break;
        vector<int> coins(N);
        for (int i = 0; i < N; i++)
            scanf("%d", &coins[i]);
        int ans = bfs(coins, N);
        if (ans == -1) printf("IMPOSSIBLE\n");
        else printf("%d\n", ans);
    }
    return 0;
}
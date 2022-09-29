#include <bits/stdc++.h>

class Event {
public:
    int node, time;

    Event(int n, int t) {
        node = n;
        time = t;
    }

    bool operator > (Event that) const {
        return time > that.time;
    }
};

int main() {
    int N;
    scanf("%d", &N);

    std::vector<std::set<int>> graph(N + 1);
    std::vector<int> last_barked(N + 1, -1);
    std::vector<int> state(N + 1, 0); // 0 = sleeping, 1 = waiting
    std::vector<int> wait_time(N + 1);
    std::vector<int> count(N + 1, 0);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &wait_time[i]);
    }


    int M;
    scanf("%d", &M);

    while (M--) {
        int x, y;
        scanf("%d%d", &x, &y);
        graph[x].insert(y);
    }

    int T;
    scanf("%d", &T);

    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> pq;
    pq.emplace(1, 0);

    while (!pq.empty()) {
        Event e = pq.top();
        pq.pop();

        if (e.time > T) break;

        last_barked[e.node] = e.time;
        state[e.node] = 0;
        count[e.node]++;

        for (int adj : graph[e.node])
            if (!state[adj] && last_barked[adj] != e.time) {
                state[adj] = 1;
                pq.emplace(adj, e.time + wait_time[adj]);
            }
    }

    for (int i = 1; i <= N; i++)
        printf("%d\n", count[i]);

    return 0;
}
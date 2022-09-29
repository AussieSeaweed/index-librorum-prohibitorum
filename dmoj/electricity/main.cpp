#include <iostream>
#include <queue>

struct Event {
    int length, index;

    bool operator<(const Event &other) const {
        return length > other.length;
    }
};

int T, N, X[100000], P[100000];
std::priority_queue<Event> pq;

void explore(int index) {
    if (index > 0 && !P[index - 1]) pq.push({ X[index] - X[index - 1], index - 1});
    if (index < N - 1 && !P[index + 1]) pq.push({ X[index + 1] - X[index], index + 1});
}

int main() {
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> T;

    while (T--) {
        std::cin >> N;

        for (int i = 0; i < N; ++i)
            std::cin >> X[i] >> P[i];

        for (int i = 0; i < N; ++i)
            if (P[i]) explore(i);

        long long sum = 0;

        while (!pq.empty()) {
            Event event = pq.top(); pq.pop();

            if (!P[event.index]) {
                P[event.index] = 1;

                sum += event.length;
                explore(event.index);
            }
        }

        std::cout << sum << std::endl;
    }

    return 0;
}
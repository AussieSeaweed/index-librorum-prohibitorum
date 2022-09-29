#include <bits/stdc++.h>

class Event {
public:
    int x, y1, y2, val;

    Event(int x, int y1, int y2, int val) {
        this->x = x;
        this->y1 = y1;
        this->y2 = y2;
        this->val = val;
    }
};

int N, M;

int main() {
    scanf("%d%d", &N, &M);

    std::vector<Event> events;
    std::set<int> ys;

    while (M--) {
        int x, y, w, h;
        scanf("%d%d%d%d", &x, &y, &w, &h);

        events.emplace_back(x, y, y + h, 1);
        events.emplace_back(x + w, y, y + h, -1);
        ys.insert(y);
        ys.insert(y + h);
    }

    std::sort(events.begin(), events.end(), [] (Event a, Event b) {
        return a.x < b.x;
    });

    std::vector<int> y_vector(ys.begin(), ys.end());
    std::unordered_map<int, int> findy;

    for (int i = 0; i < y_vector.size(); i++) {
        findy[y_vector[i]] = i;
    }

    std::vector<int> sweep_line(y_vector.size(), 0);

    int whites = 0;

    for (int i = 0; i < events.size(); i++) {
        for (int j = 0; j < sweep_line.size(); j++) {
            if (sweep_line[j] % 2 != 0) {
                whites += (events[i].x - events[i - 1].x) * (y_vector[j + 1] - y_vector[j]);
            }
        }

        for (int j = findy[events[i].y1]; j < findy[events[i].y2]; j++) {
            sweep_line[j] += events[i].val;
        }
    }

    printf("%d", whites);

    return 0;
}
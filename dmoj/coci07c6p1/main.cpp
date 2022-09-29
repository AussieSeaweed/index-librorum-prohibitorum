#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int fare[4] {0};

class Event {
public:
    int t;
    bool begin;

    Event(int t, bool begin) : t{ t }, begin{ begin } {}

    bool operator<(Event that) {
        return t < that.t;
    }
};

vector<Event> events;

int main() {
    scanf("%d%d%d", &fare[1], &fare[2], &fare[3]);

    for (int i = 0; i < 3; i++) {
        int begin, end;
        scanf("%d%d", &begin, &end);
        events.emplace_back(begin, 1);
        events.emplace_back(end, 0);
    }

    sort(events.begin(), events.end());

    int ans = 0;
    int last = 0;
    int num = 0;

    for (Event e : events) {
        ans += (e.t - last) * fare[num] * num;
        last = e.t;

        if (e.begin) {
            num++;
        } else {
            num--;
        }
    }

    printf("%d", ans);

    return 0;
}
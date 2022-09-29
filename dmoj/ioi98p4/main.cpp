/*
 * A c++ program that finds the area and the perimeter of the union of rectangles
 * Written by Juho Kim
 */

#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

class Event {
public:
    int x, y1, y2;
    int t;

    Event(int x, int y1, int y2, int t) {
        this->x = x;
        if (y1 < y2) {
            this->y1 = y1;
            this->y2 = y2;
        } else {
            this->y1 = y2;
            this->y2 = y1;
        }
        this->t = t;
    }
};

int main() {
    int N;
    scanf("%d", &N);

    std::vector<Event> events;
    std::set<int> yvals;

    for (int i = 0; i < N; i++) {
        int xleft, ybottom, xright, ytop;
        scanf("%d%d%d%d", &xleft, &ybottom, &xright, &ytop);

        events.emplace_back(xleft, ybottom, ytop, 1);
        events.emplace_back(xright, ybottom, ytop, -1);

        yvals.insert(ytop);
        yvals.insert(ybottom);
    }

    std::sort(events.begin(), events.end(), [] (Event a, Event b) -> bool {
        return a.x < b.x;
    });

    yvals.insert(-INFINITY);
    yvals.insert(INFINITY);

    std::vector<int> segy(yvals.begin(), yvals.end());
    std::map<int, int> findy;
    int count = 0;
    for (int seg : segy) {
        findy[seg] = count;
        count++;
    }

    std::vector<int> sweep_line(segy.size(), 0);
    int perimeter = 0;

    for (int i = 0; i < events.size();) {
        std::vector<int> past_sweep_line = sweep_line;
        for (int j = 0; j < sweep_line.size() -1; j++) {
            if (bool(sweep_line[j]) != bool(sweep_line[j+1]))
                perimeter += events[i].x - events[i - 1].x;
        }
        int initial_x = events[i].x;
        while (initial_x == events[i].x) {
            for (int j = findy[events[i].y1]; j < findy[events[i].y2]; j++) {
                sweep_line[j] += events[i].t;
            }
            i++;
        }
        for (int j = 0; j < sweep_line.size() -1; j++) {
            if (bool(past_sweep_line[j]) != bool(sweep_line[j]))
                perimeter += segy[j + 1] - segy[j];
        }
    }

    printf("%d", perimeter);

    return 0;
}
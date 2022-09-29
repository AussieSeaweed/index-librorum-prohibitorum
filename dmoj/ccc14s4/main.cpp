#include <bits/stdc++.h>
typedef long long int ll;

class Event {
public:
    ll x, y1, y2, t;

    Event(ll x, ll y1, ll y2, ll t) {
        this->x = x;
        this->y1 = y1;
        this->y2 = y2;
        this->t = t;
    }

    bool operator < (Event e) const {
        return x < e.x;
    }
};

int main() {
    ll N, T;
    scanf("%lld%lld", &N, &T);

    std::vector<Event> events;
    std::set<ll> segy;

    for (ll i = 0; i < N; i++) {
        ll x1, y1, x2, y2, t;
        scanf("%lld%lld%lld%lld%lld", &x1, &y1, &x2, &y2, &t);
        events.emplace_back(x1, y1, y2, t);
        events.emplace_back(x2, y1, y2, -t);
        segy.insert(y1);
        segy.insert(y2);
    }

    std::sort(events.begin(), events.end());
    std::vector<ll> ys(segy.begin(), segy.end());

    std::map<ll, ll> findy;

    ll count = 0;
    for (ll y : segy) {
        findy[y] = count;
        count++;
    }

    std::vector<ll> line(findy.size(), 0);

    ll ans = 0;
    for (ll i = 0; i < events.size(); i++) {
        for (ll j = 0; j < line.size(); j++) {
            if (line[j] >= T) {
                ans += (ys[j+1] - ys[j]) * (events[i].x - events[i-1].x);
            }
        }
        for (ll j = findy[events[i].y1]; j < findy[events[i].y2]; j++) {
            line[j] += events[i].t;
        }
    }

    printf("%lld", ans);

    return 0;
}
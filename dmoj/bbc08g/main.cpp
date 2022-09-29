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

struct Dist {
    int lp = inf, cp = inf, lv = 0;
    bool operator>(const Dist &that) const {
        return lp == that.lp ? (lv == that.lv ? cp > that.cp : lv > that.lv) : lp > that.lp;
    }
    Dist get_modified(int v) {
        Dist ret = *this;

        if (v) {
            ret.lp = ++ret.cp;
            ret.lv = v;
        } else {
            ret.cp++;
        }

        return ret;
    }
};

struct Event1 {
    Dist d;
    pair<int, int> node;
    Event1(Dist d, pair<int, int> &&node) : d{ d }, node{ node } {}
    bool operator>(const Event1 &that) const {
        return d > that.d;
    }
};

struct Event2 {
    Dist d;
    int node;
    Event2(Dist d, int node) : d{ d }, node{ node } {}
    bool operator>(const Event2 &that) const {
        return d > that.d;
    }
};

int N, M;
Dist dist1[100000][2];
Dist dist2[100000];
pair<pair<int, int>, int> pred1[100000][2];
pair<int, int> pred2[100000];
vector<pair<int, int>> graph[100000];
priority_queue<Event1, vector<Event1>, greater<Event1>> pq1;
priority_queue<Event2, vector<Event2>, greater<Event2>> pq2;

void dijkstra1() {
    dist1[0][0].lp = dist1[0][0].cp = dist1[0][1].lp = dist1[0][1].cp = 1;
    pred1[0][0] = pred1[0][1] = {{-1, -1}, -1};
    pq1.emplace(dist1[0][1], make_pair(0, 1));

    while (!pq1.empty()) {
        Event1 e = pq1.top();
        pq1.pop();
        pair<int, int> node_t = e.node;
        int node = node_t.first, t = node_t.second;

        for (pair<int, int> &adj : graph[node]) {
            int other = adj.first, len = adj.second;
            Dist ndist = dist1[node][t].get_modified(len);

            if (dist1[other][1] > ndist) {
                dist1[other][1] = ndist;
                pred1[other][1] = {{node, t}, len};
                pq1.emplace(dist1[other][1], make_pair(other, 1));
            }

            if (dist1[other][0].cp > ndist.cp) {
                dist1[other][0] = ndist;
                pred1[other][0] = {{node, t}, len};
                pq1.emplace(dist1[other][0], make_pair(other, 0));
            }
        }
    }
}

void dijkstra2() {
    dist2[0].lp = dist2[0].cp = 1;
    pred2[0] = {-1, -1};
    pq2.emplace(dist2[0], 0);

    while (!pq2.empty()) {
        Event2 e = pq2.top();
        pq2.pop();
        int node = e.node;

        for (pair<int, int> &adj : graph[node]) {
            int other = adj.first, len = adj.second;
            Dist ndist = dist2[node].get_modified(len);
            if (dist2[other] > ndist) {
                dist2[other] = ndist;
                pred2[other] = {node, len};
                pq2.emplace(dist2[other], other);
            }
        }
    }
}

int main() {
    scan(N);
    scan(M);

    while (M--) {
        int a, b, len;
        scan(a);
        scan(b);
        scan(len);
        graph[a].emplace_back(b, len);
        graph[b].emplace_back(a, len);
    }

    dijkstra1();
    dijkstra2();

    string d;
    vector<int> path;

    if (dist2[N - 1] > dist1[N - 1][1]) {
        int node = N - 1, t = 1;

        while (node != -1) {
            pair<pair<int, int>, int> predecessor = pred1[node][t];
            if (predecessor.second != -1) d.push_back(predecessor.second + '0');
            path.push_back(node);
            node = predecessor.first.first;
            t = predecessor.first.second;
        }
    } else {
        int node = N - 1;

        while (node != -1) {
            if (pred2[node].second != -1) d.push_back(pred2[node].second + '0');
            path.push_back(node);
            node = pred2[node].first;
        }
    }


    int li = 0;
    while (d[li] == '0') li++;
    if (li == d.size()) {
        printf("0\n");
    } else {
        for (int i = li; i < d.size(); i++) printf("%c", d[i]);
    }
    printf("\n%d\n", dist1[N - 1][1].cp);
    for (int node : vector<int>(path.rbegin(), path.rend())) {
        printf("%d ", node);
    }
    printf("\n");


    return 0;
}
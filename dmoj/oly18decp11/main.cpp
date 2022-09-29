#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
struct pair_hash { template <typename T1, typename T2> std::size_t operator()(const std::pair<T1, T2> &p) const { auto h1 = std::hash<T1>{}(p.first); auto h2 = std::hash<T2>{}(p.second); return h1 ^ h2; } };
template<typename T1, typename T2, typename T3> struct triple { T1 first; T2 second; T3 third; triple() : first{}, second{}, third{} {} triple(const T1 &first, const T2 &second, const T3 &third) : first{ first }, second{ second }, third{ third } {} triple(T1 &&first, T2 &&second, T3 &&third) : first{ first }, second{ second }, third{ third } {} };
template<typename T1, typename T2, typename T3, typename T4> struct quad { T1 first; T2 second; T3 third; T4 fourth; quad() : first{}, second{}, third{}, fourth{} {} quad(const T1 &first, const T2 &second, const T3 &third, const T4 &fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} quad(T1 &&first, T2 &&second, T3 &&third, T4 &&fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} };
template<typename T> inline constexpr const T &_min(const T &x,const T &y) { return x < y ? x: y; }
template<typename T> inline constexpr const T &_max(const T &x,const T &y) { return x < y ? y : x; }
template<typename T, typename...Ts> inline constexpr const T &_min(const T &x,const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename...Ts> inline constexpr const T &_max(const T &x,const Ts &...xs) { return _max(x, _max(xs...)); }
template<typename T> using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> using max_priority_queue = std::priority_queue<T>;
inline int ffs(int x) { return __builtin_ffs(x) - 1; }
inline int ctz(int x) { return __builtin_ctz(x); }
inline int clz(int x) { return __builtin_clz(x); }
inline int popcount(int x) { return __builtin_popcount(x); }
inline int ffs(long long x) { return __builtin_ffsll(x) - 1; }
inline int ctz(long long x) { return __builtin_ctzll(x); }
inline int clz(long long x) { return __builtin_clzll(x); }
inline int popcount(long long x) { return __builtin_popcountll(x); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
using namespace std;

vector<pair<int, int>> graph[2][20001];
long long dist[2][200][20001], total;
int N, M, K, Q, x[200], handled;
bool visited[20001];

void dijkstra() {
    for (int i = 0; i < K; i++) {
        {
            fill(dist[0][i], dist[0][i] + N + 1, INF);
            fill(visited, visited + N + 1, false);
            dist[0][i][x[i]] = 0;
            min_priority_queue<pair<long long, int>> pq;
            pq.emplace(0, x[i]);

            while (!pq.empty()) {
                pair<long long, int> event = pq.top();
                pq.pop();
                int node = event.second;

                if (visited[node]) continue;
                visited[node] = true;

                for (pair<int, int> &adj_edge : graph[0][node]) {
                    int other = adj_edge.first;
                    if (dist[0][i][other] > dist[0][i][node] + adj_edge.second) {
                        dist[0][i][other] = dist[0][i][node] + adj_edge.second;
                        pq.emplace(dist[0][i][other], other);
                    }
                }
            }
        }
        {
            fill(dist[1][i], dist[1][i] + N + 1, INF);
            fill(visited, visited + N + 1, false);
            dist[1][i][x[i]] = 0;
            min_priority_queue<pair<long long, int>> pq;
            pq.emplace(0, x[i]);

            while (!pq.empty()) {
                pair<long long, int> event = pq.top();
                pq.pop();
                int node = event.second;

                if (visited[node]) continue;
                visited[node] = true;

                for (pair<int, int> &adj_edge : graph[1][node]) {
                    int other = adj_edge.first;
                    if (dist[1][i][other] > dist[1][i][node] + adj_edge.second) {
                        dist[1][i][other] = dist[1][i][node] + adj_edge.second;
                        pq.emplace(dist[1][i][other], other);
                    }
                }
            }
        }
    }
}

void handle_query(int a, int b) {
    long long minimum_cost = INF;

    for (int i = 0; i < K; i++) {
        minimum_cost = min(minimum_cost, dist[1][i][a] + dist[0][i][b]);
    }

    if (minimum_cost < INF) {
        handled++;
        total += minimum_cost;
    }
}

int main() {
    scan(N);
    scan(M);
    scan(K);
    scan(Q);

    while (M--) {
        int u, v, d;
        scan(u);
        scan(v);
        scan(d);
        graph[0][u].emplace_back(v, d);
        graph[1][v].emplace_back(u, d);
    }

    for (int i = 0; i < K; i++)
        scan(x[i]);

    dijkstra();

    while (Q--) {
        int a, b;
        scan(a);
        scan(b);
        handle_query(a, b);
    }

    printf("%d\n%lld\n", handled, total);

    return 0;
}
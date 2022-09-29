#include <iostream>
#include <vector>
#include <algorithm>

#define COL false
#define ROW true
using namespace std;

int N, M, P, Q;
unsigned long long total_weight = 0;

struct Edge {
    int u, v;
    long long w;
    bool o;

    Edge(int u, int v, long long w, bool o) : u{ u }, v{ v }, w{ w }, o{ o } {}

    bool operator<(Edge that) const {
        return w < that.w;
    }
};

vector<Edge> edges;

struct Union_Find {
    int ids[100001];

    Union_Find(int num) {
        for (int i = 1; i <= num; i++)
            ids[i] = i;
    };

    int root(int node) {
        while (node != ids[node]) {
            ids[node] = ids[ids[node]];
            node = ids[node];
        }

        return node;
    }

    void merge_roots(int r1, int r2) {
        ids[r1] = r2;
    }
};

long long kruskal() {
    sort(edges.begin(), edges.end());

    Union_Find row(N), col(M);

    unsigned long long ret = 0, mst_size = 0, max_size = N * M - 1, row_added = 0, col_added = 0;

    for (int i = 0; i < edges.size() && mst_size != max_size; i++) {
        Edge& e = edges[i];

        if (e.o == ROW) {
            int r1 = row.root(e.u), r2 = row.root(e.v);
            if (r1 != r2) {
                ret += e.w * (M - col_added);
                row.merge_roots(r1, r2);
                row_added++;
                mst_size += M - col_added;
            }
        } else {
            int r1 = col.root(e.u), r2 = col.root(e.v);
            if (r1 != r2) {
                ret += e.w * (N - row_added);
                col.merge_roots(r1, r2);
                col_added++;
                mst_size += N - row_added;
            }
        }
    }

    return ret;
}

int main() {
    scanf("%d%d%d%d", &N, &M, &P, &Q);

    while (P--) {
        int u, v; unsigned long long w;
        scanf("%d%d%llu", &u, &v, &w);
        edges.emplace_back(u, v, w, COL);
        total_weight += w * N;
    }

    while (Q--) {
        int u, v; unsigned long long w;
        scanf("%d%d%llu", &u, &v, &w);
        edges.emplace_back(u, v, w, ROW);
        total_weight += w * M;
    }

    printf("%llu\n", total_weight - kruskal());

    return 0;
}
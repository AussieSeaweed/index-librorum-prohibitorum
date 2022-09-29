#include <bits/stdc++.h>

class Edge {
public:
    int v, w;
    long double rate;

    Edge(int v, int w, long double rate) {
        this->v = v;
        this->w = w;
        this->rate = rate;
    }
};

int N, M;

bool bellmanFord(std::vector<Edge> edges, int source) {
    std::vector<long double> min(N, INFINITY);

    min[source] = 0;

    for (int i = 0; i < N; i++) {
        for (Edge e : edges) {
            if (min[e.w] > min[e.v] + e.rate) {
                min[e.w] = min[e.v] + e.rate;
            }
        }
    }

    return min[source] < -1e-6;
}

int main() {
    scanf("%d%d", &N, &M);

    std::map<std::string, int> strNum;

    int appleIndex;

    for (int i = 0; i < N; i++) {
        std::string str;
        std::cin >> str;
        strNum[str] = i;
        if (str == "APPLES") appleIndex = i;
    }

    std::vector<Edge> edges;

    while (M--) {
        std::string a, b;
        long double c;

        std::cin >> a >> b;

        std::cin >> c;

        c = -log(c);

        edges.emplace_back(strNum[a], strNum[b], c);
    }

    if (bellmanFord(edges, appleIndex)) {
        printf("YA");
    } else {
        printf("NAW");
    }

    return 0;
}
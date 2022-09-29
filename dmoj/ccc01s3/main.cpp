#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, M, A, B;

const int MAX_NODE = 'Z';
int dist[MAX_NODE + 1], pred[MAX_NODE + 1];
bool visited[MAX_NODE + 1];
set<int> graph[MAX_NODE + 1];
vector<pair<int, int>> edges;

void bfs(int source) {
    fill(begin(dist), end(dist), inf);
    fill(begin(visited), end(visited), false);
    queue<int> q;
    q.push(source);
    dist[source] = 0;
    visited[source] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int adj : graph[node]) {
            if (!visited[adj]) {
                dist[adj] = dist[node] + 1;
                pred[adj] = node;
                visited[adj] = true;
                q.push(adj);
            }
        }
    }
}

int main() {
    set<char> nodes;

    while (true) {
        char a, b;
        scanf(" %c%c", &a, &b);
        if (a == '*') break;
        edges.emplace_back(a, b);
        graph[a].insert(b);
        graph[b].insert(a);
        nodes.insert(a);
        nodes.insert(b);
    }

    int count = 0;

    for (const pair<int, int> &edge : edges) {
        graph[edge.first].erase(edge.second);
        graph[edge.second].erase(edge.first);
        bfs(*nodes.begin());
        graph[edge.first].insert(edge.second);
        graph[edge.second].insert(edge.first);
        for (char node : nodes) {
            if (!visited[node]) {
                printf("%c%c\n", edge.first, edge.second);
                count++;
                break;
            }
        }
    }

    printf("There are %d disconnecting roads.\n", count);

    return 0;
}
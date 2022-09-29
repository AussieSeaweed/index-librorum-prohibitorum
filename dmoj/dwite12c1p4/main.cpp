#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <algorithm>

int get_depth(int node, int d, std::vector<std::vector<int>>& graph, std::vector<int>& depth) {
    int returnVal = d;
    depth[node] = d;

    for (int adj : graph[node])
        if (adj && depth[adj] == -1)
            returnVal = std::max(returnVal, get_depth(adj, d + 1, graph, depth));

    depth[node] = returnVal;

    return returnVal;
}

bool all(std::vector<bool>& vec) {
    for (bool b : vec)
        if (!b) return false;
    return true;
}

void count(int node, int& d, std::vector<std::vector<int>>& graph, std::vector<bool>& visited, std::vector<int>& depth) {
    visited[node] = true;

    for (int adj : graph[node]) {
        if (adj && !visited[adj]) {
            count(adj, ++d, graph, visited, depth);

            if (!all(visited))
                d++;
            else
                return;
        }
    }
}

int main() {
    int _ = 5;

    while (_--) {
        int max_depth = -1;

        std::string str;
        std::getline(std::cin, str);
        std::string  s;
        for (char ch : str) {
            if (ch == '(' || ch == ')') {
                s += ' ';
                s += ch;
                s += ' ';
            } else if (ch == ' ') {
                s += "  ";
            } else {
                s += ch;
            }
        }

        std::istringstream in(s);

        std::stack<int> st;
        std::vector<std::vector<int>> graph(1000);
        int i = 1, total = 0;
        st.push(0);

        do {
            std::string token;
            in >> token;

            if (token == "(") {
                int node = i++;
                graph[node].push_back(st.top());
                graph[st.top()].push_back(node);
                st.push(node);
            } else if (token == ")") {
                st.pop();
            } else {
                std::istringstream to_i(token);

                int val;
                to_i >> val;

                total += val;

                int node = i++;

                graph[node].push_back(st.top());
                graph[st.top()].push_back(node);
            }
        } while (st.size() > 1);

        graph.resize(i);

        std::vector<int> depth(i, -1);

        get_depth(1, 0, graph, depth);

        for (int v = 1; v < i; v++) {
            std::sort(graph[v].begin(), graph[v].end(), [=](int a, int b) {
                return depth[a] < depth[b];
            });
        }

        std::vector<bool> visited(i, false);
        visited[0] = true;
        int d = 0;

        count(1, d, graph, visited, depth);

        printf("%d %d\n", d, total);
    }

    return 0;
}
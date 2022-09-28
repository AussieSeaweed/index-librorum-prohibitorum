#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int N, S, T, IS_CIRCUIT;
vector<int> graph[26];
int inbound[26], outbound[26];
char buffer[1000];

bool invalid() {
    S = -1, T = -1;
    IS_CIRCUIT = true;

    for (int i = 0; i < 26; i++) {
        if (inbound[i] != outbound[i]) {
            IS_CIRCUIT = false;
            if (outbound[i] + 1 == inbound[i]) {
                if (T == -1) T = i;
                else return true;
            } else if (outbound[i] == inbound[i] + 1) {
                if (S == -1) S = i;
                else return true;
            } else {
                return true;
            }
        }
    }

    if (IS_CIRCUIT) {
        for (int i = 0; i < 26; i++) {
            if (outbound[i]) {
                S = i;
                break;
            }
        }
    }

    return false;
}

int euler_path() {
    int path_len = 0;

    if (invalid()) return -1;

    stack<int> s;
    s.push(S);

    while (!s.empty()) {
        int node = s.top();

        if (graph[node].empty()) {
            path_len++;
            s.pop();
        } else {
            s.push(graph[node].back());
            graph[node].pop_back();
        }
    }

    return path_len;
}

int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        fill(begin(inbound), end(inbound), 0);
        fill(begin(outbound), end(outbound), 0);
        for_each(begin(graph), end(graph), [] (vector<int>& vec) -> void {
            vec.clear();
        });

        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%s", buffer);
            int len = strlen(buffer);
            int start = buffer[0] - 'a', end = buffer[len - 1] - 'a';
            inbound[end]++, outbound[start]++;
            graph[start].push_back(end);
        }

        printf(euler_path() - 1 == N ? "Ordering is possible.\n" : "The door cannot be opened.\n");
    }
    return 0;
}
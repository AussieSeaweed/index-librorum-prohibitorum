#include <iostream>

std::string raw_tree;
int ptr = 0, X;
int tree[1000], dp[1000][2501], left[1000][2501], right[1000][2501];

void build_tree(int node) {
    while (ptr < raw_tree.size() && (isspace(raw_tree[ptr]) || raw_tree[ptr] == ')')) ptr++;
    if (ptr == raw_tree.size()) return;

    if (raw_tree[ptr] == '(') {
        ptr++;
        build_tree(node * 2);
        build_tree(node * 2 + 1);
    } else {
        int val = raw_tree[ptr++] - '0';
        while (isdigit(raw_tree[ptr])) {
            val = val * 10 + (raw_tree[ptr++] - '0');
        }
        tree[node] = val;
    }
}

void solve(int node) {
    if (tree[node]) {
        for (int x = 0; x <= X; x++) dp[node][x] = tree[node] + x;
    } else {
        solve(node * 2);
        solve(node * 2 + 1);

        for (int x = 0; x <= X; x++) {
            for (int i = 0, j = x; i <= x; i++, j--) {
                left[node][x] = std::max(left[node][x],
                        std::min(dp[node * 2][i], (1 + j) * (1 + j)));
                right[node][x] = std::max(right[node][x],
                                         std::min(dp[node * 2 + 1][i], (1 + j) * (1 + j)));
            }
        }

        for (int x = 0; x <= X; x++) {
            for (int i = 0, j = x; i <= x; i++, j--) {
                dp[node][x] = std::max(dp[node][x],
                        left[node][i] + right[node][j]
                        );
            }
        }
    }
}

int main() {
    std::getline(std::cin, raw_tree);
    scanf("%d", &X);

    build_tree(1);
    solve(1);

    printf("%d", dp[1][X]);
    return 0;
}
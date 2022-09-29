#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

unsigned int N, MOD = 1000000007;

struct Node {
    std::unordered_map<unsigned int, Node *> children;
    unsigned int maxChild = 0;

    ~Node() { for (const std::pair<const unsigned int, Node *> &pair: children) delete pair.second; }
} *root;

unsigned int solve(Node *node) {
    unsigned int count = (1 + node->maxChild - node->children.size()) % MOD;

    for (const std::pair<const unsigned int, Node *> &pair: node->children)
        count = (count + solve(pair.second)) % MOD;

    return count;
}

int main() {
    for (int t = 0; t < 10; ++t) {
        std::cin >> N;
        root = new Node;

        while (N--) {
            std::string input;
            std::cin >> input;

            if (!input.empty())
                input[0] += 1;

            Node *node = root;

            for (std::string::size_type lo = 0, hi = input.find('.');
                 lo != std::string::npos;
                 lo = (hi == std::string::npos ? hi : hi + 1), hi = input.find('.', lo)) {
                unsigned int y = std::stoi(input.substr(lo, hi - lo));

                if (!node->children.count(y))
                    node->children[y] = new Node;
                node->maxChild = std::max(node->maxChild, y);
                node = node->children[y];
            }
        }

        std::cout << solve(root) - 1 << std::endl;
        delete root;
    }
    return 0;
}
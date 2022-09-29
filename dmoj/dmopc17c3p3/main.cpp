#include <iostream>
#include <vector>
#include <map>
#include <limits>

unsigned int n, S[20];
std::map<unsigned int, std::vector<unsigned int>> masks;

int main() {
    std::cin >> n;

    for (unsigned int i = 0; i < n; ++i)
        std::cin >> S[i];

    for (unsigned int i = 1; i < (1u << n); ++i) {
        unsigned int sum = 0;

        for (unsigned int j = 0; j < n; ++j)
            if (i & (1 << j))
                sum += S[j];

        masks[sum].push_back(i);
    }

    unsigned int difference = std::numeric_limits<unsigned int>::max();
    std::pair<unsigned int, unsigned int> subsets;

    for (auto begin = masks.begin(); begin != masks.end(); ++begin) {
        for (unsigned int i : begin->second) {
            for (auto end = begin; end != masks.end() && end->first - begin->first < difference; ++end) {
                for (unsigned int j : end->second) {
                    if (!(i & j)) {
                        difference = std::min(difference, end->first - begin->first);
                        subsets = std::make_pair(i, j);
                        break;
                    }
                }
            }
        }
    }

    for (unsigned int i = 0; i < n; ++i)
        if (subsets.first & (1 << i))
            std::cout << i + 1 << ' ';
    std::cout << std::endl;

    for (unsigned int i = 0; i < n; ++i)
        if (subsets.second & (1 << i))
            std::cout << i + 1 << ' ';
    std::cout << std::endl;

    return 0;
}
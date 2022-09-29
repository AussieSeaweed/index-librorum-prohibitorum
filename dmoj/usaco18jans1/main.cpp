#include <iostream>
#include <map>

unsigned int N;
std::pair<unsigned int, unsigned int> intervals[100005];
std::map<unsigned int, unsigned int> counts, ones;

int main() {
    std::cin >> N;

    for (unsigned int i = 0; i < N; ++i) {
        std::cin >> intervals[i].first >> intervals[i].second;

        ++counts[intervals[i].first];
        --counts[intervals[i].second];
    }

    unsigned int total = 0;

    for (auto it1 = counts.begin(), it2 = ++counts.begin(); it2 != counts.end(); ++it1, ++it2) {
        it2->second += it1->second;
        ones[it2->first] = ones[it1->first];

        if (it1->second)
            total += it2->first - it1->first;
        if (it1->second == 1)
            ones[it2->first] += it2->first - it1->first;
    }

    unsigned int time = 0;

    for (unsigned int i = 0; i < N; ++i)
        time = std::max(time, total - (ones[intervals[i].second] - ones[intervals[i].first]));

    std::cout << time << std::endl;

    return 0;
}
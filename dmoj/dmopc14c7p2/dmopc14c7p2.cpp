#include <iostream>
#include <algorithm>

int N, levels[1000];

int main() {
    std::cin >> N;

    for (int i = 0; i < N; ++i)
        std::cin >> levels[i];

    auto [min_element, max_element] = std::minmax_element(levels, levels + N);

    bool unknown = false;

    for (int *it = min_element; it != max_element && !unknown; ++it)
        if (*it > *(it + 1))
            unknown = true;

    if (unknown)
        std::cout << "unknown" << std::endl;
    else
        std::cout << *max_element - *min_element << std::endl;

    return 0;
}
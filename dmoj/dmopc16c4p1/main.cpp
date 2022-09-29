#include <unordered_set>
#include <iostream>

int N;
std::unordered_set<unsigned long long> base2s;

int main() {
    for (int i = 0; i < 63; ++i)
        base2s.insert(1ull << i);

    std::cin >> N;

    while (N--) {
        unsigned long long n;
        std::cin >> n;

        if (base2s.count(n))
            std::cout << 'T' << std::endl;
        else
            std::cout << 'F' << std::endl;
    }

    return 0;
}
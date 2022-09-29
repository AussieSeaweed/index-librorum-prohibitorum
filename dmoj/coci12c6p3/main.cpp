#include <iostream>
#include <unordered_set>

int N, A[5000], count;
std::unordered_set<int> sums;

int main() {
    std::cin >> N;

    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];

        bool good = false;

        for (int j = 0; j < i && !good; ++j)
            good = sums.count(A[i] - A[j]);

        count += good;

        for (int j = 0; j <= i; ++j)
            sums.insert(A[i] + A[j]);
    }

    std::cout << count << std::endl;

    return 0;
}
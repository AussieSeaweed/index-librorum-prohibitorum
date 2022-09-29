#include <iostream>
#include <map>
#include <list>

unsigned int n, k, A[10], V[100000][10];
std::multimap<unsigned int, unsigned int> indices[10];

unsigned int update() {
    std::list<unsigned int> solved;

    for (unsigned int j = 0; j < k; ++j) {
        auto it = indices[j].begin();

        while (it != indices[j].end()) {
            auto [skill, i] = *it;

            if (skill <= A[j]) {
                it = indices[j].erase(it);

                if (j + 1 == k) {
                    solved.push_back(i);
                } else
                    indices[j + 1].emplace(V[i][j + 1], i);
            } else
                break;
        }
    }

    for (unsigned int i : solved)
        for (unsigned int j = 0; j < k; ++j)
            A[j] += V[i][j];

    return solved.size();
}

int main() {
    std::cin >> n >> k;

    for (unsigned int j = 0; j < k; ++j) {
        std::cin >> A[j];
    }

    for (unsigned int i = 0; i < n; ++i) {
        for (unsigned int j = 0; j < k; ++j)
            std::cin >> V[i][j];

        indices[0].emplace(V[i][0], i);
    }

    unsigned int count = 0, solved;

    while ((solved = update()))
        count += solved;

    std::cout << count << std::endl;

    return 0;
}
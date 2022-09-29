#include <iostream>
#include <vector>

struct Cars {
    int capacity;
    std::vector<int> counts;

    void getOff(double P) {
        for (int &count: counts)
            count = count - ((int) (count * P));
    }

    void getOn(int N) {
        for (int &count: counts) {
            if (N == 0) break;

            int delta = std::min(N, capacity - count);
            count += delta;
            N -= delta;
        }

        while (N > 0) {
            int delta = std::min(N, capacity);
            counts.push_back(delta);
            N -= delta;
        }
    }
} oldCars{132}, newCars{251};

int S, N;
double P;

int main() {
    std::cin >> S;

    while (S--) {
        std::cin >> N >> P;
        P /= 100;

        oldCars.getOff(P), oldCars.getOn(N);
        newCars.getOff(P), newCars.getOn(N);
    }

    std::cout << oldCars.counts.size() - newCars.counts.size() << std::endl;

    return 0;
}
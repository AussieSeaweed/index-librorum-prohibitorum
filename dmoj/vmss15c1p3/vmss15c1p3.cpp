#include <iostream>

long long xh, yh, xs, ys, n;

long long sign(long long x) {
    return x / std::abs(x);
}

int main() {
    std::cin >> xh >> yh >> xs >> ys >> n;

    long long count = 0;

    while (n--) {
        long long A, B, C;
        std::cin >> A >> B >> C;
        count += sign(A * xh + B * yh + C) != sign(A * xs + B * ys + C);
    }

    std::cout << count << std::endl;

    return 0;
}
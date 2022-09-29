#include <iostream>
#include <vector>

int gcd(int n, int m) {
    while (m) {
        int temp = m;
        m = n % m;
        n = temp;
    }

    return n;
}

int N, A[18][100000];

int query(int begin, int end) {
    int n = end - begin, res = 0;

    for (int i = 17; i >= 0; --i) {
        if (n >= (1 << i)) {
            res = gcd(res, A[i][begin]);
            n -= (1 << i);
            begin += (1 << i);
        }
    }

    return res;
}

int main() {
    std::cin >> N;

    for (int i = 0; i < N; ++i)
        std::cin >> A[0][i];

    for (int i = 1; i < 18; ++i)
        for (int j = 0; j + (1 << i) <= N; ++j)
            A[i][j] = gcd(A[i - 1][j], A[i - 1][j + (1 << (i - 1))]);

    int optimum = 0;

    for (int i = 0; i < N; ++i)
        optimum = std::max(optimum, gcd(query(0, i), query(i + 1, N)));

    std::cout << optimum << std::endl;

    return 0;
}
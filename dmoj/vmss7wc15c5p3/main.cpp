#include <iostream>

constexpr int DIMENSION = 2001, MODULUS = 1000000007;
int bits[DIMENSION][DIMENSION];

void update(int bit[], int i, int delta) {
    for (; i < DIMENSION; i += i & -i)
        bit[i] += delta;
}

int query(const int bit[], int i) {
    int sum = 0;

    for (; i; i -= i & -i)
        sum += bit[i];

    return sum;
}

int query(const int bit[], int i, int j) {
    return query(bit, j) - query(bit, i - 1);
}

std::pair<int, int> diagonalize(int r, int c) {
    return std::make_pair(r + c - 1, c);
}

int main() {
    int N, sum = 0;
    std::cin >> N;

    while (N--) {
        int t, r, c, a;
        std::cin >> t >> r >> c >> a;

        auto[i, j] = diagonalize(r, c);

        switch (t) {
            case 1:
                update(bits[i], j, a);
                break;
            case 2:
                sum = (sum + query(bits[i], j, j + a)) % MODULUS;
                break;
            default:
                break;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
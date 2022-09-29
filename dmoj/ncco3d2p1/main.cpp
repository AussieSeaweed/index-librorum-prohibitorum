#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

auto len = (unsigned int) (pow(2.0, ceil(log(50000.) / log(2.)) + 1));
vector<int> elems(50001);
vector<int> minimum(len);
vector<int> maximum(len);
int N, Q;

void build(int index, int lo, int hi) {
    if (lo == hi) {
        minimum[index] = maximum[index] = elems[lo];
    } else {
        int left_index = index * 2, right_index = index * 2 + 1, mid = (lo + hi) / 2;
        build(left_index, lo, mid);
        build(right_index, mid + 1, hi);

        minimum[index] = min(minimum[left_index], minimum[right_index]);
        maximum[index] = max(maximum[left_index], maximum[right_index]);
    }
}

pair<int, int> range(int index, int lo, int hi, int left, int right) {
    if (right < lo || hi < left) return {-1, -1};
    if (left <= lo && hi <= right) return {minimum[index], maximum[index]};

    pair<int, int> leftr = range(index * 2, lo, (lo + hi) / 2, left, right);
    pair<int, int> rightr = range(index * 2 + 1, (lo + hi) / 2 + 1, hi, left, right);

    if (leftr.first == -1) return rightr;
    if (rightr.first == -1) return leftr;

    return {min(leftr.first, rightr.first), max(leftr.second, rightr.second)};
};

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; i++)
        scanf("%d", &elems[i]);
    build(1, 1, N);
    while (Q--) {
        int left, right;
        scanf("%d%d", &left, &right);
        if (left == right) printf("0\n");
        else {
            pair<int, int> r = range(1, 1, N, left, right);
            printf("%d\n", r.second - r.first);
        }
    }
    return 0;
}
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int N; double score;
pair<double, double> sr[100000];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lf%lf", &sr[i].first, &sr[i].second);
    }
    sort(sr, sr + N, std::greater<>());
    scanf("%lf", &score);

    long long smallest = 1;

    for (int i = 0; i < N; i++) {
        long long latest = (long long) (sr[i].second + round(sr[i].second - smallest));
        if (sr[i].first == score) {
            printf("%lld\n%lld", smallest, latest);
            return 0;
        }
        smallest = latest + 1;
    }

    return 0;
}
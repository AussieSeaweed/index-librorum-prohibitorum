#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>

using namespace std;

vector<int> elems;
vector<int> gcd;
vector<int> count;
vector<int> minimum;

int get_gcd(int a, int b) {
    while (b) {
        int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

void init_tree(int N) {
    elems.resize(N);
    unsigned int len = (unsigned int) (pow(2.0, ceil(log((double) N) / log(2.0)) + 1));
    gcd.resize(len);
    count.resize(len);
    minimum.resize(len);
}

void build(int index, int lo, int hi) {
    if (lo == hi) {
        gcd[index] = elems[lo - 1];
        count[index] = 1;
        minimum[index] = elems[lo - 1];
    } else {
        int lefti = index * 2, righti = index * 2 + 1;
        build(lefti, lo, (lo + hi) / 2);
        build(righti, (lo + hi) / 2 + 1, hi);

        gcd[index] = get_gcd(gcd[lefti], gcd[righti]);
        count[index] = (gcd[index] == gcd[lefti] ? count[lefti] : 0) +
                (gcd[index] == gcd[righti] ? count[righti] : 0);
        minimum[index] = min(minimum[lefti], minimum[righti]);
    }
}

void update(int index, int lo, int hi, int elem, int i) {
    if (i < lo || hi < i) return;

    if (lo == hi) {
        gcd[index] = elem;
        minimum[index] = elem;
        elems[i - 1] = elem;
    } else {
        int lefti = index * 2, righti = index * 2 + 1;
        update(lefti, lo, (lo + hi) / 2, elem, i);
        update(righti, (lo + hi) / 2 + 1, hi, elem, i);

        gcd[index] = get_gcd(gcd[lefti], gcd[righti]);
        count[index] = (gcd[index] == gcd[lefti] ? count[lefti] : 0) +
                (gcd[index] == gcd[righti] ? count[righti] : 0);
        minimum[index] = min(minimum[lefti], minimum[righti]);
    }
}

tuple<int, int, int> query(int index, int lo, int hi, int left, int right) {
    if (right < lo || hi < left) return {-1, -1, -1};
    if (left <= lo && hi <= right) return {gcd[index], count[index], minimum[index]};

    tuple<int, int, int> leftv = query(index * 2, lo, (lo + hi) / 2, left, right);
    tuple<int, int, int> rightv = query(index * 2 + 1, (lo + hi) / 2 + 1, hi, left, right);

    if (get<0>(leftv) == -1) return rightv;
    if (get<0>(rightv) == -1) return leftv;

    int gcd = get_gcd(get<0>(leftv), get<0>(rightv));
    int count = (gcd == get<0>(leftv) ? get<1>(leftv) : 0) +
            (gcd == get<0>(rightv) ? get<1>(rightv) : 0);
    int minimum = min(get<2>(leftv), get<2>(rightv));

    return {gcd, count, minimum};
};

int main() {
    int N, Q;
    scanf("%d%d", &N, &Q);
    init_tree(N);
    for (int i = 0; i < N; i++)
        scanf("%d", &elems[i]);
    build(1, 1, N);
    while (Q--) {
        char T;
        int a, b;
        scanf(" %c%d%d", &T, &a, &b);
        if (T == 'C') {
            update(1, 1, N, b, a);
        } else if (T == 'M') {
            printf("%d\n", get<2>(query(1, 1, N, a, b)));
        } else if (T == 'G') {
            printf("%d\n", get<0>(query(1, 1, N, a, b)));
        } else if (T == 'Q') {
            printf("%d\n", get<1>(query(1, 1, N, a, b)));
        }
    }
    return 0;
}
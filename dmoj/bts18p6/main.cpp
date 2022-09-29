#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct Porcupine {
    long long l, r, a, b, c;

    Porcupine(long long l, long long r, long long a, long long b, long long c) : l{ l }, r{ r }, a{ a }, b{ b }, c{ c } {}
};

struct END_ORDER {
    bool operator()(Porcupine *a, Porcupine *b) {
        return a->r > b->r;
    }
};

struct START_ORDER {
    bool operator()(Porcupine *a, Porcupine *b) {
        return a->l < b->l;
    }
};

priority_queue<Porcupine *, vector<Porcupine *>, END_ORDER> pq;
Porcupine *p[100000];
int N, T;


int main() {
    scanf("%d%d", &N, &T);

    for (int i = 0; i < N; i++) {
        long long l, r, a, b, c;
        scanf("%lld%lld%lld%lld%lld", &l, &r, &a, &b, &c);
        p[i] = new Porcupine(l, r, a, b, c);
    }

    sort(p, p + N, START_ORDER());
    long long a = 0, b = 0, c = 0, bl = 0, al2 = 0, twoal = 0;

    for (int i = 0, t = 1; t <= T; t++) {
        while (i < N && p[i]->l <= t) {
            pq.push(p[i]);
            a += p[i]->a;
            b += p[i]->b;
            c += p[i]->c;
            bl += p[i]->b * p[i]->l;
            al2 += p[i]->a * p[i]->l * p[i]->l;
            twoal += 2 * p[i]->a * p[i]->l;
            i++;
        }

        while (!pq.empty() && pq.top()->r < t) {
            Porcupine *porcupine = pq.top();
            a -= porcupine->a;
            b -= porcupine->b;
            c -= porcupine->c;
            bl -= porcupine->b * porcupine->l;
            al2 -= porcupine->a * porcupine->l * porcupine->l;
            twoal -= 2 * porcupine->a * porcupine->l;
            pq.pop();
        }

        printf("%lld ", a * t * t - twoal * t + al2 + b * t - bl + c);
    }

    printf("\n");

    return 0;
}
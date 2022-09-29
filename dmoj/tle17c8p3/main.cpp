#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

vector<long long> palindromes;
long long N, M, K, Q;

void insert(long long num, int len) {
    if (len > 10) return;
    if (num % 10 && num % K == 0) palindromes.push_back(num);
    long long nb = 10;
    for (int i = 0; i < len; i++)
        nb *= 10;
    for (int i = 0; i <= 9; i++) {
        insert(i * nb + num * 10 + i, len + 2);
    }
}

void insert_palindromes() {
    for (int i = 0; i <= 9; i++) {
        insert(i, 1);
        insert(i * 11, 2);
    }
    sort(palindromes.begin(), palindromes.end());
}

int main() {
    scan(Q);
    scan(K);

    insert_palindromes();

    while (Q--) {
        long long N, M;
        scan(N);
        scan(M);
        printf("%d\n", upper_bound(palindromes.begin(), palindromes.end(), M) - lower_bound(palindromes.begin(), palindromes.end(), N));
    }

    return 0;
}
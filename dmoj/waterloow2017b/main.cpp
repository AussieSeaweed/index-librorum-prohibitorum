#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, K, cnt[26];
char A[2002];

int main() {
    scan(N);
    scan(K);

    scanf("%s", A);

    if (K > N) {
        printf("WRONGANSWER\n");
        return 0;
    }

    for (int i = 0; i < N; i++)
        cnt[A[i] - 'a']++;

    char fill_character = -1;
    int freq = inf;

    for (char ch = 0; ch < 26; ch++) {
        if (cnt[ch] < freq) {
            fill_character = ch + 'a';
            freq = cnt[ch];
        }
    }

    if (K < freq) {
        printf("WRONGANSWER\n");
        return 0;
    }

    for (int i = 0; i < N - K; i++)
        printf("%c", fill_character);

    for (int i = 0; i < K; i++)
        printf("%c", A[i]);

    return 0;
}
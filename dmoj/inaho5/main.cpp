#include <bits/stdc++.h>

using namespace std;

int main() {
    unsigned long long sum = 0;
    
    int N;
    scanf("%d", &N);
    
    while (N--) {
        long long num;
        scanf("%lld", &num);
        
        sum += -num;
    }
    
    if (sum != 0) printf("-");
    printf("%lu", sum);
    
    return 0;
}
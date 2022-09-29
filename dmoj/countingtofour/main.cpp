#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

string str_val[] {
    "", "one", "two", "three", "four",
    "five", "six", "seven", "eight", "nine",
    "ten", "eleven", "twelve", "thirteen", "fourteen",
    "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
};

string tens_str_val[] {
    "",
    "ten",
    "twenty",
    "thirty",
    "forty",
    "fifty",
    "sixty",
    "seventy",
    "eighty",
    "ninety",
};

string to_str(int i) {
    if (i >= 1000000000) {
        return to_str(i / 1000000000) + "billion" + to_str(i % 1000000000);
    } else if (i >= 1000000) {
        return to_str(i / 1000000) + "million" + to_str(i % 1000000);
    } else if (i >= 1000) {
        return to_str(i / 1000) + "thousand" + to_str(i % 1000);
    } else if (i >= 100) {
        return to_str(i / 100) + "hundred" + to_str(i % 100);
    } else if (i >= 20) {
        return tens_str_val[i / 10] + to_str(i % 10);
    } else {
        return str_val[i];
    }
}

int main() {
    int N;
    scan(N);

    do {
        N = to_str(N).size();
        printf("%d\n", N);
    } while (N != 4);

    return 0;
}
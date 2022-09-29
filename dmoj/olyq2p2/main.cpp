#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
template<typename T>constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T>constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

long long  digits[19], dp[19][7][9][1 << 8], modthousand,
        s7mul[] {1, 3, 2, 6, 4, 5, 1, 3, 2, 6, 4, 5, 1, 3, 2, 6, 4, 5, 1, 3, 2, 6, 4, 5};

long long solve(int index, bool tight, int s7, int s, int bm) {
    if (!tight && ~dp[index][s7][s][bm]) return dp[index][s7][s][bm];

    if (index == 0) {
        return tight ? digits[0] + 1 : dp[index][s7][s][bm] = 10;
    } else if (index == 1) {
        if (!tight && ~dp[index][s7][s][bm]) return dp[index][s7][s][bm];
        long long ret = 0;
        int lim = tight ? modthousand : 99; // in this case modthousand = num % 100

        for (int num = 0; num <= lim; num++) {
            int ones = num % 10, tens = num / 10 % 10;
            int sum = (s + ones + tens) % 9;
            int bitmask = bm;
            if (ones >= 2) bitmask |= (1 << (ones - 2));
            if (tens >= 2) bitmask |= (1 << (tens - 2));
            int special7 = (s7 + s7mul[1] * tens + s7mul[0] * ones) % 7;
            bool valid = true;

            for (int digit = 2; digit <= 9 && valid; digit++) {
                if (bitmask & (1 << (digit - 2))) {
                    if (digit == 2) {
                        valid = ones % 2 == 0;
                    } else if (digit == 3) {
                        valid = sum % 3 == 0;
                    } else if (digit == 4) {
                        valid = (num) % 4 == 0;
                    } else if (digit == 5) {
                        valid = ones == 5 || ones == 0;
                    } else if (digit == 6) {
                        valid = ones % 2 == 0 && sum % 3 == 0;
                    } else if (digit == 7) {
                        valid = special7 == 0;
                    } else if (digit == 8) {
                        valid = num % 8 == 0;
                    } else if (digit == 9) {
                        valid = sum == 0;
                    }
                }
            }

            ret += valid;
        }

        if (!tight) dp[index][s7][s][bm] = ret;

        return ret;
    } if (index == 2) {
        if (!tight && ~dp[index][s7][s][bm]) return dp[index][s7][s][bm];
        long long  ret = 0;
        int lim = tight ? modthousand : 999;

        for (int num = 0; num <= lim; num++) {
            int ones = num % 10, tens = num / 10 % 10, hundreds = num / 100;
            int sum = (s + ones + tens + hundreds) % 9;
            int bitmask = bm;
            if (ones >= 2) bitmask |= (1 << (ones - 2));
            if (tens >= 2) bitmask |= (1 << (tens - 2));
            if (hundreds >= 2) bitmask |= (1 << (hundreds - 2));
            int special7 = (s7 + s7mul[2] * hundreds + s7mul[1] * tens + s7mul[0] * ones) % 7;
            bool valid = true;

            for (int digit = 2; digit <= 9 && valid; digit++) {
                if (bitmask & (1 << (digit - 2))) {
                    if (digit == 2) {
                        valid = ones % 2 == 0;
                    } else if (digit == 3) {
                        valid = sum % 3 == 0;
                    } else if (digit == 4) {
                        valid = (num) % 4 == 0;
                    } else if (digit == 5) {
                        valid = ones == 5 || ones == 0;
                    } else if (digit == 6) {
                        valid = ones % 2 == 0 && sum % 3 == 0;
                    } else if (digit == 7) {
                        valid = special7 == 0;
                    } else if (digit == 8) {
                        valid = num % 8 == 0;
                    } else if (digit == 9) {
                        valid = sum == 0;
                    }
                }
            }

            ret += valid;
        }

        if (!tight) dp[index][s7][s][bm] = ret;

        return ret;
    } else {
        long long ret = 0;

        int lim = tight ? digits[index] : 9;
        for (int digit = 0; digit <= lim; digit++) {
            ret += solve(index - 1, digit == lim && tight, (s7 + s7mul[index] * digit) % 7,
                                                 (s + digit) % 9, digit >= 2 ? bm | (1 << (digit - 2)) : bm);
        }

        if (!tight) dp[index][s7][s][bm] = ret;

        return ret;
    }
}

long long solve(long long num) {
    if (num == 0) return 1;
    modthousand = num % 1000;
    int i = 0;
    while (num) {
        digits[i++] = num % 10;
        num /= 10;
    }
    return solve(i - 1, true, 0, 0, 0);
}

int main() {
    memset(dp, -1, sizeof dp);
    int T;
    scan(T);
    while (T--) {
        long long l, r;
        scan(l);
        scan(r);
        printf("%lld\n", solve(r) - solve(l - 1));
    }
    return 0;
}
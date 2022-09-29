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

int N;

string square[36];

bool is_latin() {
    char marked[128];

    for (int r = 0; r < N; r++) {
        for (int i = 0; i < 128; i++)
            marked[i] = false;

        for (int c = 0; c < N; c++) {
            if (marked[square[r][c]])
                return false;
            marked[square[r][c]] = true;
        }
    }

    for (int c = 0; c < N; c++) {
        for (int i = 0; i < 128; i++)
            marked[i] = false;

        for (int r = 0; r < N; r++) {
            if (marked[square[r][c]])
                return false;
            marked[square[r][c]] = true;
        }
    }

    return true;
}

bool is_reduced() {
    for (int r = 0; r < N - 1; r++)
        if (square[r][0] > square[r + 1][0]) return false;

    for (int c = 0; c < N - 1; c++)
        if (square[0][c] > square[0][c + 1]) return false;

    return true;
}

int main() {
    scan(N);

    for (int i = 0; i < N; i++)
        cin >> square[i];

    if (is_latin()) {
        if (is_reduced()) {
            printf("Reduced\n");
        } else {
            printf("Latin\n");
        }
    } else {
        printf("No\n");
    }

    return 0;
}
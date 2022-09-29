#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;



int main() {
    int N;
    scan(N);

    while (N--) {
        string str[3];
        cin >> str[0] >> str[1] >> str[2];
        sort(str, str + 3, [] (string &a, string &b) -> bool {
            return a.size() < b.size();
        });

        bool found = false;

        for (int i = 0; i < 3 && !found; i++)
            for (int j = i + 1; j < 3 && !found; j++)
                if (str[i] == str[j].substr(0, str[i].size()) || str[i] == str[j].substr(str[j].size() - str[i].size(), str[i].size())) {
                    printf("No\n");
                    found = true;
                }

        if (!found)
            printf("Yes\n");
    }

    return 0;
}
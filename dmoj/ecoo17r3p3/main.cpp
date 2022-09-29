#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, x[100], y[100];

double solve(vector<int> &pts) {
    double x_sum = 0, x2_sum = 0;

    for (int index : pts) {
        x_sum += x[index];
        x2_sum += x[index] * x[index];
    }

    double x_loc = x_sum / pts.size(), x_ans = pts.size() * x_loc * x_loc - 2 * x_loc * x_sum + x2_sum;

    double y_sum = 0, y2_sum = 0;

    for (int index : pts) {
        y_sum += y[index];
        y2_sum += y[index] * y[index];
    }

    double y_loc = y_sum / pts.size(), y_ans = pts.size() * y_loc * y_loc - 2 * y_loc * (y_sum) + y2_sum;

    return x_ans + y_ans;
}

double sqr_dist(int i, int j) {
    double dx = x[i] - x[j], dy = y[i] - y[j];
    return dx * dx + dy * dy;
}

int main() {
    int t = 10;
    while (t--) {
        int N;
        scan(N);
        for (int i = 0; i < N; i++) {
            scan(x[i]);
            scan(y[i]);
        }

        double ans = inf;

        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                vector<int> a, b;
                for (int k = 0; k < N; k++) {
                    if (sqr_dist(i, k) < sqr_dist(j, k)) {
                        a.push_back(k);
                    } else {
                        b.push_back(k);
                    }
                }
                ans = min(ans, solve(a) + solve(b));
            }
        }

        printf("%.0lf\n", ans);
    }
    return 0;
}
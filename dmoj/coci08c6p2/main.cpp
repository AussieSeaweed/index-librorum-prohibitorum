#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;



int main() {
    int x, y;
    scan(x);
    scan(y);

    double total = 250 * 250 / 2., difference = INF;
    pair<double, double> ans;

    if (!x) {
        for (double i = 0.; i <= 250.; i += 0.005) {
            double area, cur_dif;

            area = i * y / 2.;
            cur_dif = abs(total - 2 * area);

            if (cur_dif < difference) {
                difference = cur_dif;
                ans = {i, 0};
            }

            area = (250 - y) * (-i + 250) / 2.;
            cur_dif = abs(total - 2 * area);

            if (cur_dif < difference) {
                difference = cur_dif;
                ans = {-i + 250, i};
            }
        }
    } else if (!y) {
        for (double i = 0.; i <= 250.; i += 0.005) {
            double area, cur_dif;

            area = i * x / 2.;
            cur_dif = abs(total - 2 * area);

            if (cur_dif < difference) {
                difference = cur_dif;
                ans = {0, i};
            }

            area = (250 - x) * (-i + 250) / 2.;
            cur_dif = abs(total - 2 * area);

            if (cur_dif < difference) {
                difference = cur_dif;
                ans = {i, -i + 250};
            }
        }
    } else {
        for (double i = 0.; i <= 250.; i += 0.005) {
            double area, cur_dif;

            area = y * (250 - i) / 2.;
            cur_dif = abs(total - 2 * area);

            if (cur_dif < difference) {
                difference = cur_dif;
                ans = {i, 0};
            }

            area = x * (250 - i) / 2.;
            cur_dif = abs(total - 2 * area);

            if (cur_dif < difference) {
                difference = cur_dif;
                ans = {0, i};
            }
        }
    }

    printf("%.2lf %.2lf", ans.first, ans.second);

    return 0;
}
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
template<typename T> inline constexpr const T&_min(const T&x,const T&y) {return x<y?x:y;}
template<typename T> inline constexpr const T&_max(const T&x,const T&y) {return x<y?y:x;}
template<typename T,typename...Ts> inline constexpr const T&_min(const T&x,const Ts&...xs) {return _min(x,_min(xs...));}
template<typename T,typename...Ts> inline constexpr const T&_max(const T&x,const Ts&...xs) {return _max(x,_max(xs...));}
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

struct Equation {
    vector<double> coefficients;
    int degree;

    Equation(int degree, vector<double> &coefficients) : degree{ degree }, coefficients{ coefficients } {}

    double eval(double x) {
        double ret = 0, p = 1;
        for (int i = coefficients.size() - 1; i >= 0; i--) {
            ret += coefficients[i] * p;
            p *= x;
        }
        return ret;
    }

    Equation get_derivative() {
        vector<double> nc(coefficients);
        nc.pop_back();
        for (int p = degree, i = 0; p > 0; p--, i++) {
            nc[i] *= p;
        }
        return {degree - 1, nc};
    }

    vector<double> get_roots() {
        if (degree == 1) {
            return {-coefficients[1] / coefficients[0]};
        } else {
            vector<double> roots;
            vector<double> roots_of_derivative = get_derivative().get_roots();
            roots_of_derivative.push_back(150);
            double prev_x = -150;
            for (double next_x : roots_of_derivative) {
                double lo = prev_x, hi = next_x;
                while (hi - lo > 1e-1) {
                    double m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
                    double v1 = abs(eval(m1)), v2 = abs(eval(m2));
                    if (v1 > v2) {
                        lo = m1;
                    } else {
                        hi = m2;
                    }
                }
                roots.push_back(lo);
                prev_x = next_x;
            }
            return roots;
        }
    }
};

int N;

int main() {
    scan(N);
    while (N--) {
        int d;
        scan(d);
        vector<double> coefficients(d + 1);
        for (int i = 0; i <= d; i++) {
            long long c;
            scan(c);
            coefficients[i] = c;
        }
        Equation eqn(d, coefficients);
        for (double x : eqn.get_roots()) {
            printf("%lld ", (long long) round(x));
        }
        printf("\n");
    }
    return 0;
}
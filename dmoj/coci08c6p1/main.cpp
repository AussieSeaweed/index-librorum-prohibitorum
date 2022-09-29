#include <bits/stdc++.h>
#include <bits/extc++.h>
#define pscan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
#define scan(x) do{while((x=getchar())<'-'); _ssign=x=='-'; if(_ssign) while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0'); x=_ssign?-x:x;}while(0)
char _; bool _ssign;
struct pair_hash { template <typename T1, typename T2> std::size_t operator()(const std::pair<T1, T2> &p) const { auto h1 = std::hash<T1>{}(p.first); auto h2 = std::hash<T2>{}(p.second); return h1 ^ h2; } };
template<typename T1, typename T2, typename T3> struct triple { T1 first; T2 second; T3 third; triple() : first{}, second{}, third{} {} triple(const T1 &first, const T2 &second, const T3 &third) : first{ first }, second{ second }, third{ third } {} triple(T1 &&first, T2 &&second, T3 &&third) : first{ first }, second{ second }, third{ third } {} };
template<typename T1, typename T2, typename T3, typename T4> struct quad { T1 first; T2 second; T3 third; T4 fourth; quad() : first{}, second{}, third{}, fourth{} {} quad(const T1 &first, const T2 &second, const T3 &third, const T4 &fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} quad(T1 &&first, T2 &&second, T3 &&third, T4 &&fourth) : first{ first }, second{ second }, third{ third }, fourth{ fourth } {} };
template<typename T> using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template<typename T> using max_priority_queue = std::priority_queue<T>;
inline int ffs(int x) { return __builtin_ffs(x) - 1; }
inline int ctz(int x) { return __builtin_ctz(x); }
inline int clz(int x) { return __builtin_clz(x); }
inline int popcount(int x) { return __builtin_popcount(x); }
inline int ffs(long long x) { return __builtin_ffsll(x) - 1; }
inline int ctz(long long x) { return __builtin_ctzll(x); }
inline int clz(long long x) { return __builtin_clzll(x); }
inline int popcount(long long x) { return __builtin_popcountll(x); }
template<typename T> inline constexpr const T &_min(const T &x, const T &y) { return x < y ? x: y; }
template<typename T> inline constexpr const T &_max(const T &x, const T &y) { return x < y ? y : x; }
template<typename T, typename...Ts> inline constexpr const T &_min(const T &x, const Ts &...xs) { return _min(x, _min(xs...)); }
template<typename T, typename...Ts> inline constexpr const T &_max(const T &x, const Ts &...xs) { return _max(x, _max(xs...)); }
#define min(...) _min(__VA_ARGS__)
#define max(...) _max(__VA_ARGS__)
#define INF 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
using namespace std;

struct Big_Integer {
    vector<int> a;
    int sign;

    Big_Integer() : sign(1) { }

    Big_Integer(long long v) {
        *this = v;
    }

    Big_Integer(const string &s) {
        read(s);
    }

    void operator = (const Big_Integer &v) {
        sign = v.sign;
        a = v.a;
    }

    void operator = (long long v) {
        sign = 1;
        if (v < 0) sign = -1, v = -v;
        a.clear();
        for (; v > 0; v = v / 10) a.push_back(v % 10);
    }

    Big_Integer operator + (const Big_Integer &v) const {
        if (sign == v.sign) {
            Big_Integer res = v;
            for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; i++) {
                if (i == (int) res.a.size()) res.a.push_back(0);
                res.a[i] += carry + (i < (int) a.size() ? a[i] : 0);
                carry = res.a[i] >= 10;
                if (carry) res.a[i] -= 10;
            }
            return res;
        }
        return *this - (-v);
    }

    Big_Integer operator - (const Big_Integer &v) const {
        if (sign == v.sign) {
            if (abs() >= v.abs()) {
                Big_Integer res = *this;
                for (int i = 0, carry = 0; i < (int) v.a.size() || carry; i++) {
                    res.a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
                    carry = res.a[i] < 0;
                    if (carry) res.a[i] += 10;
                }
                res.trim();
                return res;
            }
            return -(v - *this);
        }
        return *this + (-v);
    }

    void operator *= (int v) {
        if (v < 0) sign = -sign, v = -v;
        for (int i = 0, carry = 0; i < (int) a.size() || carry; i++) {
            if (i == (int) a.size()) a.push_back(0);
            long long cur = a[i] * (long long) v + carry;
            carry = (int) (cur / 10);
            a[i] = (int) (cur % 10);
        }
        trim();
    }

    Big_Integer operator * (int v) const {
        Big_Integer res = *this;
        res *= v;
        return res;
    }

    friend pair<Big_Integer, Big_Integer> divmod(const Big_Integer &a1, const Big_Integer &b1) {
        int norm = 10 / (b1.a.back() + 1);
        Big_Integer a = a1.abs() * norm;
        Big_Integer b = b1.abs() * norm;
        Big_Integer q, r;
        q.a.resize(a.a.size());

        for (int i = a.a.size() - 1; i >= 0; i--) {
            r *= 10;
            r += a.a[i];
            int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
            int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            int d = ((long long) 10 * s1 + s2) / b.a.back();
            r -= b * d;
            while (r < 0) r += b, --d;
            q.a[i] = d;
        }

        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return make_pair(q, r / norm);
    }

    Big_Integer operator / (const Big_Integer &v) const {
        return divmod(*this, v).first;
    }

    Big_Integer operator % (const Big_Integer &v) const {
        return divmod(*this, v).second;
    }

    void operator /= (int v) {
        if (v < 0) sign = -sign, v = -v;
        for (int i = (int) a.size() - 1, rem = 0; i >= 0; i--) {
            long long cur = a[i] + rem * (long long) 10;
            a[i] = (int) (cur / v);
            rem = (int) (cur % v);
        }
        trim();
    }

    Big_Integer operator / (int v) const {
        Big_Integer res = *this;
        res /= v;
        return res;
    }

    int operator % (int v) const {
        if (v < 0) v = -v;
        int m = 0;
        for (int i = a.size() - 1; i >= 0; i--) m = (a[i] + m * (long long) 10) % v;
        return m * sign;
    }

    void operator += (const Big_Integer &v) {
        *this = *this + v;
    }
    void operator -= (const Big_Integer &v) {
        *this = *this - v;
    }
    void operator *= (const Big_Integer &v) {
        *this = *this * v;
    }
    void operator /= (const Big_Integer &v) {
        *this = *this / v;
    }

    bool operator < (const Big_Integer &v) const {
        if (sign != v.sign) return sign < v.sign;
        if (a.size() != v.a.size()) return a.size() * sign < v.a.size() * v.sign;
        for (int i = a.size() - 1; i >= 0; i--) if (a[i] != v.a[i]) return a[i] * sign < v.a[i] * sign;
        return false;
    }

    bool operator > (const Big_Integer &v) const {
        return v < *this;
    }
    bool operator <= (const Big_Integer &v) const {
        return !(v < *this);
    }
    bool operator >= (const Big_Integer &v) const {
        return !(*this < v);
    }
    bool operator == (const Big_Integer &v) const {
        return !(*this < v) && !(v < *this);
    }
    bool operator != (const Big_Integer &v) const {
        return *this < v || v < *this;
    }

    void trim() {
        while (!a.empty() && a.back() == 0) a.pop_back();
        if (a.empty()) sign = 1;
    }

    bool isZero() const {
        return a.empty() || (a.size() == 1 && !a[0]);
    }

    Big_Integer operator - () const {
        Big_Integer res = *this;
        res.sign = -sign;
        return res;
    }

    Big_Integer abs() const {
        Big_Integer res = *this;
        res.sign *= res.sign;
        return res;
    }

    long long longValue() const {
        long long res = 0;
        for (int i = a.size() - 1; i >= 0; i--) res = res * 10 + a[i];
        return res * sign;
    }

    friend Big_Integer gcd(const Big_Integer &a, const Big_Integer &b) {
        return b.isZero() ? a : gcd(b, a % b);
    }
    friend Big_Integer lcm(const Big_Integer &a, const Big_Integer &b) {
        return a / gcd(a, b) * b;
    }

    void read(const string &s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-') sign = -sign;
            pos++;
        }
        for (int i = s.size() - 1; i >= pos; i--) {
            int x = 0;
            for (int j = max(pos, i); j <= i; j++) x = x * 10 + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }

    friend istream& operator >> (istream &stream, Big_Integer &v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }

    friend ostream& operator << (ostream &stream, const Big_Integer &v) {
        if (v.sign == -1) stream << '-';
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int) v.a.size() - 2; i >= 0; i--) stream << setw(1) << setfill('0') << v.a[i];
        return stream;
    }

    void fft(vector<complex<double> > & a, bool invert) const {
        int n = (int) a.size();
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j >= bit; bit >>= 1) j -= bit;
            j += bit;
            if (i < j) swap(a[i], a[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * 3.14159265358979323846 / len * (invert ? -1 : 1);
            complex<double> wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                complex<double> w = (1);
                for (int j = 0; j < len / 2; j++) {
                    complex<double> u = a[i + j];
                    complex<double> v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }
        if (invert) for (int i = 0; i < n; i++) a[i] /= n;
    }

    void multiply_fft(const vector<int> &a, const vector<int> &b, vector<int> &res) const {
        vector<complex<double> > fa(a.begin(), a.end());
        vector<complex<double> > fb(b.begin(), b.end());
        int n = 1;
        while (n < (int) max(a.size(), b.size())) n <<= 1;
        n <<= 1;
        fa.resize(n);
        fb.resize(n);

        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; i++) fa[i] *= fb[i];
        fft(fa, true);

        res.resize(n);
        for (int i = 0, carry = 0; i < n; i++) {
            res[i] = int(fa[i].real() + 0.5) + carry;
            carry = res[i] / 10;
            res[i] %= 10;
        }
    }

    Big_Integer operator * (const Big_Integer &v) const {
        Big_Integer res;
        res.sign = sign * v.sign;
        multiply_fft(a, v.a, res.a);
        res.trim();
        return res;
    }

    Big_Integer mul_simple(const Big_Integer &v) const {
        Big_Integer res;
        res.sign = sign * v.sign;
        res.a.resize(a.size() + v.a.size());
        for (int i = 0; i < (int) a.size(); i++) {
            if (a[i]) {
                for (int j = 0, carry = 0; j < (int) v.a.size() || carry; j++) {
                    long long cur = res.a[i + j] + (long long) a[i] * (j < (int) v.a.size() ? v.a[j] : 0) + carry;
                    carry = (int) (cur / 10);
                    res.a[i + j] = (int) (cur % 10);
                }
            }
        }
        res.trim();
        return res;
    }

    typedef vector<long long> vll;

    static vll karatsubaMultiply(const vll &a, const vll &b) {
        int n = a.size();
        vll res(n + n);
        if (n <= 32) {
            for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) res[i + j] += a[i] * b[j];
            return res;
        }

        int k = n >> 1;
        vll a1(a.begin(), a.begin() + k);
        vll a2(a.begin() + k, a.end());
        vll b1(b.begin(), b.begin() + k);
        vll b2(b.begin() + k, b.end());

        vll a1b1 = karatsubaMultiply(a1, b1);
        vll a2b2 = karatsubaMultiply(a2, b2);

        for (int i = 0; i < k; i++) a2[i] += a1[i];
        for (int i = 0; i < k; i++) b2[i] += b1[i];

        vll r = karatsubaMultiply(a2, b2);
        for (int i = 0; i < (int) a1b1.size(); i++) r[i] -= a1b1[i];
        for (int i = 0; i < (int) a2b2.size(); i++) r[i] -= a2b2[i];
        for (int i = 0; i < (int) r.size(); i++) res[i + k] += r[i];
        for (int i = 0; i < (int) a1b1.size(); i++) res[i] += a1b1[i];
        for (int i = 0; i < (int) a2b2.size(); i++) res[i + n] += a2b2[i];
        return res;
    }

    Big_Integer mul_karatsuba(const Big_Integer &v) const {
        vll a(this->a.begin(), this->a.end());
        vll b(v.a.begin(), v.a.end());
        while (a.size() < b.size()) a.push_back(0);
        while (b.size() < a.size()) b.push_back(0);
        while (a.size() & (a.size() - 1)) a.push_back(0), b.push_back(0);
        vll c = karatsubaMultiply(a, b);
        Big_Integer res;
        res.sign = sign * v.sign;
        for (int i = 0, carry = 0; i < (int) c.size(); i++) {
            long long cur = c[i] + carry;
            res.a.push_back((int) (cur % 10));
            carry = (int) (cur / 10);
        }
        res.trim();
        return res;
    }
};

int main() {
    Big_Integer a, b;
    cin >> a;
    char op;
    scanf(" %c", &op);
    cin >> b;
    cout << (op == '+' ? a + b : a * b) << endl;
    return 0;
}
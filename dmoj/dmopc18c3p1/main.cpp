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

string notes[] {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
map<string, int> val;
string inversions[] {"root position", "second inversion", "first inversion"};
string f, s, t;
int first, second, third;

int dif(int a, int b) {
    return ((b - a) + 12) % 12;
}

int main() {
    for (int i = 0; i < 12; i++) {
        val[notes[i]] = i;
    }

    cin >> f >> s >> t;

    first = val[f], second = val[s], third = val[t];

    for (int i = 0; i < 3; i++, swap(first, second), swap(second, third)) {
        if (dif(first, second) == 4 && dif(second, third) == 4) {
            cout << notes[first] << '\n';
            cout << "augmented\n";
            cout << inversions[i] << '\n';
            break;
        } else if (dif(first, second) == 4 && dif(second, third) == 3) {
            cout << notes[first] << '\n';
            cout << "major\n";
            cout << inversions[i] << '\n';
            break;
        } else if (dif(first, second) == 3 && dif(second, third) == 4) {
            cout << notes[first] << '\n';
            cout << "minor\n";
            cout << inversions[i] << '\n';
            break;
        } else if (dif(first, second) == 3 && dif(second, third) == 3) {
            cout << notes[first] << '\n';
            cout << "diminished\n";
            cout << inversions[i] << '\n';
            break;
        }
    }

    return 0;
}
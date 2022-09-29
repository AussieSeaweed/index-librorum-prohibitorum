#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, K;
char buffer[200010];
bool unmatched[200000];
bool modified[200000], is_impossible = false;
vector<int> unmatches;
int p[200000];
map<char, char> corresponding {
        {'(', ')'},
        {'[', ']'},
        {'{', '}'},
        {')', '('},
        {']', '['},
        {'}', '{'}
};
map<pair<char, char>, char> other {
        {{')', ']'}, '}'},
        {{']', ')'}, '}'},

        {{']', '}'}, ')'},
        {{'}', ']'}, ')'},

        {{')', '}'}, ']'},
        {{'}', ')'}, ']'},
};
map<char, char> nextchar {
        {'(', '['},
        {'[', '{'},
        {'{', '('}
};

int get_num_unmatches() {
    int ret = 0;
    stack<int> pred;
    stack<char> req;

    for (int i = 0; i < N; i++) {
        if (buffer[i] == '(' || buffer[i] == '[' || buffer[i] == '{') {
            pred.push(i);
            req.push(corresponding[buffer[i]]);
        } else if (req.empty()) {
            is_impossible = true;
            return inf;
        } else {
            if (buffer[i] != req.top()) {
                ret++;
                unmatched[i] = true;
                unmatched[pred.top()] = true;
                unmatches.push_back(pred.top());
            }

            p[i] = pred.top();
            p[pred.top()] = i;
            pred.pop();
            req.pop();
        }
    }

    if (!req.empty()) is_impossible = true;
    return ret;
}

bool possible(int num_unmatch, int num_match) {
    int rem_k = K;

    if (rem_k & 1) {
        if (!num_unmatch) return false;
        rem_k--;
        num_unmatch--;
    }

    while (num_unmatch) {
        if (rem_k == 0) {
            return false;
        } else if (rem_k < num_unmatch * 2) {
            rem_k--;
        } else {
            rem_k -= 2;
        }

        num_unmatch--;
    }

    return rem_k <= num_match * 2;
}

void fix_unmatches(int num_unmatches) {
    if (K & 1) {
        K--;
        buffer[p[unmatches.back()]] = corresponding[buffer[unmatches.back()]];
        modified[unmatches.back()] = true;
        modified[p[unmatches.back()]] = true;
        unmatches.pop_back();
        num_unmatches--;
    }

    for (int index : unmatches) {
        if (K < num_unmatches * 2) {
            K--;
            buffer[p[index]] = corresponding[buffer[index]];
            modified[index] = true;
            modified[p[index]] = true;
        } else {
            char close = other[{corresponding[buffer[index]], buffer[p[index]]}], open = corresponding[close];
            K -= 2;
            buffer[index] = open;
            buffer[p[index]] = close;
            modified[index] = true;
            modified[p[index]] = true;
        }
        num_unmatches--;
    }
}

void swap_as_fit() {
    for (int i = 0; i < N && K; i++) {
        if (!modified[i]) {
            char open = nextchar[buffer[i]], close = corresponding[open];
            buffer[i] = open;
            buffer[p[i]] = close;
            modified[i] = true;
            modified[p[i]] = true;
            K -= 2;
        }
    }
}

int main() {
    scan(N);
    scan(K);
    scanf("%s", buffer);
    int num_unmatches = get_num_unmatches(), num_matches = N / 2 - num_unmatches;

    if (is_impossible || !possible(num_unmatches, num_matches)) {
        printf("impossible\n");
    } else {
        fix_unmatches(num_unmatches);
        swap_as_fit();
        printf(buffer);
    }
    return 0;
}
#include <bits/stdc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
using namespace std;

int N, K, M;

struct Node {
    int len, ans;
    pair<long long, int> prefix[50], suffix[50];

    Node() : len{ 0 }, ans{ inf } {}
    Node(int index, int value) {
        len = 1;
        ans = K == 1 ? 1 : inf;
        prefix[0] = suffix[0] = make_pair(1ll << (value - 1), index);
    }
};

Node seg_tree[262144];

bool subset(long long a, long long b) {
    return (a & b) == a;
}

void merge(Node &parent, Node &left, Node &right) {
    int len;

    for (len = 0; len < left.len; len++)
        parent.prefix[len] = left.prefix[len];
    for (int i = 0; i < right.len; i++) {
        if (len == 0 || !subset(right.prefix[i].first, parent.prefix[len - 1].first)) {
            parent.prefix[len].first = right.prefix[i].first;
            if (len) parent.prefix[len].first |= parent.prefix[len - 1].first;
            parent.prefix[len].second = right.prefix[i].second;
            len++;
        }
    }

    for (len = 0; len < right.len; len++)
        parent.suffix[len] = right.suffix[len];
    for (int i = 0; i < left.len; i++) {
        if (len == 0 || !subset(left.suffix[i].first, parent.suffix[len - 1].first)) {
            parent.suffix[len].first = left.suffix[i].first;
            if (len) parent.suffix[len].first |= parent.suffix[len - 1].first;
            parent.suffix[len].second = left.suffix[i].second;
            len++;
        }
    }

    parent.len = len;
    parent.ans = min(left.ans, right.ans);

    for (int lptr = 0, rptr = right.len - 1; lptr < left.len && rptr >= 0; rptr--) {
        while (lptr < left.len && (left.suffix[lptr].first | right.prefix[rptr].first) != (1ll << K) - 1) lptr++;
        if (lptr < left.len && (left.suffix[lptr].first | right.prefix[rptr].first) == (1ll << K) - 1) {
            parent.ans = min(parent.ans, right.prefix[rptr].second - left.suffix[lptr].second + 1);
        }
    }
}

void update(int node, int lo, int hi, int index, int value) {
    if (index < lo || hi < index) return;

    if (lo == hi) {
        seg_tree[node] = Node(index, value);
    } else {
        int mid = lo + (hi - lo) / 2;
        update(node * 2, lo, mid, index, value);
        update(node * 2 + 1, mid + 1, hi, index, value);
        merge(seg_tree[node], seg_tree[node * 2], seg_tree[node * 2 + 1]);
    }
}

int main() {
    scan(N);
    scan(K);
    scan(M);

    for (int i = 1; i <= N; i++) {
        int value;
        scan(value);
        update(1, 1, N, i, value);
    }

    while (M--) {
        int t;
        scan(t);

        switch (t) {
            case 1: {
                int p, v;
                scan(p);
                scan(v);
                update(1, 1, N, p, v);
            }
                break;
            case 2: {
                printf("%d\n", seg_tree[1].ans == inf ? -1 : seg_tree[1].ans);
            }
                break;
            default: break;
        }
    }

    return 0;
}
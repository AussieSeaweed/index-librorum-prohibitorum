#include <bits/stdc++.h>
#include <bits/extc++.h>
#define scan(x) do{while((x=getchar())<'0'); for(x-='0'; '0'<=(_=getchar()); x=(x<<3)+(x<<1)+_-'0');}while(0)
char _;
#define INF 9000000000000000000
#define inf 2000000000
#define MOD 1000000007
using namespace std;

long long base[200001];

struct Node {
    char c;
    Node *left, *right;
    int size;
    long long hash;

    Node(Node *left, Node *right) : size{ left->size + right->size },c{ 0 }, left{ left }, right{ right } {
        hash = (left->hash + right->hash * base[left->size]) % MOD;
    }

    Node(char c) : size{ 1 }, c{ c }, hash{ c }, left{ nullptr }, right{ nullptr } {}
};

int N, Q, L;
char S[200005];
Node *versions[200001];

Node *build_tree(int lo, int hi) {
    if (lo == hi) {
        return new Node(S[lo]);
    } else {
        int mid = lo + (hi - lo) / 2;
        return new Node(build_tree(lo, mid), build_tree(mid + 1, hi));
    }
}

char query(Node *node, int lo, int hi, int index) {
    if (lo == hi) return node->c;
    int mid = lo + (hi - lo) / 2;
    if (index <= mid) return query(node->left, lo, mid, index);
    else return query(node->right, mid + 1, hi, index);
}

bool cmp_aux(Node *a, Node *b, int lo, int hi) {
    if (lo == hi) return a->c < b->c;
    int mid = lo + (hi - lo) / 2;
    if (a->left->hash != b->left->hash) return cmp_aux(a->left, b->left, lo, mid);
    else return cmp_aux(a->right, b->right, mid + 1, hi);
}

bool cmp(Node *a, Node *b) {
    return cmp_aux(a, b, 1, L);
}

Node *update(Node *node, int lo, int hi, int index, char c) {
    if (index < lo || hi < index) return node;

    if (lo == hi) {
        return new Node(c);
    } else {
        int mid = lo + (hi - lo) / 2;
        return new Node(update(node->left, lo, mid, index, c), update(node->right, mid + 1, hi, index, c));
    }
}

int main() {
    scanf("%s", S + 1);
    L = strlen(S + 1);

    base[0] = 1;

    for (int i = 1; i <= L; i++) {
        base[i] = base[i - 1] * ('z' + 1) % MOD;
    }

    versions[1] = build_tree(1, L);

    scan(N);

    for (int i = 2; i <= N; i++) {
        int index;
        char c;
        scan(index);
        scanf(" %c", &c);
        versions[i] = update(versions[i - 1], 1, L, index, c);
    }

    sort(versions + 1, versions + N + 1, cmp);

    scan(Q);

    while (Q--) {
        int i, j;
        scan(i);
        scan(j);

        printf("%c\n", query(versions[i], 1, L, j));
    }

    return 0;
}
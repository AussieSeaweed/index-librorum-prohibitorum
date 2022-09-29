import sys
raw_input = sys.stdin.readline


class UF:
    def __init__(self, n):
        self.id = range(n)
        self.size = [1] * n

    def root(self, i):
        while self.id[i] != i:
            self.id[i] = self.id[self.id[i]]
            i = self.id[i]
        return i

    def union(self, a, b):
        aroot = self.root(a)
        broot = self.root(b)
        if self.size[aroot] < self.size[b]:
            self.id[self.root(a)] = broot
            self.size[broot] += self.size[aroot]
        else:
            self.id[broot] = aroot
            self.size[aroot] += self.size[broot]

    def connected(self, a, b):
        return self.root(a) == self.root(b)


n, q = map(int, raw_input().split())

uf = UF(n)

for x in xrange(q):
    query, p, q = raw_input().split()
    p = int(p) - 1
    q = int(q) - 1

    if query == "Q":
        if uf.connected(p, q):
            print "Y"
        else:
            print "N"
    else:
        uf.union(p, q)
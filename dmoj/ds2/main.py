class DataStructure:
    def __init__(self, num_nodes, node_factory):
        self._num_nodes = num_nodes
        self._node_factory = node_factory

        self._nodes = self._create_nodes()

    def _create_node(self):
        return self._node_factory()

    def _create_nodes(self):
        return [self._create_node() for _ in range(self._num_nodes)]

    def __len__(self):
        return self._num_nodes

    def __getitem__(self, item):
        return self._nodes[item]

    def __setitem__(self, key, value):
        self._nodes[key] = value


class DisjointSet(DataStructure):
    def __init__(self, num_nodes, node_factory=lambda: 1):
        super().__init__(num_nodes, node_factory)

        self.__parents = list(range(num_nodes))

    def root(self, index):
        if self.__parents[index] != index:
            self.__parents[index] = self.root(self.__parents[index])

        return self.__parents[index]

    def query(self, u, v):
        return self.root(u) == self.root(v)

    def merge(self, u, v):
        u, v = sorted([self.root(u), self.root(v)])

        if u != v:
            self.__parents[v] = u
            self._nodes[u] += self._nodes[v]
        else:
            raise ValueError('The nodes are already connected')

    def __getitem__(self, item):
        return super().__getitem__(self.root(item))

    def __setitem__(self, key, value):
        return super().__setitem__(self.root(key), value)


N, M = map(int, input().split())
disjoint_set = DisjointSet(N)
indices = []

for i in range(M):
    u, v = map(int, input().split())

    if not disjoint_set.query(u - 1, v - 1):
        disjoint_set.merge(u - 1, v - 1)
        indices.append(i)

if disjoint_set[0] == N:
    print('\n'.join(map(lambda index: str(index + 1), indices)))
else:
    print('Disconnected Graph')
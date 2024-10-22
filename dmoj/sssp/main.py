from abc import ABC, abstractmethod
from collections import defaultdict, deque
from functools import partial
from itertools import chain
from math import inf, isfinite, isinf


class Edge:
    def __init__(self, u, v, *, directed=False, weight=None, flow=None, capacity=None):
        self.u = u
        self.v = v

        self.directed = directed
        self.weight = weight
        self.flow = flow
        self.capacity = capacity

    @property
    def endpoints(self):
        return self.u, self.v

    def match(self, u, v):
        if u is None and v is None:
            return True
        elif u is None:
            return v == self.v or (not self.directed and v == self.u)
        elif v is None:
            return u == self.u or (not self.directed and u == self.v)
        else:
            return (u, v) == self.endpoints or (not self.directed and (v, u) == self.endpoints)

    def other(self, vertex):
        if vertex == self.u:
            return self.v
        elif vertex == self.v:
            return self.u
        else:
            raise ValueError('The vertex is not one of the endpoints')


class Graph(ABC):
    def __init__(self):
        self.__nodes = set()

    @property
    def nodes(self):
        return iter(self.__nodes)

    def add(self, edge):
        self.__nodes.add(edge.u)
        self.__nodes.add(edge.v)

    @abstractmethod
    def edges(self, from_=None, to=None):
        pass


class EdgeList(Graph):
    def __init__(self):
        super().__init__()

        self.__edge_list = []

    def add(self, edge):
        super().add(edge)

        self.__edge_list.append(edge)

    def edges(self, from_=None, to=None):
        return iter({edge for edge in self.__edge_list if edge.match(from_, to)})


class AdjacencyMatrix(Graph):
    def __init__(self):
        super().__init__()

        self.__adj_matrix = defaultdict(partial(defaultdict, list))

    def add(self, edge):
        super().add(edge)

        self.__adj_matrix[edge.u][edge.v].append(edge)

        if not edge.directed:
            self.__adj_matrix[edge.v][edge.u].append(edge)

    def edges(self, from_=None, to=None):
        edges = set()

        if from_ is None and to is None:
            for adj_lists in self.__adj_matrix.values():
                for adj_list in adj_lists.values():
                    edges |= set(adj_list)
        elif from_ is None:
            for adj_lists in self.__adj_matrix.values():
                edges |= set(adj_lists[to])
        elif to is None:
            for adj_list in self.__adj_matrix[from_].values():
                edges |= set(adj_list)
        else:
            edges = self.__adj_matrix[from_][to]

        return iter(edges)


class AdjacencyLists(Graph):
    def __init__(self):
        super().__init__()

        self.__adj_lists = defaultdict(list)

    def add(self, edge):
        super().add(edge)

        self.__adj_lists[edge.u].append(edge)

        if not edge.directed:
            self.__adj_lists[edge.v].append(edge)

    def edges(self, from_=None, to=None):
        if from_ is None and to is None:
            return iter(set(chain(*(self.edges(node) for node in self.nodes))))
        elif from_ is None:
            return (edge for edge in self.edges() if edge.match(None, to))
        elif to is None:
            return iter(self.__adj_lists[from_])
        else:
            return (edge for edge in self.__adj_lists[from_] if to in edge.endpoints)


class SingleSourceTraverser(ABC):
    def __init__(self, graph, source):
        self.graph = graph
        self.source = source

        self._dists = defaultdict(lambda: inf)
        self._preds = defaultdict(lambda: None)

        self._traverse()

    def visited(self, node):
        return isfinite(self._dists[node])

    def distance(self, node):
        return self._dists[node]

    def path(self, node):
        if not self.visited(node):
            raise ValueError('The node is not reachable')

        path = []

        while node is not None:
            path.append(node)
            node = self._preds[node]

        return reversed(path)

    @abstractmethod
    def _traverse(self):
        pass


class ShortestPathFaster(SingleSourceTraverser):
    def _traverse(self):
        self._dists[self.source] = 0
        queue = deque((self.source,))
        queued = {self.source}

        while queue:
            node = queue.popleft()
            queued.remove(node)

            for edge in self.graph.edges(node):
                other = edge.other(node)

                if self._dists[other] > self._dists[node] + edge.weight:
                    self._dists[other] = self._dists[node] + edge.weight

                    if other not in queued:
                        queue.append(other)
                        queued.add(other)


N, M = map(int, input().split())

graph = AdjacencyLists()

for _ in range(M):
    u, v, w = map(int, input().split())

    graph.add(Edge(u, v, weight=w))

spf = ShortestPathFaster(graph, 1)

for i in range(1, N + 1):
    dist = spf.distance(i)

    print(-1 if isinf(dist) else dist)
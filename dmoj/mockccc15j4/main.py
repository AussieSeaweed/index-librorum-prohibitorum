from abc import ABC, abstractmethod
from math import ceil


class Symmetry(ABC):
    def __init__(self, n, grid):
        self.n = n
        self.grid = grid

    def is_symmetric(self):
        for r, c in self.get_indices():
            p, q = self.get_index(r, c)

            if self.get_chr(self.grid[r][c]) != self.grid[p][q]:
                return False

        return True

    @abstractmethod
    def get_indices(self): ...

    @abstractmethod
    def get_index(self, r, c): ...

    @abstractmethod
    def get_chr(self, c): ...


class HorizontalSymmetry(Symmetry):  # Reflection on -----
    def get_indices(self):
        for r in range(ceil(self.n / 2)):
            for c in range(self.n):
                yield r, c

    def get_index(self, r, c):
        return self.n - 1 - r, c

    def get_chr(self, c):
        if c in ('.', 'O'):
            return c
        elif c == '(':
            return '('
        elif c == ')':
            return ')'
        elif c == '/':
            return '\\'
        elif c == '\\':
            return '/'
        else:
            return None


class VerticalSymmetry(Symmetry):  # Reflection on |
    def get_indices(self):
        for r in range(self.n):
            for c in range(ceil(self.n / 2)):
                yield r, c

    def get_index(self, r, c):
        return r, self.n - 1 - c

    def get_chr(self, c):
        if c in ('.', 'O'):
            return c
        elif c == '(':
            return ')'
        elif c == ')':
            return '('
        elif c == '/':
            return '\\'
        elif c == '\\':
            return '/'
        else:
            return None


class DiagonalSymmetry(Symmetry, ABC):
    def get_chr(self, c):
        if c in ('.', 'O'):
            return c
        elif c == '(':
            return None
        elif c == ')':
            return None
        elif c == '/':
            return '/'
        elif c == '\\':
            return '\\'
        else:
            return None


class DiagonalUpSymmetry(DiagonalSymmetry):
    def get_indices(self):
        for r in range(self.n):
            for c in range(self.n - r):
                yield r, c

    def get_index(self, r, c):
        return self.n - 1 - c, self.n - 1 - r


class DiagonalDownSymmetry(DiagonalSymmetry):
    def get_indices(self):
        for r in range(self.n):
            for c in range(r, self.n):
                yield r, c

    def get_index(self, r, c):
        return c, r


N = int(input())
grid = [input() for _ in range(N)]
symmetries = [
    HorizontalSymmetry(N, grid),
    VerticalSymmetry(N, grid),
    DiagonalUpSymmetry(N, grid),
    DiagonalDownSymmetry(N, grid),
]

print(sum(symmetry.is_symmetric() for symmetry in symmetries))
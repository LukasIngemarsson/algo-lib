

class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n)) 
        self.rank = [0] * n

    def find(self, a):
        if self.parent[a] != a:
            self.parent[a] = self.find(self.parent[a])
        return self.parent[a]

    def union(self, a, b):
        a_root = self.find(a)
        b_root = self.find(b)
        if a_root == b_root:
            return
        if self.rank[a_root] <= self.rank[b_root]:
            if self.rank[a_root] == self.rank[b_root]:
                self.rank[b_root] += 1
            self.parent[a_root] = b_root
        else:
            self.parent[b_root] = a_root

    def same(self, a, b):
        return self.find(a) == self.find(b)

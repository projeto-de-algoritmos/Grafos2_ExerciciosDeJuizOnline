class UnionFind:
    def __init__(self, n):
        self.parent = [i for i in range(n)]
        self.rank = [0] * n

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)

        if root_x == root_y:
            return False

        if self.rank[root_x] < self.rank[root_y]:
            self.parent[root_x] = root_y
        elif self.rank[root_x] > self.rank[root_y]:
            self.parent[root_y] = root_x
        else:
            self.parent[root_y] = root_x
            self.rank[root_x] += 1

        return True


def kruskal(edges, n):
    edges.sort(key=lambda edge: edge[2])
    mst_weight = 0
    uf = UnionFind(n)

    for edge in edges:
        u, v, weight = edge
        if uf.union(u, v):
            mst_weight += weight

    return mst_weight

while True:
    m, n = map(int, input().split())
    if m == 0 and n == 0:
        break

    roads = []
    for _ in range(n):
        x, y, z = map(int, input().split())
        roads.append((x, y, z))

    total_distance = kruskal([(roads[i][0], roads[i][1], roads[i][2]) for i in range(n)], m)
    print(total_distance)

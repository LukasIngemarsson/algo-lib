import sys


sys.setrecursionlimit(10**6)


def find_bridges(adj):
    n = len(adj)
    bridges = []
    vis = [False] * n
    tin = [-1] * n
    low = [-1] * n
    timer = 1
    def dfs(v, p=-1):
        nonlocal timer
        vis[v] = True
        tin[v] = low[v] = timer
        timer += 1
        parent_skipped = False
        for to in adj[v]:
            if to == p and not parent_skipped:
                parent_skipped = True
                continue
            if vis[to]:
                low[v] = min(low[v], tin[to])
            else:
                dfs(to, v)
                low[v] = min(low[v], low[to])
                if low[to] > tin[v]:
                    bridges.append((min(v, to), max(v, to)))
    for i in range(n):
        if not vis[i]:
            dfs(i)
    return bridges

import sys
sys.setrecursionlimit(10**6)

def sieve(N):
    is_prime = [True] * (N + 1)
    is_prime[0] = False
    if N >= 1:
        is_prime[1] = False

    a = 2
    while a * a <= N:
        if is_prime[a]:
            multiple = a * a
            while multiple <= N:
                is_prime[multiple] = False
                multiple += a
        a += 1

    return is_prime


def efficiencyScores(n, values, edges, queries):

    tree = [[] for _ in range(n + 1)]
    for u, v in edges:
        tree[u].append(v)
        tree[v].append(u)

    is_prime = sieve(max(values))
    primeCount = [0] * (n + 1)

    def dfs(u, parent):
        count = 1 if is_prime[values[u - 1]] else 0

        for v in tree[u]:
            if v != parent:
                count += dfs(v, u)

        primeCount[u] = count
        return count

    dfs(1, -1)

    return [primeCount[q] for q in queries]

n = 5
values = [10, 7, 4, 5, 6]
edges = [[1,2], [1,3], [2,4], [2,5]]
queries = [1, 2, 3]

result = efficiencyScores(n, values, edges, queries)

print("Prime counts in queried subtrees:")
for q, res in zip(queries, result):
        print(f"Node {q}: {res}")
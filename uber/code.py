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

def run_test(test_num, n, values, edges, queries, expected):
    print(f"\n--- Test Case {test_num} ---")
    print("Values:", values)
    print("Edges:", edges)
    print("Queries:", queries)

    result = efficiencyScores(n, values, edges, queries)

    print("Output:", result)
    print("Expected:", expected)

    if result == expected:
        print("PASS")
    else:
        print("FAIL")


# ---------- TEST CASES ----------

# Test Case 1
run_test(
    1,
    5,
    [10, 7, 4, 5, 6],
    [[1,2], [1,3], [2,4], [2,5]],
    [1, 2, 3],
    [2, 2, 0]
)

# Test Case 2 (All non-prime)
run_test(
    2,
    4,
    [1, 4, 6, 8],
    [[1,2], [1,3], [2,4]],
    [1, 2, 3, 4],
    [0, 0, 0, 0]
)

# Test Case 3 (All prime)
run_test(
    3,
    5,
    [2, 3, 5, 7, 11],
    [[1,2], [1,3], [2,4], [2,5]],
    [1, 2, 3],
    [5, 3, 1]
)

# Test Case 4 (Skewed tree)
run_test(
    4,
    5,
    [2, 4, 3, 9, 5],
    [[1,2], [2,3], [3,4], [4,5]],
    [1, 2, 3, 4, 5],
    [3, 2, 2, 1, 1]
)

# Test Case 5 (Mixed)
run_test(
    5,
    7,
    [8, 3, 10, 7, 6, 5, 2],
    [[1,2], [1,3], [2,4], [2,5], [3,6], [3,7]],
    [1, 2, 3, 4],
    [4, 2, 2, 1]
)
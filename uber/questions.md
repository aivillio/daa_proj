# Uber Infrastructure Problem – Subtree Prime Count

## 🔹 Problem Overview

Given a tree of `N` nodes where each node represents a service hub with an efficiency score, we must answer multiple queries:

> For a given node `u`, count how many nodes in its subtree (including itself) have **prime efficiency scores**.

---

# 1. Psudocode

FUNCTION efficiencyScores(n, values, edges, queries):

    CREATE adjacency list tree[1..n]

    FOR each (u, v) in edges:
        tree[u].append(v)
        tree[v].append(u)

    maxVal = maximum value in values

    isPrime = SIEVE(maxVal)

    CREATE array primeCount[1..n] initialized to 0


    FUNCTION DFS(u, parent):

        IF isPrime[values[u]]:
            count = 1
        ELSE:
            count = 0

        FOR each v in tree[u]:
            IF v != parent:
                count = count + DFS(v, u)

        primeCount[u] = count

        RETURN count


    CALL DFS(1, -1)

    CREATE result list

    FOR each q in queries:
        result.append(primeCount[q])

    RETURN result

FUNCTION SIEVE(N):

    CREATE array isPrime[0..N] and set all values to TRUE

    isPrime[0] = FALSE
    isPrime[1] = FALSE

    FOR a from 2 while (a * a ≤ N):

        IF isPrime[a] == TRUE:

            FOR multiple from (a * a) to N step a:
                isPrime[multiple] = FALSE

    RETURN isPrime

3. Efficient Prime Determination Method

We use the Sieve of Eratosthenes to determine primality efficiently.

# Algorithm:
* Initialize all numbers as prime.
* Iterate from 2 to √N.
* For each number a, if it is prime:
* Mark all multiples of a (starting from a * a) as non-prime.

🔹 Complexity:

   O(Nlog⁡log⁡N)


Here is the markdown version of the complexity analysis shown in the image, ready for copy-pasting.

---

## ✅ 4. Time Complexity Analysis

* **Prime Preprocessing**
  $$O(N \log \log N)$$

---

* **Tree Traversal and Preprocessing (DFS)**
  $$O(N)$$
    * Each node is visited once.

---

* **Each Query**
  $$O(1)$$
    * Direct lookup from precomputed array.

---

* **Overall Complexity**
  $$O(N \log \log N + N + Q)$$


# Performance for Large Inputs and Optimizations

## 🔹 Performance for Large Inputs (N, Q ≤ 10⁵)

The proposed approach performs efficiently for large inputs due to the following reasons:

### Single DFS Traversal:
- The tree is traversed only once to compute subtree prime counts.
- **Time complexity = O(N)**

### Efficient Prime Preprocessing:
- Using the Sieve of Eratosthenes allows computation of primes up to 10⁵ in:
- **O(N log log N)**

### Constant-Time Queries:
- Each query is answered using a precomputed value:
- **O(1) per query**

## 🔹 Overall Time Complexity

$$O(N \log \log N + N + Q)$$

👉 This is efficient and scalable for **N, Q ≤ 10⁵**.
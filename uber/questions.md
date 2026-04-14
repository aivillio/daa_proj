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


The time complexity of the **Sieve of Eratosthenes** comes from counting how many times we mark numbers as non-prime.

---



For every prime ( p ), we mark its multiples:

* ( p, 2p, 3p, 4p, \dots \le N )
* Number of multiples ≈ ( \frac{N}{p} )

So total work is roughly:

[
\sum_{\text{primes } p \le N} \frac{N}{p}
]

Factor out ( N ):

[
N \sum_{\text{primes } p \le N} \frac{1}{p}
]

---

## 🔹 Key mathematical result

The important result from number theory:

[
\sum_{\text{primes } p \le N} \frac{1}{p} \approx \log \log N
]

So total complexity becomes:

[
N \cdot \log \log N
]

---

## 🔹 Final summation form



[
\sum_{p \le N} \left\lfloor \frac{N}{p} \right\rfloor
]

Approximate it:

[
\approx N \sum_{p \le N} \frac{1}{p}
\approx N \log \log N
]

---

## 🔹 Why not ( N \log N )?

Because:

* We **don’t iterate over all numbers** in the inner loop
* Only over **primes**
* And primes become rarer as numbers grow

That’s why the harmonic-like sum over primes grows slower:

* Harmonic series ->( \log N )
* Prime harmonic series ->( \log \log N )

---




## 4. Time Complexity Analysis

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

This is efficient and scalable for **N, Q ≤ 10⁵**.des (consider constraints up to 10^5).

## Optimization 

To handle queries efficiently in an online setting where updates and queries are interleaved, the current DFS-based approach can be optimized using the Euler Tour technique combined with a Fenwick Tree (Binary Indexed Tree). The Euler Tour is used to flatten the tree into an array such that each subtree corresponds to a contiguous range. We then maintain a Fenwick Tree over this array, storing 1 for prime-valued nodes and 0 otherwise. This allows subtree queries to be answered as range sum queries and node updates to be handled efficiently. As a result, both updates and queries can be processed in 
O(log⁡N) O(logN) time, making the solution suitable for dynamic scenarios with large inputs.
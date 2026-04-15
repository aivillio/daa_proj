#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Data Structures ---

typedef struct Edge {
    int to;
    struct Edge *next;
} Edge;

typedef struct {
    Edge **head;
    int n;
} Graph;

// --- Helper Functions ---

bool* sieve(int N) {
    bool *is_prime = (bool*)malloc((N + 1) * sizeof(bool));
    for (int i = 0; i <= N; i++) is_prime[i] = true;
    is_prime[0] = false;
    if (N >= 1) is_prime[1] = false;

    for (int p = 2; p * p <= N; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= N; i += p)
                is_prime[i] = false;
        }
    }
    return is_prime;
}

void add_edge(Graph *g, int u, int v) {
    Edge *e1 = (Edge*)malloc(sizeof(Edge));
    e1->to = v;
    e1->next = g->head[u];
    g->head[u] = e1;

    Edge *e2 = (Edge*)malloc(sizeof(Edge));
    e2->to = u;
    e2->next = g->head[v];
    g->head[v] = e2;
}

void free_graph(Graph *g) {
    for (int i = 1; i <= g->n; i++) {
        Edge *curr = g->head[i];
        while (curr) {
            Edge *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(g->head);
}

// --- Core Logic ---

int dfs(int u, int p, Graph *g, int *values, bool *is_prime_vals, int *primeCount) {
    int count = is_prime_vals[values[u - 1]] ? 1 : 0;

    for (Edge *e = g->head[u]; e != NULL; e = e->next) {
        int v = e->to;
        if (v != p) {
            count += dfs(v, u, g, values, is_prime_vals, primeCount);
        }
    }

    primeCount[u] = count;
    return count;
}

void efficiencyScores(int n, int *values, int edges[][2], int edge_count, int *queries, int query_count, int *res_counts, bool *res_flags) {
    Graph g;
    g.n = n;
    g.head = (Edge**)calloc(n + 1, sizeof(Edge*));

    for (int i = 0; i < edge_count; i++) {
        add_edge(&g, edges[i][0], edges[i][1]);
    }

    int max_val = 0;
    for (int i = 0; i < n; i++) {
        if (values[i] > max_val) max_val = values[i];
    }

    bool *is_prime_vals = sieve(max_val);
    int *primeCount = (int*)calloc(n + 1, sizeof(int));

    dfs(1, -1, &g, values, is_prime_vals, primeCount);

    bool *is_prime_counts = sieve(n);

    for (int i = 0; i < query_count; i++) {
        int q = queries[i];
        res_counts[i] = primeCount[q];
        res_flags[i] = is_prime_counts[res_counts[i]];
    }

    // Cleanup
    free(is_prime_vals);
    free(is_prime_counts);
    free(primeCount);
    free_graph(&g);
}

// --- Test Harness ---

void run_test(int test_num, int n, int *values, int edges[][2], int edge_count, int *queries, int query_count, int *expected_counts, bool *expected_flags) {
    printf("\n--- Test Case %d ---\n", test_num);
    
    int *res_counts = (int*)malloc(query_count * sizeof(int));
    bool *res_flags = (bool*)malloc(query_count * sizeof(bool));

    efficiencyScores(n, values, edges, edge_count, queries, query_count, res_counts, res_flags);

    printf("Prime Counts: ");
    for (int i = 0; i < query_count; i++) printf("%d ", res_counts[i]);
    printf("\nIs Count Prime?: ");
    for (int i = 0; i < query_count; i++) printf("%s ", res_flags[i] ? "True" : "False");
    printf("\n");

    bool pass = true;
    for (int i = 0; i < query_count; i++) {
        if (res_counts[i] != expected_counts[i] || res_flags[i] != expected_flags[i]) {
            pass = false;
            break;
        }
    }

    if (pass) printf("PASS\n");
    else printf("FAIL\n");

    free(res_counts);
    free(res_flags);
}

int main() {
    // Test Case 1
    {
        int values[] = {10, 7, 4, 5, 6};
        int edges[][2] = {{1, 2}, {1, 3}, {2, 4}, {2, 5}};
        int queries[] = {1, 2, 3};
        int exp_counts[] = {2, 2, 0};
        bool exp_flags[] = {true, true, false};
        run_test(1, 5, values, edges, 4, queries, 3, exp_counts, exp_flags);
    }

    // Test Case 2
    {
        int values[] = {1, 4, 6, 8};
        int edges[][2] = {{1, 2}, {1, 3}, {2, 4}};
        int queries[] = {1, 2, 3, 4};
        int exp_counts[] = {0, 0, 0, 0};
        bool exp_flags[] = {false, false, false, false};
        run_test(2, 4, values, edges, 3, queries, 4, exp_counts, exp_flags);
    }

    // Test Case 3
    {
        int values[] = {2, 3, 5, 7, 11};
        int edges[][2] = {{1, 2}, {1, 3}, {2, 4}, {2, 5}};
        int queries[] = {1, 2, 3};
        int exp_counts[] = {5, 3, 1};
        bool exp_flags[] = {true, true, false};
        run_test(3, 5, values, edges, 4, queries, 3, exp_counts, exp_flags);
    }

    // Test Case 4
    {
        int values[] = {2, 4, 3, 9, 5};
        int edges[][2] = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
        int queries[] = {1, 2, 3, 4, 5};
        int exp_counts[] = {3, 2, 2, 1, 1};
        bool exp_flags[] = {true, true, true, false, false};
        run_test(4, 5, values, edges, 4, queries, 5, exp_counts, exp_flags);
    }

    // Test Case 5
    {
        int values[] = {8, 3, 10, 7, 6, 5, 2};
        int edges[][2] = {{1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}, {3, 7}};
        int queries[] = {1, 2, 3, 4};
        int exp_counts[] = {4, 2, 2, 1};
        bool exp_flags[] = {false, true, true, false};
        run_test(5, 7, values, edges, 6, queries, 4, exp_counts, exp_flags);
    }

    return 0;
}

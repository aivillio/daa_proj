
##  task 1 - Algorithm 
---
BACKTRACK():

    
    IF row == N:
        add copy of board to solutions
        RETURN

   
    FOR col FROM 0 TO N-1:

      
        IF (row, col) IN blocked_cells:
            CONTINUE

        
        IF col IN cols:
            CONTINUE

        
        IF (row - col) IN neg_diag:
            CONTINUE

        
        IF (row + col) IN pos_diag:
            CONTINUE

        
        board[row] <- col
        ADD col        TO cols
        ADD (row-col)  TO neg_diag
        ADD (row+col)  TO pos_diag

        
        BACKTRACK(row + 1, board, cols, neg_diag, pos_diag, solutions)

        
        REMOVE col        FROM cols
        REMOVE (row-col)  FROM neg_diag
        REMOVE (row+col)  FROM pos_diag

    
    RETURN



## Task 3 — Board Representation & Conflict Tracking

**Board representation:**

The board is stored as a 1D array of length N where `board[row] = col` records which column holds the vault in each row. This works because the one-vault-per-row constraint is always satisfied by construction — the backtracker places exactly one vault per row before moving to the next. A 2D matrix would carry the same information across N² cells, but N²−N of them would always be empty and serve no purpose.

**Conflict tracking:**

Three hash sets track occupied positions at all times:

- `cols` — stores occupied column indices. If `col in cols`, that column is taken.
- `neg_diag` — stores `row - col` values. All cells on the same main diagonal share the same `row - col` value.
- `pos_diag` — stores `row + col` values. All cells on the same anti-diagonal share the same `row + col` value.

Every placement adds to all three sets in O(1), and every removal (backtrack) deletes from all three in O(1). The conflict check at each cell is therefore three O(1) lookups — constant time regardless of N.

Rows never need a set because the algorithm advances one row at a time, so two vaults can never share a row by construction.

---

## Task 4 — Time Complexity Analysis

**Worst case:**

At row 0 there are N column choices. At row 1 at most N−1 remain (one column taken). At row 2 at most N−2, and so on. This gives an upper bound of:

O(N!)


In practice the diagonal constraints eliminate far more branches than just the column constraint, so the actual nodes explored are significantly fewer than N!. For reference:



**Effect of blocked cells:**

Blocked cells only ever shrink the search space. Each blocked cell at `(row, col)` eliminates one candidate from the loop at that row with a single `continue` — no recursive call is made. The more blocked cells there are, especially in early rows, the more subtrees are pruned before they are explored. Blocked cells never increase the worst case; they strictly reduce nodes visited.

---

## Task 5 — Pruning, Auxiliary Structures & Brute Force Comparison

**Pruning invalid placements early:**

The key pruning insight is to check constraints *before* recursing, not after. At each `(row, col)` candidate, if any of the three set lookups fail, the entire subtree rooted at that placement is skipped instantly. This is called *constraint propagation* — invalid states are detected at the earliest possible point in the search tree, avoiding wasted work on all descendants.

Without early pruning you would recurse into a known-invalid state and only discover the conflict several rows deeper, having explored many nodes needlessly.

**Auxiliary diagonal encoding:**

The diagonal sets use the mathematical insight that:
- All cells sharing a main diagonal have the same `row - col` value
- All cells sharing an anti-diagonal have the same `row + col` value

This encodes two-dimensional diagonal relationships as single integers, making lookup O(1). The naive alternative — scanning every previously placed vault and computing diagonal distance — would be O(N) per cell, adding a factor of N to every node in the tree and pushing the effective complexity toward O(N · N!).

**Comparison with brute force:**

| Approach | Strategy | Time complexity | N=8 states examined |
|---|---|---|---|
| Brute force | Generate all N^N placements, validate each | O(N^N) | ~16 million |
| Backtracking (no aux structures) | Recurse + O(N) conflict scan per cell | O(N · N!) | ~80,000 |
| Backtracking + hash sets | Recurse + O(1) conflict check | O(N!) | ~2,000 |
| Backtracking + hash sets + blocked cells | Same, skip blocked candidates early | < O(N!) | fewer still |

Brute force is completely impractical beyond N=8 or so because N^N grows catastrophically — N=10 gives 10 billion placements to generate and check. The backtracking solution with hash sets reduces this to tens of thousands of nodes for the same N, making it feasible well into N=15 and beyond.
def main(n,blocked_cells=set()):
    cols=set()
    pos_diag=set()
    neg_diag=set()
    board=[-1]*n
    sols=[]


    def backtrack(row):
        if row==n:
            sols.append(board[:])
            return
        else:
            for col in range(n):
                if col in cols or row+col in pos_diag or row-col in neg_diag or (row,col) in blocked_cells:
                    continue
                board[row]=col
                cols.add(col);pos_diag.add(row+col);neg_diag.add(row-col)

                backtrack(row+1)
                board[row]=-1
                cols.remove(col); neg_diag.remove(row-col); pos_diag.remove(row+col)
    backtrack(0)
    return sols

def print_board(solution, n, blocked_cells=None):
    if blocked_cells is None:
        blocked_cells = set()
    for row in range(n):
        line = []
        for col in range(n):
            if (row, col) in blocked_cells:
                line.append('X')
            elif solution[row] == col:   
                line.append('V')
            else:
                line.append('.')
        print(' '.join(line))
    print()
n = 6
blocked = {(0, 0), (2, 3)}

solutions = main(n, blocked)
print(f"N={n}, Blocked={blocked}")
print(f"Total valid configurations: {len(solutions)}\n")

if solutions:
    print("First solution:")
    print_board(solutions[0], n, blocked)
    print("Last solution:")
    print_board(solutions[-1], n, blocked)
    print(len(solutions))
        

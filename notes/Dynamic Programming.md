# Dynamic Programming

## What is DP

- Solve problem by **combining solutions to subproblems**.
- Trade space for time. (memoization)
- "狀態轉移"

## D&C vs DP

- D&C
  - Independent / disjoint subproblems.
  - Repeatedly solving common sub-subproblems.
  - Some times more work than necessary.
- DP
  - Dependent / overlapping subproblems: same subproblem visited several times.
  - Avoid recomputing the same problem.
    - Memoization
      - Better when not all subproblems need to be solved.
    - Topological sort & bottom up
      - Better when all subproblems need to be solved (no function call overhead).

## DP & optimization

**Optimal substructure**: an optimal solution can be constructed from optimal solutions to subproblems.

> Optimal substructure is required for DP to be correctly used in optimal problems

## Time analysis

- Method 1: (#subproblems) * (#choices for each subproblems)
- Method 2: subproblem graph
  - Illustrates how each subproblem depends on others.
  - Memoization is DFS.
  - Bottom up is Topological sort.

## Rod Cutting

### Problem

Different price for different length, not linear.

## Stamp

### Problem

Minimum stamps to cover the postage.

## Matrix Multiplication

### Problem

Given `n` matrices `A[1:n]`, minimize computation for multiplying them together by deciding the order of computation.

### Subproblem & Optimal Substructure

`M(i,j)` is the the minimal computation needed for `A[i:j]`.

## Weighted Task Scheduling

### Problem

Given `n` tasks with `s[n],f[n],v[n],p[n]`. `s` and `f` is the start and finish time, `v` is the value of that task. Tasks are sorted by `s`, `f`. `p[j]` is the last task compatible with task `j`.

### Subproblem & Optimal Substructure

`dp(i)` is the solution to the first `i` tasks.
Two cases for solution:

- Case 1: Task `i` is in solution, then choose `dp(p[i])`.
- Case 2: Task `i` isn't in solution, then choose `dp(i-1)`.

## Edit Distance

## 0-1 Knapsack

`dp(i,w)`: Max value with first `i` items & `w` capacity.

`dp(i,w) = max(dp(i-1,w), v_i+dp(i-1, w-w_i))`

Time complexity: $O(nW)$

## Unbounded Knapsack

`dp(w)`: Max value with `w` capacity.

`dp(w) = max(v_i+dp(w-w_i))`

Time complexity: $O(nW)$

## Bounded Size Knapsack

```pseudocode
function dp(n, W, D)
	M[n][W][D]
	for i from 0 to n
		for w from 0 to W
			for d from 0 to D
				if (i==0)	
					M[i][w][d] = 0
				else if w<w_i or d<d_i
					M[i][w][d] = M[i-1][w][d]
				else
					M[i][w][d] = max(v_i+M[i-1][w-w_i][d-d_i], M[i-1][w][d])
```




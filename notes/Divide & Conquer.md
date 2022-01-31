# Divide & Conquer

## What is D & C ?

- Solve the problem **recursively**
- Apply three steps:

  1. **Divide**: Divide the problem into several subproblems that are smaller instances of the same problem.
  2. **Conquer**: Conquer subproblems by solving them recursively. If the subproblem is small enough (aka base case) then just solve it.
  3. **Combine**: Combine solutions of subproblems to get the desired solution.
- Suitable for parallel computing (multicore / GPU)
- Efficient memory access

## Tower of Hanoi

### Problem

`f(n, A, C, B)`: move n disks from A to C

### Algorithm

Move the first `n-1` disks to spare, move largest disk, then move all disk to dest.

```pseudocode
function f(n, A, C, B)
	if (n==1)
		move disk from A to C
	else
		f(n-1, A, B, C)
		move disk from A to C
		f(n-1, B, C, A)
```

### Time complexity

$T(n)=2T(n-1)+1 \Rightarrow T(n)=O(2^n)$

## Merge Sort

### Algorithm

```pseudocode
function MergeSort(A, l, r)
	if l==r
		return
	m = (l+r-1)//2
	MergeSort(A, l, m)
	MergeSort(A, m+1, r)
	Merge(A, l, m, r) /* O(n) */
```

### Time complexity

$T(n)=2T(\frac{n}{2})+O(n) \Rightarrow T(n)=O(n\log{n})$

## Maximum subarray

### Problem

Find the consecutive subarray with maximum sum.

### Algorithm

- Split the array into two halves.
- There are three cases for the answer:
  - Case 1: The max subarray is in the left.
    - $T(n/2)$
  - Case 2: The max subarray is in the right.
    - $T(n/2)$
  - Case 3: The max subarray crosses the middle.
    - Start from middle, find max going left and right, then combine them.
    - $O(n)$

### Time Complexity

$T(n) = 2T(\frac{n}{2})+O(n)=O(n\log{n})$

## Master Theorem / Master Method

When recurrence relation is:
$$
T(n) =
\begin{cases}
O(1) &\text{if $n\le1$} \\
a\cdot T(\frac{n}{b})+f(n) &\text{if $n>1$} \\
\end{cases}
$$
Compare $f(n)$ with $n^{\log_ba}$:

- Case 1: $f(n)$ is polynomially slower than $n^{\log_ba}$.
  - 
- Case 2: They grows similarly.
- Case 3: $f(n)$ is polynomially faster than $n^{\log_ba}$.

Note: $\log{n} = O(n^{\epsilon})\;\forall\;\epsilon>0$ 




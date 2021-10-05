// refs & ppl discussed with:
// https://cp.wiwiho.me/fenwick-tree/
// https://oi-wiki.org/misc/discrete/
// b09902100

// deja vu? dsa hw2 p5 

// #include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

#define lli long long int

// x_i = b*p_i+c
// y_i = a*p_i
// z_i = z_i
const int MAX_Z = 1e9;
const int MIN_Z = 0;
const int MAX_N = 2*(1e6)+10;

using namespace std;

void insertBIT(vector<int> &BIT, int x) {
	for (; x<BIT.size(); x+=x&(-x)) {
		BIT[x]++;
	}
}

int queryBIT(vector<int> &BIT, int t) {
	int ans=0;
	for (; t>0; t-=t&(-t)) {
		ans += BIT[t];
	}
	return ans;
}

int myCmp(const void *a, const void *b) {
    lli sub = *(lli*)a - *(lli*)b;
    if (sub > 0) return 1;
    else if (sub < 0) return -1;
    else return 0;
}

lli vecs[MAX_N][3];

int main() {
	// ios_base::sync_with_stdio(false);
	// cin.tie(nullptr);
	int N;
	lli a, b, c;
	// cin >> N >> a >> b >> c;
	scanf("%d %lld %lld %lld", &N, &a, &b, &c);
	
	vector<lli> sorted_int(N);
	for (int i=0; i<N; i++) {
		lli p_i, z_i;
		// cin >> p_i >> z_i;
		scanf("%lld %lld", &p_i, &z_i);
		vecs[i][0] = z_i;
		vecs[i][1] = b*p_i+c;
		vecs[i][2] = a*p_i;
		sorted_int[i] = b*p_i+c;
	}
	
	// remap x_i and y_i to a smaller range
	sort(sorted_int.begin(), sorted_int.end());
	auto uq = unique(sorted_int.begin(), sorted_int.end());
	// sorted_int.erase(unique(sorted_int.begin(), sorted_int.end()), sorted_int.end());

	// sort by z_i
	qsort(vecs, N, 3*sizeof(lli), myCmp);
	lli sum_d = 0;

	// build a binary indexed tree to store x_i
	// vector<int> BIT(sorted_int.size()+10, 0);
	vector<int> BIT(uq-sorted_int.begin()+10, 0);
	int hold_x[N];
	int holding=0;
	lli old_z = MIN_Z - 1;
	for (int i=0; i<N; i++) {
		lli z_i = vecs[i][0];
		// int x_i = lower_bound(sorted_int.begin(), sorted_int.end(), vecs[i][1])-sorted_int.begin()+1;
		// int y_i = lower_bound(sorted_int.begin(), sorted_int.end(), vecs[i][2])-sorted_int.begin()+1;
		int x_i = lower_bound(sorted_int.begin(), uq, vecs[i][1])-sorted_int.begin()+1;
		int y_i = lower_bound(sorted_int.begin(), uq, vecs[i][2])-sorted_int.begin()+1;
		if (z_i != old_z) {
			// insert all holding x if on a new z value
			while (holding) {
				holding--;
				insertBIT(BIT, hold_x[holding]);
			}
			old_z = z_i;
		}
		// query prefix sum
		sum_d += (lli) queryBIT(BIT, y_i-1);
		// add x_i to holding x
		hold_x[holding] = x_i;
		holding++;
	}

	// cout << sum_d << endl;
	printf("%lld\n", sum_d);
	return 0;
}

// refs & ppl discussed with:
// https://cp.wiwiho.me/fenwick-tree/
// https://oi-wiki.org/misc/discrete/
// b09902100

// deja vu? dsa hw2 p5 

// #include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>

#define lli long long int


// x_i = b*p_i+c
// y_i = a*p_i
// z_i = z_i
const int MAX_Z = 1e9;
const int MIN_Z = 0;


using namespace std;

// bool cmpVec(vector<lli> &v_a, vector<lli> &v_b) {
// 	return (v_a[2] < v_b[2]);
// }

void insertBIT(vector<int> &BIT, int x) {
	for (int i=x; i<BIT.size(); i+=i&(-i)) {
		BIT[i]++;
	}
}

int queryBIT(vector<int> &BIT, int target) {
	int ans=0;
	for (int i=target; i>0; i-=i&(-i)) {
		ans += BIT[i];
	}
	return ans;
}

// int BSIndex(vector<lli> v, lli target) {
// 	int l=0, r=v.size()-1;
// 	while (l<=r) {
// 		int m = (l+r)/2;
// 		if (v[m] == target) return m;
// 		else if (v[m] > target) r=m-1;
// 		else if (v[m] < target) l=m+1;
// 	}
// 	return l;
// }


int main() {
	// ios_base::sync_with_stdio(false);
	// cin.tie(nullptr);
	
	int N;
	lli a, b, c;
	// cin >> N >> a >> b >> c;
	scanf("%d %lld %lld %lld", &N, &a, &b, &c);
	
	vector< vector<lli> > vecs(N, vector<lli>(3));
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
	sorted_int.erase(uq, sorted_int.end());

	// sort by z_i
	sort(vecs.begin(), vecs.end());
	
	lli sum_d = 0;

	// build a binary indexed tree to store x_i
	vector<int> BIT(sorted_int.size()+10, 0);
	vector<int> hold_x;
	lli old_z = MIN_Z - 1;
	for (int i=0; i<N; i++) {
		lli z_i = vecs[i][0];
		int x_i = lower_bound(sorted_int.begin(), sorted_int.end(), vecs[i][1])-sorted_int.begin()+1;
		int y_i = lower_bound(sorted_int.begin(), sorted_int.end(), vecs[i][2])-sorted_int.begin()+1;
		if (z_i != old_z) {
			// insert all holding x if on a new z value
			while (! hold_x.empty()) {
				insertBIT(BIT, hold_x.back());
				hold_x.pop_back();
			}
			old_z = z_i;
		}
		// query prefix sum
		lli query = (lli) queryBIT(BIT, y_i-1);
		sum_d += query;
		// add x_i to holding x
		hold_x.push_back(x_i);
	}

	// cout << sum_d << endl;
	printf("%lld\n", sum_d);
	return 0;
}

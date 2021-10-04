// refs & ppl discussed with:
// https://en.wikipedia.org/wiki/Tower_of_Hanoi#Binary_solution
// b09902011 b09902100

#include <iostream>

#define MAX_N 100005
#define RM 998244353
#define lli long long int
using namespace std;

lli calc_steps(int* peg, int n) {
	lli steps = 0;
	lli bt = 0;
	if (peg[n] == 0) bt = 1;
	steps = ((steps << 1)%RM + bt)%RM;
	//cout << bt << endl;
	for (int i=n-1; i>=1; i--) {
		if (peg[i] != peg[i+1]) bt = 1-bt;
		//cout << bt << endl;
		steps = ((steps << 1)%RM + bt)%RM;
	}
	return steps;
}

int check_valid(int* peg, int n, int st, int md, int ed) {	
	if (peg[n] == md) {
		return 0;
	} else if (peg[n] == st) {
		if (n == 1) return 1;
		else return check_valid(peg, n-1, st, ed, md);
	} else if (peg[n] == ed) {
		if (n == 1) return 1;
		else return check_valid(peg, n-1, md, st, ed);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int disk_n;
	cin >> disk_n;
	int peg[MAX_N];
	int peg_cnt;
	cin >> peg_cnt;
	for (int i=0; i<peg_cnt; i++) {
		int disk;
		cin >> disk;
		peg[disk] = 0;
	}
	cin >> peg_cnt;
	for (int i=0; i<peg_cnt; i++) {
		int disk;
		cin >> disk;
		peg[disk] = 1;
	}
	cin >> peg_cnt;
	for (int i=0; i<peg_cnt; i++) {
		int disk;
		cin >> disk;
		peg[disk] = 2;
	}
	
	if (check_valid(peg, disk_n, 0, 1, 2)) {
		cout << calc_steps(peg, disk_n) << "\n";
	} else {
		cout << -1 << "\n";
	}

	return 0;
}

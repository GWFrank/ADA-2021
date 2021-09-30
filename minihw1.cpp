#include <iostream>
#include <algorithm>

#define MAXN 200005
#define lli long long int
using namespace std;


lli solve(int* song, int st, int ed, lli x, lli y, lli z) {
	if (ed-st == 1) {
		return x*song[st] + z*song[ed];
	} else if (ed-st == 2){
		lli case1 = x*song[st] + y*song[st+1] + z*song[ed];
	   	lli case2 = x*song[st] + z*song[st+1];
		lli case3 = x*song[st+1] + z*song[ed];
		return max({case1, case2, case3});
	}
	// recursive
	int split = (st+ed)/2;

	lli l_best = solve(song, st, split, x, y, z);
	lli r_best = solve(song, split+1, ed, x, y, z);

	lli l_cur = x*song[split];
	lli l_re = l_cur;
	for (int i=split-1; i>=st; i--) {
		l_cur -= x*song[i+1];
		l_cur += y*song[i+1] + x*song[i];
		if (l_cur > l_re) {
			l_re = l_cur;
		}
	}
	
	lli r_cur = z*song[split+1];
	lli r_re = r_cur;
	for (int i=split+2; i<=ed; i++) {
		r_cur -= z*song[i-1];
		r_cur += y*song[i-1] + z*song[i];
		if (r_cur > r_re) {
			r_re = r_cur;
		}
	}
	
	lli m_best = l_re + r_re;
	//cout << st << ", " << ed << endl;
   	//cout << l_best << ", " << m_best << ", " << r_best << endl;
	
	return max({l_best, r_best, m_best});
	
}

int main() {
    int N;
	lli x, y, z;
    cin >> N >> x >> y >> z;
    int song[MAXN];
    for (int i=0; i<N; i++){
        cin >> song[i];
    }
	cout << solve(song, 0, N-1, x, y, z) << endl;

    return 0;
}

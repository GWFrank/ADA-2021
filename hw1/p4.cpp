#include <iostream>
#include <stdlib.h>

#define lli long long int 

const int MAX_N = 1e5;

using namespace std;

int mySign(lli x) {
    return (x>0) ? 1:-1;
}

typedef struct __sol {
    lli sum;
    int* idx;
    int cnt=0;
} sol;


sol solve(lli* candies, int N, int flag) {
    sol ans;
    sol max_neg;
    
    ans.idx = (int*) malloc(N*sizeof(int));
    max_neg.idx = (int*) malloc(N*sizeof(int));

    ans.sum = candies[0];
    ans.idx[0] = 0;
    ans.cnt = 1;
    if (candies[0] <= 0) {
        max_neg.sum = candies[0];
        max_neg.idx[0] = 0;
        max_neg.cnt = 1;
    } else {
        max_neg.sum = -(1e9)-10;
        max_neg.idx[0] = 0;
        max_neg.cnt = 1;
    }

    for (int i=1; i<N; i++) {
        if (candies[i] > 0) {
            if (candies[i] > ans.sum){
                ans.sum = candies[i];
                ans.idx = (int*) malloc(N*sizeof(int));
                ans.idx[0] = i;
                ans.cnt = 1;
            }
            if ((candies[i]+max_neg.sum) > ans.sum) {
                ans.sum = candies[i]+max_neg.sum;
                if (flag) {
                    if (ans.idx != max_neg.idx) {
                        int* tmp = ans.idx;
                        ans.idx = max_neg.idx;
                        free(tmp);
                        // for (int j=0; j<max_neg.cnt; j++) {
                        //     ans.idx[j] = max_neg.idx[j];
                        // }
                    }
                    ans.idx[max_neg.cnt] = i;
                    ans.cnt = max_neg.cnt+1;
                }
            }
        } else {
            if (ans.sum + candies[i] > max_neg.sum) {
                max_neg.sum = candies[i]+ans.sum;
                if (flag) {
                    if (max_neg.idx != ans.idx) {
                        int* tmp = max_neg.idx;
                        max_neg.idx = ans.idx;
                        free(tmp);
                        // for (int j=0; j<ans.cnt; j++) {
                        //     max_neg.idx[j] = ans.idx[j];
                        // }
                    }
                    max_neg.idx[ans.cnt] = i;
                    max_neg.cnt = ans.cnt+1;
                }
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, N, flag;
    cin >> T >> flag;
    for (int i=0; i<T; i++) {
        lli candies[MAX_N];
        int og_idx[MAX_N];
        cin >> N;
        for (int j=0; j<N; j++) {
            cin >> candies[j];
        }

        // leave largest num in consective part
        int ed=1, ed_sign=mySign(candies[0]);
        og_idx[0] = 0;
        for (int j=1; j<N; j++) {
            if (mySign(candies[j]) == ed_sign) {
                if (candies[j] > candies[ed-1]) {
                    candies[ed-1] = candies[j];
                    og_idx[ed-1] = j;
                }
            } else {
                ed++;
                candies[ed-1] = candies[j];
                og_idx[ed-1] = j;
                ed_sign = -ed_sign;
            }
        }
        N = ed;

        // testing
        // for (int j=0; j<ed; j++) {
        //     cout << og_idx[j] << ": " << candies[j] << "\n";
        // }

        // /*
        sol solution = solve(candies, N, flag);

        cout << solution.sum << "\n";
        if (flag) {
            cout << solution.cnt;
            for (int j=0; j<solution.cnt; j++) {
                cout << " " << og_idx[solution.idx[j]]+1;
            }
            cout << "\n";
        }
        // */
    }

    return 0;
}

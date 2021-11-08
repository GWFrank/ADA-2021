#include <iostream>
#include <numeric>
#include <algorithm>
#define lli long long int

using namespace std;

const int max_n = 500;
int n, a[max_n];
lli dp[max_n][max_n], gcd_table[max_n][max_n];

lli solve_dp(int i, int j) {
    if (i > j) return -1;
    if (dp[i][j] != 0) return dp[i][j];
    dp[i][j] = -1;
    switch (j-i) {
        case 0:
            return dp[i][j];
        case 1:
            if (gcd_table[i][j] != 1) dp[i][j] = gcd_table[i][j];
            return dp[i][j];
        case 2:
            if (gcd_table[i][j] != 1
                && gcd_table[i][i+1] != 1
                && gcd_table[i+1][j] != 1) {
                dp[i][j] = gcd_table[i][i+1] + gcd_table[i+1][j];
            }
            return dp[i][j];
    }

    if (gcd_table[i][j] != 1) {
        // case 1
        if (solve_dp(i+1, j-1) > 0) {
            dp[i][j] = max(dp[i][j], gcd_table[i][j] + dp[i+1][j-1]);
        }
        // case 2
        for (int k=i+1; k<j; k++) {
            if (gcd_table[i][k]!=1 && gcd_table[k][j]!=1) {
                if (k!=i+1 && k!=j-1) { // case 2-1
                    if (solve_dp(i+1, k-1) > 0 && solve_dp(k+1, j-1) > 0) {
                        dp[i][j] = max(dp[i][j], dp[i+1][k-1]+dp[k+1][j-1]+gcd_table[i][k]+gcd_table[k][j]);
                    }
                } else if (k==i+1) { // case 2-2
                    if (solve_dp(k+1, j-1) > 0) {
                        dp[i][j] = max(dp[i][j], dp[k+1][j-1]+gcd_table[i][k]+gcd_table[k][j]);
                    }
                } else if (k==j-1) { // case 2-3
                    if (solve_dp(i+1, k-1) > 0) {
                        dp[i][j] = max(dp[i][j], dp[i+1][k-1]+gcd_table[i][k]+gcd_table[k][j]);
                    }
                }
            }
        }
    }
    // case 3
    for (int m=i+1; m<j-1; m++) {
        if (solve_dp(i, m) > 0 && solve_dp(m+1, j) > 0) {
            dp[i][j] = max(dp[i][j], dp[i][m]+dp[m+1][j]);
        }
    }

    return dp[i][j];
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> a[i];
    }
    for (int i=0; i<n; i++) {
        for (int j=i; j<n; j++) {
            gcd_table[i][j] = (lli) gcd(a[i], a[j]);
            gcd_table[j][i] = gcd_table[i][j];
            dp[i][j] = 0; dp[j][i] = 0;
        }
    }
    cout << solve_dp(0, n-1) << endl;
    return 0;
}
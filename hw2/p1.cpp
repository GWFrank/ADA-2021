// #include <iostream>
// #include <stdlib.h>
#include <bits/stdc++.h>

#define lli long long int
#define MAX_N 400
#define MAX_M 400
#define MAX_K 800

using namespace std;

lli DP[MAX_N][MAX_M][MAX_K];
lli reward[MAX_N][MAX_M];
int parent[MAX_N][MAX_M][MAX_K][2];

lli toNum(string &s) {
    if(s[0] == 'X') {
        return INT64_MIN;
    }
    int neg=0;
    lli num=0;
    int i=0;
    if (s[i] == '-') {
        neg=1; i++;
    }
    for (; i<s.length(); ++i) {
        num = num*10+(s[i]-'0');
    }
    // if (neg) num=-num;
    // return num;
    return neg ? -num : num;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T, n, m, step;
    cin >> T;
    // T=1;
    for (int t=0; t<T; ++t) {
        // cout << "howdy0" << endl;
        cin >> n >> m >> step;
        // memset(DP, 0, sizeof(DP));
        // memset(reward, 0, sizeof(reward));
        // memset(parent, 0, sizeof(parent));
        // cout << "howdy1" << endl;
        // cout << n << " " << m << " " << step << endl;
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                string s;
                cin >> s;
                reward[i][j] = toNum(s);
            }
        }
        // cout << "howdy2" << endl;
        for (int i=0; i<n; ++i) {
            for (int j=0; j<m; ++j) {
                DP[i][j][0] = INT64_MIN;
                for (int k=step; k>0; --k) {
                    DP[i][j][k] = INT64_MIN;
                    // cout << i << "," << j << "," << k << endl;
                    if (i-1 >= 0) {
                        // cout << "compare to above" << endl;
                        // cout << DP[i-1][j][k-1] << endl;
                        if (DP[i-1][j][k-1] > DP[i][j][k]) {
                            DP[i][j][k] = DP[i-1][j][k-1];
                            if (k-1 != 0) {
                                parent[i][j][k][0] = parent[i-1][j][k-1][0];
                                parent[i][j][k][1] = parent[i-1][j][k-1][1];
                            } else {
                                parent[i][j][k][0] = i-1;
                                parent[i][j][k][1] = j;
                            }
                        }
                    }
                    if (j-1 >= 0) {
                        // cout << "compare to left" << endl;
                        // cout << DP[i][j-1][k-1] << endl;
                        if (DP[i][j-1][k-1] > DP[i][j][k]) {
                            DP[i][j][k] = DP[i][j-1][k-1];
                            if (k-1 != 0) {
                                parent[i][j][k][0] = parent[i][j-1][k-1][0];
                                parent[i][j][k][1] = parent[i][j-1][k-1][1];
                            } else {
                                parent[i][j][k][0] = i;
                                parent[i][j][k][1] = j-1;
                            }
                        }
                    }
                    if (DP[i][j][k] > DP[i][j][0]) {
                        DP[i][j][0] = DP[i][j][k];
                        parent[i][j][0][0] = parent[i][j][k][0];
                        parent[i][j][0][1] = parent[i][j][k][1];
                    }
                }
                if (i==0 && j==0) {
                    DP[i][j][0] = 0;
                }
                if (DP[i][j][0] > INT64_MIN) {
                    if (reward[i][j] > INT64_MIN) {
                        DP[i][j][0] += reward[i][j];
                    } else {
                        DP[i][j][0] = INT64_MIN;
                    }
                    
                }
            }
        }
        // for (int k=0; k<=step; k++) {
        //     cout << "k=" << k << endl;
        //     for (int i=0; i<n; i++) {
        //         for (int j=0; j<m; j++) {
        //             cout << DP[i][j][k] << " ";
        //         }
        //         cout << endl;
        //     }
        // }
        // cout << "reward=" << DP[n][m][0] << endl;
        if (DP[n-1][m-1][0] == INT64_MIN) {
            cout << "Impassable\n";
        } else {
            int path[MAX_N+MAX_M][2];
            int path_len=0;
            int row=n-1, col=m-1;
            while (!(row==0 && col==0)) {
                path[path_len][0] = row+1;
                path[path_len][1] = col+1;
                int *coord = parent[row][col][0];
                row = coord[0];
                col = coord[1];
                path_len++;
            }
            path[path_len][0]=1; path[path_len][1]=1;
            path_len++;
            cout << "Passable\n" << DP[n-1][m-1][0] << "\n" << path_len << "\n";
            for (int i=path_len-1; i>=0; i--) {
                cout << path[i][0] << " " << path[i][1] << "\n";
            }
        }

    }
    return 0;
}
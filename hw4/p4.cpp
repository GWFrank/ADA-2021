#include <bits/stdc++.h>
typedef long long lli;
// using namespace std;
using std::vector;
using std::pair;
using std::cin;
using std::cerr;
using std::cout;
using std::abs;
using std::max;

lli cutValue(int i, vector<lli> &b, int N) {
    if (i > 0)
        return - abs(b[i+1]-b[i])
               + b[i+1] * ((b[i]&b[i+1]) ^ (b[i+1]|b[i+2]) ^ (b[i]+b[i+2]))
               + b[i]   * ((b[i-1]&b[i]) ^ (b[i]|b[i+1])   ^ (b[i-1]+b[i+1]));
    else
        return - abs(b[1]-b[0])
               + b[1] * ((b[0]&b[1])   ^ (b[1]|b[2]) ^ (b[0]+b[+2]))
               + b[0] * ((b[N-1]&b[0]) ^ (b[0]|b[1]) ^ (b[N-1]+b[1]));
}

lli overlapValue(int i, int j, vector<lli> &b, int N) {
    if (j != i+1) {
        return 0;
    } else {
        if (i<0)
            return b[0] * ((b[N-1]&b[0]) ^ (b[0]|b[1]) ^ (b[N-1]+b[1]));
        else
            return b[i+1] * ((b[i]&b[i+1]) ^ (b[i+1]|b[i+2]) ^ (b[i]+b[i+2]));
    }
}

void printVec(vector<vector<lli>> &v) {
    cerr << "------\n";
    for (auto it=v.begin(); it!=v.end(); ++it) {
        for (auto itt=(*it).begin(); itt!=(*it).end(); ++itt) {
            cerr << *itt << " ";
        }
        cerr << "\n";
    }
    cerr << "------\n";
}
void printVec2(vector<vector<int>> &v) {
    cerr << "------\n";
    for (auto it=v.begin(); it!=v.end(); ++it) {
        for (auto itt=(*it).begin(); itt!=(*it).end(); ++itt) {
            cerr << *itt << " ";
        }
        cerr << "\n";
    }
    cerr << "------\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    cin >> N >> M;
    vector<lli> b(N+2);
    for (int i=0; i<N; ++i)
        cin >> b[i];
    b[N] = b[0]; b[N+1] = b[1]; // for the sake of simpler code
    
    lli total_val = 0;
    for (int i=0; i<N; ++i) {
        total_val += b[i+1]*((b[i]&b[i+1]) ^ (b[i+1]|b[i+2]) ^ (b[i]+b[i+2]));
        total_val -= abs(b[i+1]-b[i]);
        total_val += b[i];
    }

    // Case 1: Cut at (b[n-1], b[0])
    // dp1[m][n] = m cuts for the first n elements
    vector<vector<lli>> dp1(M+1, vector<lli>(N)); // cut value
    vector<vector<int>> dp1_lc(M+1, vector<int>(N)); // last cut pos
    for (int m=1; m<=M; ++m) {
        for (int n=max(0,m-2); n<N; ++n) {
            if (m == 1) {
                // base case
                dp1[m][n] = cutValue(N-1, b, N);
                dp1_lc[m][n] = -1;
            } else if (m == 2) {
                if (n == N-1) { // this cut is already counted
                    // (m, n-1) -> (m, n)
                    dp1[m][n] = dp1[m][n-1];
                    dp1_lc[m][n] = dp1_lc[m][n-1];
                    continue;
                }
                // base case
                dp1[m][n] = cutValue(N-1, b, N)
                            + cutValue(n, b, N)
                            - overlapValue(-1, n, b, N)
                            - overlapValue(n, N-1, b, N);
                dp1_lc[m][n] = n;
                // (m, n-1) -> (m, n)
                if (n>=m-1 && dp1[m][n-1] > dp1[m][n]) {
                    dp1[m][n] = dp1[m][n-1];
                    dp1_lc[m][n] = dp1_lc[m][n-1];
                }
            }else {
                if (n == N-1) { // this cut is already counted
                    // (m, n-1) -> (m, n)
                    dp1[m][n] = dp1[m][n-1];
                    dp1_lc[m][n] = dp1_lc[m][n-1];
                    continue;
                }
                // (m-1, n-1) -> (m, n)
                dp1[m][n] = dp1[m-1][n-1]
                            + cutValue(n, b, N)
                            - overlapValue(dp1_lc[m-1][n-1], n, b, N)
                            - overlapValue(n, N-1, b, N);
                dp1_lc[m][n] = n;
                // (m-1, n-2) -> (m, n)
                if (n-2>=0 && n>=m-1 && dp1_lc[m-1][n-1] == n-1) {
                    lli tmp = dp1[m-1][n-2]
                              + cutValue(n, b, N)
                              - overlapValue(dp1_lc[m-1][n-2], n, b, N)
                              - overlapValue(n, N-1, b, N);
                    if (tmp > dp1[m][n]) {
                        dp1[m][n] = tmp;
                        dp1_lc[m][n] = n;
                    }
                }
                // (m, n-1) -> (m, n)
                if (n>=m-1 && dp1[m][n-1] > dp1[m][n]) {
                    dp1[m][n] = dp1[m][n-1];
                    dp1_lc[m][n] = dp1_lc[m][n-1];
                }
            }
        }
    }
    // printVec(dp1);
    // printVec2(dp1_lc);
    // Case 2: No cut at (b[n-1], b[0])
    vector<vector<lli>> dp2(M+1, vector<lli>(N)); // cut value
    vector<vector<int>> dp2_lc(M+1, vector<int>(N)); // last cut pos
    for (int m=0; m<=M; ++m) {
        for (int n=max(0, m-1); n<N; ++n) {
            if (m == 0) {
                // base case
                dp2[m][n] = 0;
                dp2_lc[m][n] = -1;
            } else if (m == 1) {
                if (n == N-1) { // no this cut
                    // (m, n-1) -> (m, n)
                    dp2[m][n] = dp2[m][n-1];
                    dp2_lc[m][n] = dp2_lc[m][n-1];
                    continue;
                }
                // base case
                dp2[m][n] = cutValue(n, b, N);
                dp2_lc[m][n] = n;
                // (m, n-1) -> (m, n)
                if (n>m-1 && dp2[m][n-1] > dp2[m][n]) {
                    dp2[m][n] = dp2[m][n-1];
                    dp2_lc[m][n] = dp2_lc[m][n-1];
                }
            } else {
                if (n == N-1) { // no this cut
                    // (m, n-1) -> (m, n)
                    dp2[m][n] = dp2[m][n-1];
                    dp2_lc[m][n] = dp2_lc[m][n-1];
                    continue;
                }
                // (m-1, n-1) -> (m, n)
                dp2[m][n] = dp2[m-1][n-1]
                            + cutValue(n, b, N)
                            - overlapValue(dp2_lc[m-1][n-1], n, b, N);
                dp2_lc[m][n] = n;
                // (m-1, n-2) -> (m, n)
                if (n-2>=0 && n>m-1 && dp2_lc[m-1][n-1] == n-1) {
                    lli tmp = dp2[m-1][n-2]
                              + cutValue(n, b, N)
                              - overlapValue(dp2_lc[m-1][n-2], n, b, N);
                    if (tmp > dp2[m][n]) {
                        dp2[m][n] = tmp;
                        dp2_lc[m][n] = n;
                    }
                }
                // (m, n-1) -> (m, n)
                if (n>m-1 && dp2[m][n-1] > dp2[m][n]) {
                    dp2[m][n] = dp2[m][n-1];
                    dp2_lc[m][n] = dp2_lc[m][n-1];
                }
            }
        }
    }
    // printVec(dp2);
    // printVec2(dp2_lc);
    // cerr << dp1[M][N-1] << "\n";
    // cerr << dp2[M][N-1] << "\n";
    // cerr << total_val << "\n";
    cout << total_val - max(dp1[M][N-1], dp2[M][N-1]) << "\n";
    return 0;
}
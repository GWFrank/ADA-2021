#include <bits/stdc++.h>
typedef long long lli;
using namespace std;

lli val2(const int &pos, const vector<lli> &b, const int &N) {
    return abs(b[pos%N] - b[(pos-1)%N]);
}

lli val3(const int &pos, const vector<lli> &b, const int &N) {
    return b[pos%N] * ((b[(pos-1)%N]&b[pos%N]) ^ (b[pos%N]|b[(pos+1)%N]) ^ (b[(pos-1)%N]+b[(pos+1)%N]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<lli> b(N);
    for (int i=0; i<N; ++i) {
        cin >> b[i];
    }

    lli total_val = 0;
    for (int i=0; i<N; ++i) {
        total_val += b[i];
        total_val -= val2(i, b, N);
        total_val += val3(i, b, N);
    }

    // (i, j, k{0, 1}) -> first i elements, cut j times, cut at i is k
    // cut at i = cut between (i-1, i)
    vector<vector<vector<int>>> dp( N, vector<vector<int>>( M+1, vector<int>(2, total_val) ) );
    dp[0][0][0] = total_val;
    dp[0][1][1] = total_val + val2(0, b, N) - val3(0, b, N) - val3(-1, b, N);
    for (int j=1; j<M; ++j) {
        for (int i=1; i<N; ++i) {
            dp[i][j][0] = dp[i-1][j][0];
            dp[i][j][0] = min(dp[i-1][j][0], dp[i-1][j][1]);
        }
    }



    return 0;
}
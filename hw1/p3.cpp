// refs & ppl discussed with:
// b09902100

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#define lli long long int

using namespace std;

const int MAX_N = 2*1e5;

struct point {
    int x, y;
    const bool operator < (const point &a) const{
        return (y < a.y);
    }
    const bool operator < (const int &a) const{
        return (y < a);
    }
    const bool operator > (const int &a) const{
        return (y > a);
    }
};

int myCmp(const void *a, const void *b) {
    return ((point*)a)->x - ((point*)b)->x;
}

void mySwap(int &a, int&b) {
    a=a^b; b=a^b; a=a^b;
}

void printStk(vector<point> &s) {
    for (auto &v : s) {
        cout << "(" << v.x << "," << v.y << "), ";
    }
    cout << "\n";
}

lli solve(point* pts,int N) {
    if (N==1) {
        return 0;
    } else if (N==2) {
        if (pts[0].y > pts[1].y) {
            mySwap(pts[0].x, pts[1].x);
            mySwap(pts[0].y, pts[1].y);
        }
        return 1;
    }

    lli l_pairs = solve(pts, N/2);
    lli r_pairs = solve(&(pts[N/2]), (N-N/2));

    lli m_pairs = 0;
    point merged[N];
    int l_idx=0, r_idx=N/2, merged_idx=0;
    vector<point> l_stk, r_stk;
    while (l_idx < N/2 && r_idx < N) {
        if (pts[l_idx].y < pts[r_idx].y) {
            while(!l_stk.empty()) {
                if (l_stk.back().x < pts[l_idx].x) l_stk.pop_back();
                else break;
            }
            int l_prev = (l_stk.empty()) ? 0 : l_stk.back().y;
            m_pairs += (lli)(r_stk.size() - (lower_bound(r_stk.begin(), r_stk.end(), l_prev)-r_stk.begin()));
            l_stk.push_back(pts[l_idx]);
            merged[merged_idx] = pts[l_idx];
            l_idx++;
            merged_idx++;
        } else {
            while(!r_stk.empty()) {
                if (r_stk.back().x > pts[r_idx].x) r_stk.pop_back();
                else break;
            }
            int r_prev = (r_stk.empty()) ? 0 : r_stk.back().y;
            m_pairs += (lli)(l_stk.size() - (lower_bound(l_stk.begin(), l_stk.end(), r_prev)-l_stk.begin()));
            r_stk.push_back(pts[r_idx]);
            merged[merged_idx] = pts[r_idx];
            r_idx++;
            merged_idx++;
        }
        
    }
    while (l_idx < N/2) {
        while(!l_stk.empty()) {
            if (l_stk.back().x < pts[l_idx].x) l_stk.pop_back();
            else break;
        }
        int l_prev = (l_stk.empty()) ? 0 : l_stk.back().y;
        m_pairs += (lli)(r_stk.size() - (lower_bound(r_stk.begin(), r_stk.end(), l_prev)-r_stk.begin()));
        l_stk.push_back(pts[l_idx]);
        merged[merged_idx] = pts[l_idx];
        l_idx++;
        merged_idx++;
    }
    while (r_idx < N) {
        while(!r_stk.empty()) {
            if (r_stk.back().x > pts[r_idx].x) r_stk.pop_back();
            else break;
        }
        int r_prev = (r_stk.empty()) ? 0 : r_stk.back().y;
        m_pairs += (lli)(l_stk.size() - (lower_bound(l_stk.begin(), l_stk.end(), r_prev)-l_stk.begin()));
        r_stk.push_back(pts[r_idx]);
        merged[merged_idx] = pts[r_idx];
        r_idx++;
        merged_idx++;
    }

    for (; merged_idx>0; merged_idx--) {
        pts[merged_idx-1] = merged[merged_idx-1];
    }
    // cout << 0 << ":" << N/2-1 << " for " << l_pairs << "\n";
    // cout << N/2 << ":" << N-1 << " for " << r_pairs << "\n";
    // cout << l_pairs+r_pairs+m_pairs << " @ N="  << N << "\n";
    return l_pairs+r_pairs+m_pairs;
}


int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    int N;
    point pts[MAX_N];
    cin >> N;
    for (int i=0; i<N; i++) {
        cin >> pts[i].x >> pts[i].y;
    }
    qsort(pts, N, 2*sizeof(int), myCmp);

    cout << solve(pts, N) << endl;

    return 0;
}
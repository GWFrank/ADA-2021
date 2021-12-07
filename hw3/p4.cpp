// Refs & ppl discussed with
// b09902100

#include <bits/stdc++.h>

#define lli long long int

using namespace std;

struct djs_node {
    int p, rk, sz;
    djs_node() = default;
    djs_node(int _p, int _rk, int _sz) : p(_p), rk(_rk), sz(_sz) {}
};

int findSet(int val, vector<djs_node> &djs) {
    if (djs[val].p == val) {
        return val;
    } else {
        djs[val].p = findSet(djs[val].p, djs);
        return djs[val].p;
    }
}

lli unionSet(int sa, int sb, vector<djs_node> &djs) {
    lli crowd_diff = (lli) djs[sa].sz * (lli) djs[sb].sz;
    if (djs[sa].rk < djs[sb].rk) {
        swap(sa, sb);
    }
    if (djs[sa].rk == djs[sb].rk) {
        djs[sa].rk += 1;
    }
    djs[sb].p = sa;
    djs[sa].sz += djs[sb].sz;
    return crowd_diff;
}

void placeFood(int p, int r, vector<djs_node> &djs, map<int, int> &garden, lli &crowd) {
    auto left=garden.lower_bound(p-r);
    auto right=garden.upper_bound(p+r);
    for (auto it=left; it!=right; it++) {
        int main_set = findSet(left->second, djs);
        int merged_set = findSet(it->second, djs);
        if (main_set != merged_set) {
            crowd += unionSet(main_set, merged_set, djs);
        }
    }
    if (left != right) {
        int boss = findSet(left->second, djs);
        garden.erase(left, right);
        garden[p] = boss;
    }
}

void moveCat(int t, int x, vector<djs_node> &djs, vector<int> &djs_idx, map<int, int> &garden, lli &crowd) {
    int og_set = findSet(djs_idx[t], djs);
    djs[og_set].sz -= 1;
    crowd -= (lli) djs[og_set].sz;
    djs_idx[t] = djs.size();
    djs.push_back(djs_node(djs_idx[t], 0, 1));
    if (!garden.count(x)) {
        garden[x] = djs_idx[t];
    } else {
        int main_set = findSet(garden[x], djs);
        crowd += unionSet(main_set, djs_idx[t], djs);
        garden[x] = findSet(djs_idx[t], djs);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    
    vector<djs_node> djs(n+1);
    vector<int> djs_idx(n+1);
    map<int, int> garden;
    lli crowd=0;
    for (int i=1; i<=n; i++) {
        int pos_x;
        cin >> pos_x;
        djs_idx[i] = i;
        djs[i] = djs_node(i, 0, 1);
        if (!garden.count(pos_x)) {
            garden[pos_x] = i;
        } else {
            crowd += unionSet(garden[pos_x], i, djs);
        }
    }

    for (int i=0; i<q; i++) {
        int op, arg1, arg2;
        cin >> op >> arg1 >> arg2;
        if (op == 1) {
            placeFood(arg1, arg2, djs, garden, crowd);
        } else {
            moveCat(arg1, arg2, djs, djs_idx, garden, crowd);
        }
        cout << crowd << "\n";
    }

    return 0;
}
#include <bits/stdc++.h>

#define lli long long int

using namespace std;

struct djs_node {
    int p, rk, sz;
    djs_node() = default;
    djs_node(int _p, int _rk, int _sz) : p(_p), rk(_rk), sz(_sz) {}
};

int findSet(int val, map<int, djs_node> &djs) {
    int p = djs[val].p;
    if (p == val) {
        return val;
    } else {
        int set_id = findSet(p, djs);
        djs[val].p = set_id;
        return set_id;
    }
}

void unionSet(int sa, int sb, map<int, djs_node> &djs) {
    // int sz_a=djs[sa].rk, sz_b=djs[sb].rk;
    auto na=djs.find(sa), nb=djs.find(sb);
    if (na->second.rk > nb->second.rk) {
        nb->second.p = na->first;
        na->second.sz += nb->second.sz;
        nb->second.sz = 0;
    } else if (na->second.rk < nb->second.rk) {
        na->second.p = nb->first;
        nb->second.sz += na->second.sz;
        na->second.sz = 0;
    } else {
        nb->second.p = na->first;
        na->second.rk += 1;
        na->second.sz += nb->second.sz;
        nb->second.sz = 0;
    }
}

void placeFood(int p, int r, map<int, djs_node> &djs) {
    if (!djs.count(p)) {
        djs[p] = djs_node(p, 0, 0);
    }
    auto left = djs.lower_bound(p-r);
    auto right = djs.upper_bound(p+r);
    for (auto it = left; it!=right; it++) {
        int mid_set = findSet(p, djs);
        int merged_set = findSet(it->first, djs);
        if (merged_set == it->first && merged_set != mid_set) {
            unionSet(mid_set, merged_set, djs);
        }
    }
    int tmp = findSet(p, djs);
    if (tmp != p) {
        djs[p].sz = djs[tmp].sz;
        djs[p].rk = djs[tmp].rk;
        djs[tmp].sz = 0;
        djs[tmp].p = p;
        djs[p].p = p;
    }
}

void moveCat(int t, int x, map<int, djs_node> &djs, vector<int> &cat_id) {
    int og_set = findSet(cat_id[t], djs);
    djs[og_set].sz -= 1;
    cat_id[t] = x;
    if (!djs.count(x)) {
        djs[x] = djs_node(x, 0, 1);
    } else {
        if (findSet(x, djs) == x) {
            if (djs[x].rk == 0) djs[x].rk+=1;
            djs[x].sz += 1;
        } else {
            djs[x] = djs_node(x, 0, 1);
        }
    }
}

lli calcCrowd(map<int, djs_node> &djs) {
    lli ans=0;
    for (auto it=djs.begin(); it!=djs.end(); it++) {
        if (it->second.sz > 0) {
            ans += (lli)(it->second.sz) * ((lli)(it->second.sz)-1) / 2;
        }
    }
    return ans;
}


void printMap(map<int, djs_node> m) {
    cout << "===== printing map =====\n";
    for (auto it=m.begin(); it!=m.end(); it++) {
        cout << "key: " << it->first << "\n";
        cout << "p: " << it->second.p << ", rk: " << it->second.rk << ", sz: " << it->second.sz << "\n";
    }
    cout << "======= finished =======\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    
    // map<int, int> djs_p, djs_rk;
    map<int, djs_node> djs;
    vector<int> cat_id(n+1);
    for (int i=1; i<=n; i++) {
        int pos_x;
        cin >> pos_x;
        cat_id[i] = pos_x;
        if (!djs.count(pos_x)) {
            djs[pos_x] = djs_node(pos_x, 0, 1);
        } else {
            djs[pos_x].rk = 1;
            djs[pos_x].sz += 1;
        }
    }

    // printMap(djs_p);
    // printMap(djs_rk);

    for (int i=0; i<q; i++) {
        int op, arg1, arg2;
        cin >> op >> arg1 >> arg2;

        if (op == 1) {
            placeFood(arg1, arg2, djs);
        } else {
            moveCat(arg1, arg2, djs, cat_id);
        }

        // for (int j=1; j<=n; j++) {
        //     cat_id[j] = findSet(cat_id[j], djs_p);
        // }
        // printMap(djs_p);
        // printMap(djs_rk);

        cout << calcCrowd(djs) << "\n";
    }

    return 0;
}
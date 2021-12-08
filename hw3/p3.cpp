// Refs & ppl discussed with
// b09902100

#include <bits/stdc++.h>

#define lli long long int

using namespace std;

struct edge {
    int v, idx;
    lli w;
    edge() = default;
    edge(int _v, int _idx, lli _w) : v(_v), idx(_idx), w(_w) {}
};

struct v_dijk {
    int key, p_idx;
    lli d;
    v_dijk() = default;
    v_dijk(int _key, int _p_idx, lli _d) : key(_key), p_idx(_p_idx), d(_d) {}
    const bool operator<(const v_dijk &v) const {
        if (d != v.d) return d>v.d;
        else return key>v.key;
    }
};

struct v_prim {
    int key;
    lli d;
    v_prim() = default;
    v_prim(int _key, lli _d) : key(_key), d(_d) {}
    const bool operator<(const v_prim &v) const {
        if (d != v.d) return d>v.d;
        else return key>v.key;
    }
};

lli dijkstra(int n, vector<vector<edge>> &adj, vector<lli> &edge_w, vector<int> &sel_idx) {
    vector<v_dijk> vertices(n+1);
    vector<int> tree(n+1, 0);
    priority_queue<v_dijk> q;
    lli total_w=0;

    for (int i=1; i<=n; i++) // Init vertices
        vertices[i] = v_dijk(i, 0, INT64_MAX);
    vertices[1].d = 0;

    for (int i=1; i<=n; i++) // Build heap
        q.push(vertices[i]);
    
    while (!q.empty()) {
        while (!q.empty() && tree[q.top().key]) q.pop();
        if (q.empty()) break;
        
        int u = q.top().key; q.pop();
        tree[u] = 1;
        for (auto it=adj[u].begin(); it!=adj[u].end(); it++) {
            int v=it->v, w=it->w, p_idx=it->idx;
            // Relax
            if (vertices[v].d >= vertices[u].d + w){
                vertices[v].d = vertices[u].d + w;
                vertices[v].p_idx = p_idx;
                q.push(vertices[v]);
            }
        }
        if (u != 1) {
            sel_idx.push_back(vertices[u].p_idx);
            total_w += edge_w[vertices[u].p_idx];
        }
    }
    return total_w;
}

lli prim(int n, vector<vector<edge>> &adj) {
    vector<v_prim> vertices(n+1);
    vector<int> tree(n+1, 0);
    priority_queue<v_prim> q;
    lli total_w=0;

    for (int i=1; i<=n; i++)
        vertices[i] = v_prim(i, INT64_MAX);
    vertices[1].d = 0;
    
    for (int i=1; i<=n; i++)
        q.push(vertices[i]);

    while (!q.empty()) {
        while (!q.empty() && tree[q.top().key]) q.pop();
        if (q.empty()) break;
        
        int u = q.top().key; q.pop();
        tree[u] = 1;
        for (auto it=adj[u].begin(); it!=adj[u].end(); it++) {
            int v=it->v, w=it->w;
            // Update
            if (!tree[v] && vertices[v].d > w) {
                vertices[v].d = w;
                q.push(vertices[v]);
            }
        }
        total_w += vertices[u].d;
    }
    return total_w;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<edge>> adj(n+1);
    vector<lli> edge_w(m+1, 0);
    for (int i=1; i<=m; i++) {
        int v1, v2, w;
        cin >> v1 >> v2 >> w;
        adj[v1].push_back(edge(v2, i, w));
        adj[v2].push_back(edge(v1, i, w));
        edge_w[i] = w;
    }

    lli dijk_w=0, prim_w=0;
    vector<int> sel_idx;
    
    dijk_w = dijkstra(n, adj, edge_w, sel_idx);
    prim_w = prim(n, adj);
    
    // cout << dijk_w << " " << prim_w << "\n";

    if (prim_w == dijk_w) {
        cout << "Yes\n";
        sort(sel_idx.begin(), sel_idx.end());
        for (auto it=sel_idx.begin(); it!=sel_idx.end(); it++) cout << *it << " ";
        cout << "\n";
    } else {
        cout << "No\n";
    }

    return 0;
}
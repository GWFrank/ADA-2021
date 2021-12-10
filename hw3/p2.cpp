// Refs & ppl discussed with
// b09902100

#include <bits/stdc++.h>

struct vertex {
    int color, scc_id;
    int f;
};

void DFSvisit(vector<vector<int>> &adj, vector<vertex> &vertices, int st) {
    vertices[st].color = 1;
    for (auto it=adj[st].begin(); it!=adj[st].end(); it++) {
        if (!vertices[*it].color) {
            vertices[*it].pi = st;
            DFSvisit(adj, vertices, *it);
        }
    }
}

void DFS(vector<vector<int>> &adj, vector<vertex> &vertices, int st) {
    for (auto v_it=vertices.begin(); v_it!=vertices.end(); v_it++) {
        v_it->color = 0;
        v_it->pi = -1;
    }
    DFSvisit(adj, vertices, st);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, flag;
    cin >> T >> flag;
    for (int t=0; t<T; t++) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj(n+1), adj_rev(n+1);
        for (int i=0; i<m; i++) {
            int u, v;
            cin >> u >> v;
            
        }

        

    }

    return 0;
}
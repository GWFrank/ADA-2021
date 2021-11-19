#include <bits/stdc++.h>

using namespace std;

void printVec(vector<int> &vec) {
    for (auto it=vec.begin(); it!=vec.end(); it++) cout << *it << " ";
    cout << "\n";
}

void DFSvisit(vector<vector<int>> &adj, int &v, vector<int> &status, vector<int> &res) {
    status[v] = 1;
    res.push_back(v);
    for (auto it=adj[v].begin(); it!=adj[v].end(); it++) {
        if (!status[*it]) DFSvisit(adj, *it, status, res);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int v, e;
    cin >> v >> e;
    vector<vector<int>> adj(v+1);
    for (int i=0; i<e; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }
    for (int i=1; i<=v; i++) {
        sort(adj[i].begin(), adj[i].end());
        // printVec(adj[i]);
    }
    // BFS
    vector<int> bfs_status(v+1, 0), bfs_res, nxt;
    queue<int> q;
    bfs_status[1] = 1;
    q.push(1);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto it=adj[u].begin(); it!=adj[u].end(); it++) {
            if (!bfs_status[*it]) {
                bfs_status[*it] = 1;
                nxt.push_back(*it);
            }
        }
        if (q.empty()) {
            sort(nxt.begin(), nxt.end());
            for (auto it=nxt.begin(); it!=nxt.end(); it++) q.push(*it);
            nxt.clear();
        }
        bfs_res.push_back(u);
    }
    // DFS
    vector<int> dfs_status(v+1, 0), dfs_res;
    for (int i=1; i<=v; i++) {
        if (!dfs_status[i]) DFSvisit(adj, i, dfs_status, dfs_res);
    }

    // Output ans
    printVec(dfs_res);
    printVec(bfs_res);
    return 0;
}
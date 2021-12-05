// Refs & ppl discussed with
// b09902100

#include <bits/stdc++.h>

using namespace std;

struct vertex {
    int color;
    int dist;
    int pi; // For DFS
};

void printVec(vector<int> &vec) {
    for (auto it=vec.begin(); it!=vec.end(); it++) cout << *it << " ";
    cout << "\n";
}

void BFS(vector<vector<int>> &adj, vector<vertex> &vertices, int st) {
    for (auto v_it=vertices.begin(); v_it!=vertices.end(); v_it++) {
        v_it->color = 0;
        v_it->dist = -1;
    }
    vertices[st].color = 1;
    vertices[st].dist = 0;
    queue<int> q;
    q.push(st);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto it=adj[u].begin(); it!=adj[u].end(); it++) {
            if (!vertices[*it].color) {
                vertices[*it].color = 1;
                vertices[*it].dist = vertices[u].dist+1;
                q.push(*it);
            }
        }
    }
}

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

void DPvisit(vector<vector<int>> &adj, vector<vertex> &vertices, int st, vector<vector<int>> &dp, vector<int> &dia) {
    vertices[st].color = 1;
    dp[st][0] = 0;
    dp[st][1] = 0;
    dia[st] = 1;
    for (auto it=adj[st].begin(); it!=adj[st].end(); it++) {
        if (!vertices[*it].color) {
            DPvisit(adj, vertices, *it, dp, dia);
            if (dp[*it][0]+1 >= dp[st][0]) {
                dp[st][1] = dp[st][0];
                dp[st][0] = dp[*it][0]+1;
            } else if (dp[*it][0]+1 > dp[st][1]) {
                dp[st][1] = dp[*it][0]+1;
            }
            dia[st] = max(dia[st], dia[*it]);
        }
    }
    dia[st] = max(dia[st], dp[st][0]+dp[st][1]+1);
}

void DP(vector<vector<int>> &adj, vector<vertex> &vertices, int st, vector<vector<int>> &dp, vector<int> &dia) {
    for (auto v_it=vertices.begin(); v_it!=vertices.end(); v_it++) {
        v_it->color = 0;
    }
    DPvisit(adj, vertices, st, dp, dia);
}

int calcRad(int dia) {
    return ((dia+1)%2) ? ((dia+1)/2)+1 : (dia+1)/2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int v;
    cin >> v;
    vector<vertex> vertices(v);
    vector<vector<int>> adj(v);
    for (int i=0; i<v-1; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        adj[v1-1].push_back(v2-1);
        adj[v2-1].push_back(v1-1);
    }

    // cout << "======= adjacency list =======\n";
    // for (int i=0; i<v; i++) {
    //     printVec(adj[i]);
    // }
    // cout << "==============================\n";
    
    // Find diameter path
    int dia_st, dia_st_d=-1;
    BFS(adj, vertices, 0);
    for (int i=0; i<v; i++) {
        // cout << "v:" <<  i << " @dist " << vertices[i].dist << "\n";
        if (vertices[i].dist > dia_st_d) {
            dia_st = i;
            dia_st_d = vertices[i].dist;
        }
    }
    int dia_ed, dia_ed_d=-1;
    BFS(adj, vertices, dia_st);
    for (int i=0; i<v; i++) {
        if (vertices[i].dist > dia_ed_d) {
            dia_ed = i;
            dia_ed_d = vertices[i].dist;
        }
    }
    vector<int> dia_path;
    DFS(adj, vertices, dia_ed);
    int dia_v = dia_st;
    while (dia_v != -1) {
        dia_path.push_back(dia_v);
        dia_v = vertices[dia_v].pi;
    }

    // printVec(dia_path);
    // cout << dia_st << " @dist " << dia_st_d << "\n";

    // Tree DP
    vector<vector<int>> dp1(v), dp2(v);
    vector<int> dia_fw(v), dia_bw(v);
    for (int i=0; i<v; i++) {
        dp1[i].resize(2);
        dp2[i].resize(2);
    }
    DP(adj, vertices, dia_st, dp1, dia_fw);
    DP(adj, vertices, dia_ed, dp2, dia_bw);
    // cout << "dia_fw:\n";
    // printVec(dia_fw);
    // cout << "dia_bw:\n";
    // printVec(dia_bw);

    // Cut each edge on the diameter
    int new_dia = INT32_MAX;
    for (int i=0; i<dia_path.size()-1; i++) {
        int v1 = dia_path[i], v2 = dia_path[i+1];
        int res_dia = calcRad(dia_bw[v1]) + calcRad(dia_fw[v2]);
        res_dia = max(res_dia, dia_bw[v1]);
        res_dia = max(res_dia, dia_fw[v2]);
        // cout << "cut at " << v1 << "," << v2 <<"\n";
        // cout << "result diameter: " << res_dia <<"\n";
        new_dia = min(new_dia, res_dia);
    }

    cout << new_dia-1 << "\n";

    return 0;
}
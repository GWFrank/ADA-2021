// Refs & ppl discussed with
// b09902100

#include <bits/stdc++.h>

using namespace std;

struct vertex {
    int color, scc_id;
    vertex(int _color, int _scc_id) : color(_color), scc_id(_scc_id) {}
};

struct scc_vertex{
    int color, is_src, is_snk, real_v, paired;
    scc_vertex(int _color, int _is_src, int _is_snk, int _real_v, int _paired):
        color(_color), is_src(_is_src), is_snk(_is_snk), real_v(_real_v), paired(_paired) {}
};

void printVec(vector<int> &vec) {
    for (auto it=vec.begin(); it!=vec.end(); it++) cout << *it << " ";
    cout << "\n";
}

void DFSvisit(vector<vector<int>> &adj, vector<vertex> &vertices, int st, stack<int> &stk) {
    vertices[st].color = 1;
    for (auto it=adj[st].begin(); it!=adj[st].end(); it++) {
        if (!vertices[*it].color)
            DFSvisit(adj, vertices, *it, stk);
    }
    stk.push(st); // Finished vertex
}

void DFS(vector<vector<int>> &adj, vector<vertex> &vertices, stack<int> &stk) {
    for (auto v_it=vertices.begin(); v_it!=vertices.end(); v_it++) {
        v_it->color = 0;
    }
    for (int i=1; i<vertices.size(); i++) {
        if (!vertices[i].color)
            DFSvisit(adj, vertices, i, stk);
    }
}

void DFS_SCC_visit(vector<vector<int>> &adj_rev, vector<vertex> &vertices, int st, int &scc_id) {
    vertices[st].color = 1;
    vertices[st].scc_id = scc_id;
    for (auto it=adj_rev[st].begin(); it!=adj_rev[st].end(); it++) {
        if (!vertices[*it].color) {
            DFS_SCC_visit(adj_rev, vertices, *it, scc_id);
        }
    }
}

void DFS_SCC(vector<vector<int>> &adj_rev, vector<vertex> &vertices, stack<int> stk, int &scc_n) {
    for (auto v_it=vertices.begin(); v_it!=vertices.end(); v_it++) {
        v_it->color = 0;
    }
    while (!stk.empty()) {
        int i=stk.top();
        stk.pop();
        if (!vertices[i].color) {
            DFS_SCC_visit(adj_rev, vertices, i, scc_n);
            scc_n++;
        }
    }
}

int pairing_visit(vector<vector<int>> &scc_adj, vector<scc_vertex> &scc_v, int st) {
    scc_v[st].color = 1;
    if (scc_v[st].is_snk) {
        scc_v[st].paired = 1;
        return st;
    }
    for (auto it=scc_adj[st].begin(); it!=scc_adj[st].end(); it++) {
        if (!scc_v[*it].color) {
            int paired_snk = pairing_visit(scc_adj, scc_v, *it);
            if (paired_snk >= 0)
                return paired_snk;
        }
    }
    return -1;
}

void pairing(vector<vector<int>> &scc_adj, vector<scc_vertex> &scc_v, vector<int> &src, vector<pair<int, int>> &src_snk_pairs) {
    for (auto it=scc_v.begin(); it!=scc_v.end(); it++) {
        it->color = 0;
        it->paired = 0;
    }
    for (auto it=src.begin(); it!=src.end(); it++) {
        int paired_snk = pairing_visit(scc_adj, scc_v, *it);
        if (paired_snk >= 0) {
            src_snk_pairs.push_back(make_pair(*it, paired_snk));
            scc_v[*it].paired = 1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, flag;
    cin >> T >> flag;
    for (int t=0; t<T; t++) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj(n+1, vector<int>(0)), adj_rev(n+1, vector<int>(0));
        for (int i=0; i<m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj_rev[v].push_back(u);
        }
        vector<vertex> vertices(n+1, vertex(0, -1));
        stack<int> scc_stk;
        int scc_n=0;
        DFS(adj, vertices, scc_stk);
        DFS_SCC(adj_rev, vertices, scc_stk, scc_n);

        // Build DAG of SCCs
        vector<scc_vertex> scc_v(scc_n, scc_vertex(0, 1, 1, 0, 0));
        vector<vector<int>> scc_adj(scc_n, vector<int>(0));
        for (int i=1; i<=n; i++) {
            int scc_id = vertices[i].scc_id;
            scc_v[scc_id].real_v=i;
            // cout << "vertex: " << i << " scc_id: " << scc_id << "\n";
            for (auto it=adj[i].begin(); it!=adj[i].end(); it++) {
                if (scc_id != vertices[*it].scc_id) {
                    scc_adj[scc_id].push_back(vertices[*it].scc_id);
                    scc_v[scc_id].is_snk = 0; // out-degree != 0
                    scc_v[vertices[*it].scc_id].is_src = 0; // in-degree != 0
                }
            }
        }

        // Group isolated, sources, sinks
        vector<int> src, snk, iso;
        src.clear(); snk.clear(); iso.clear();
        for (int i=0; i<scc_n; i++) {
            if (scc_v[i].is_snk && scc_v[i].is_src)
                iso.push_back(i);
            else if (scc_v[i].is_snk)
                snk.push_back(i);
            else if (scc_v[i].is_src)
                src.push_back(i);
        }

        // cout << "sources: "; printVec(src); cout << "\n";
        // cout << "sink: "; printVec(snk); cout << "\n";
        // cout << "isolated: "; printVec(iso); cout << "\n";
        

        // Pair source to sink
        vector<pair<int, int>> ss_pairs;
        ss_pairs.clear();
        pairing(scc_adj, scc_v, src, ss_pairs);
        for (auto it=iso.begin(); it!=iso.end(); it++)
            ss_pairs.push_back(make_pair(*it, *it));

        vector<pair<int, int>> new_edges;
        new_edges.clear();
        for (int i=0; i<ss_pairs.size(); i++) {
            new_edges.push_back( make_pair(ss_pairs[i].second, ss_pairs[(i+1)%ss_pairs.size()].first) );
        }

        ss_pairs.clear();

        vector<int> src_left, snk_left;
        src_left.clear(); snk_left.clear();
        for (auto it=src.begin(); it!=src.end(); it++)
            if (!scc_v[*it].paired)
                src_left.push_back(*it);
        for (auto it=snk.begin(); it!=snk.end(); it++)
            if (!scc_v[*it].paired)
                snk_left.push_back(*it);
        for (int i=0; i<min(src_left.size(), snk_left.size()); i++)
            new_edges.push_back( make_pair(snk_left[i], src_left[i]) );
            // ss_pairs.push_back(make_pair(src_left[i], snk_left[i]));
        
        
        // for (auto it=ss_pairs.begin(); it!=ss_pairs.end(); it++) {
        //     cout << "(" << it->first << "," << it->second << ") ";
        // }
        // cout << "\n";

        

        if (src_left.size() >= snk_left.size()) { // extra sources
            for (int i=snk_left.size(); i<src_left.size(); i++) {
                new_edges.push_back( make_pair(new_edges[0].first, src_left[i]) );
            }
        } else {
            for (int i=src_left.size(); i<snk_left.size(); i++) { // extra sinks
                new_edges.push_back( make_pair(snk_left[i], new_edges[0].second) );
            }
        }

        // for (auto it=new_edges.begin(); it!=new_edges.end(); it++) {
        //     cout << "(" << it->first << "," << it->second << ") ";
        // }
        // cout << "\n";

        if (scc_n > 1) {
            cout << new_edges.size() << "\n";
            if (flag) {
                for (auto it=new_edges.begin(); it!=new_edges.end(); it++) {
                    cout << scc_v[it->first].real_v << " " << scc_v[it->second].real_v << "\n";
                }
            }
        } else {
            cout << "0\n";
        }
    }

    return 0;
}
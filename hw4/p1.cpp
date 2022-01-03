// Refs & ppl discussed with
// b09902100
// https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
// https://web.ntnu.edu.tw/~algo/CompleteGraph.html#2

#include <bits/stdc++.h>
using namespace std;
// #include "ypglpk.hpp"

// Hack mixed_integer_linear_programming() to work with binary variables
#ifndef __YP_CLIQUE_GLPK_HEADER
#define __YP_CLIQUE_GLPK_HEADER
#include<glpk.h>
#include<vector>
#include<utility>
// https://www.gnu.org/software/glpk/
// http://most.ccib.rutgers.edu/glpk.pdf
namespace ypglpk
{
    using std::vector, std::pair;
    bool output = 0;
    constexpr double INF = 1e300;
    // set whether to output verbose information about the solver (for debugging)
    void set_output(bool _output)
    {
        output = _output;
    }
    // for interal usage. please do not call it unless you are really sure about what you are doing
    void set_constraints(glp_prob *P, const vector<vector<double>> &A, const vector<double> &b, const vector<double> &c)
    {
        int n = c.size(), m = b.size();
        glp_set_obj_dir(P, GLP_MAX);
        glp_add_rows(P, m);
        glp_add_cols(P, n);
        for (int i = 0; i < m; i++)
            glp_set_row_bnds(P, i + 1, GLP_UP, 0, b[i]);
        for (int i = 0; i < n; i++)
            glp_set_col_bnds(P, i + 1, GLP_FR, 0, 0);
        for (int i = 0; i < n; i++)
            glp_set_obj_coef(P, i + 1, c[i]);
        vector<int> ia(1), ja(1);
        vector<double> ar(1);
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (A[i][j] == 0)
                    continue;
                ia.push_back(i + 1);
                ja.push_back(j + 1);
                ar.push_back(A[i][j]);
            }
        }
        glp_load_matrix(P, (int)ia.size() - 1, ia.data(), ja.data(), ar.data());
    }
    // maximize cx subject to Ax<=b and xi is an integer if isint[i]. return pair(cy,y) where y is the optimal x. if the constraints are infeasible or unbounded, return pair(-INF,{}).
    pair<double, vector<double>> bin_lp(
          const vector<vector<double>> &A, const vector<double> &b, const vector<double> &c
        ) {
        int n = c.size();
        glp_term_out(output ? GLP_ON : GLP_OFF);
        glp_prob *milp = glp_create_prob();
        set_constraints(milp, A, b, c);
        for (int i = 0; i < n; i++) {
            // if (isint[i])
            glp_set_col_kind(milp, i + 1, GLP_BV);
        }
        glp_iocp parm;
        glp_init_iocp(&parm);
        parm.presolve = GLP_ON;
        if (glp_intopt(milp, &parm)) {
            glp_delete_prob(milp);
            return {-INF, {}};
        }
        vector<double> ans(n);
        for (int i = 0; i < n; i++)
            ans[i] = glp_mip_col_val(milp, i + 1);
        double opt = glp_mip_obj_val(milp);
        glp_delete_prob(milp);
        return {opt, ans};
    }
}
#endif

struct vertex {
    int idx, deg;
    vertex() = default;
    vertex(int _idx, int _deg) : idx(_idx), deg(_deg) {}
};

bool myCmp(vertex v1, vertex v2) { return v1.deg > v2.deg; }

void BKSearch(bitset<80> R, bitset<80> P, bitset<80> X, vector<bitset<80>> &adj_mat, vector<bitset<80>> &cliques) {
    if (P.none() && X.none()) {
        cliques.push_back(R);
        return;
    }
    bitset<80> tmp = P|X;
    int pivot;
    for (pivot=0; pivot<adj_mat.size(); ++pivot)
        if (tmp[pivot]) break;
    // vector<int> pivots(0);
    // for (int i=0; i<adj_mat.size(); ++i)
    //     if (tmp[i]) pivots.push_back(i);
    // pivot = pivots[rand()%pivots.size()];
    tmp = P^(P&adj_mat[pivot]);
    for (int v=0; v<adj_mat.size(); ++v) {
        if (tmp[v]) {
            bitset<80> only_v; only_v.reset(); only_v[v]=1;
            BKSearch(R|only_v, P&adj_mat[v], X&adj_mat[v], adj_mat, cliques);
            P[v] = 0;
            X[v] = 1;
        }
    }
}

void BronKerbosch(vector<vertex> &vertices, vector<bitset<80>> &adj_mat, vector<bitset<80>> &cliques) {
    sort(vertices.begin(), vertices.end(), myCmp);
    bitset<80> R, P, X;
    P.set(); R.reset(); X.reset();
    for (auto it=vertices.begin(); it!=vertices.end(); ++it) {
        int v=it->idx;
        bitset<80> only_v; only_v.reset(); only_v[v]=1;
        BKSearch(R|only_v, P&adj_mat[v], X&adj_mat[v], adj_mat, cliques);
        P[v] = 0;
        X[v] = 1;
    }
}

void printCliques(vector<bitset<80>> &cliques) {
    cerr << "Total: " << cliques.size() << " cliques\n";
    for (auto it=cliques.begin(); it!=cliques.end(); ++it)
        cerr << *it << "\n";
}

void printVec(vector<double> &vec) {
    cerr << "< ";
    for (auto it=vec.begin(); it!=vec.end(); ++it) { cerr.width(2); cerr << *it << " "; }
    cerr << ">\n";
}

void printMat(vector<vector<double>> &mat) {
    for(auto it=mat.begin(); it!=mat.end(); ++it)
        printVec(*it);
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int t=0; t<T; ++t) {
        int V, E;
        cin >> V >> E;

        vector<bitset<80>> adj_mat(V);
        vector<vertex> vertices(V);
        for (int i=0; i<V; ++i)
            adj_mat[i].reset();
        for (int i=0; i<E; ++i) {
            int v1, v2;
            cin >> v1 >> v2;
            adj_mat[v1][v2] = 1;
            adj_mat[v2][v1] = 1;
        }
        for (int i=0; i<V; ++i)
            vertices[i] = vertex(i, adj_mat[i].count());
        
        // List all maximal cliques
        vector<bitset<80>> cliques;
        cliques.clear();
        BronKerbosch(vertices, adj_mat, cliques);
        // printCliques(cliques);

        // Prepare LP
        // int cnst = V+cliques.size()*2, strt = cliques.size();
        int cnst = V, strt = cliques.size();
        vector<vector<double>> A(cnst, vector<double>(strt, 0));
        vector<double> b(cnst), c(strt);
        // vector<bool> isint(strt);

        for (int i=0; i<V; ++i) {
            // -v_i = -(x_k1 + ... + x_kn) <= -1
            for (int j=0; j<strt; ++j)
                A[i][j] = -cliques[j][i];
            b[i] = -1;
        }
        // for (int i=0; i<strt; i++) {
        //     // x_i <= 1
        //     // fill(A[V+i].begin(), A[V+i].end(), 0);
        //     A[V+i][i] = 1;
        //     b[V+i] = 1;
        //     // -x_i <= 0
        //     // fill(A[V+strt+i].begin(), A[V+strt+i].end(), 0);
        //     A[V+strt+i][i] = -1;
        //     b[V+strt+i] = 0;
        //     // c[i] = -1;
        //     // isint[i] = true;
        // }
        // target: minimize sum(x)
        fill(c.begin(), c.end(), -1);
        // fill(isint.begin(), isint.end(), true);
        // cerr << "A = \n"; printMat(A);
        // cerr << "b = "; printVec(b);
        // cerr << "c = "; printVec(c);

        // Solve LP & output
        pair<double, vector<double>> sol = ypglpk::bin_lp(A, b, c);
        bitset<80> chosen; chosen.reset();
        cout << -sol.first << "\n";
        for (int i=0; i<strt; i++) {
            if (sol.second[i] == 1) {
                bitset<80> clicked = cliques[i]^(cliques[i]&chosen);
                cout << clicked.count() << " ";
                for (int j=0; j<80; j++)
                    if (clicked[j]) cout << j << " ";
                cout << "\n";
                chosen |= cliques[i];
            }
        }

    }
    return 0;
}
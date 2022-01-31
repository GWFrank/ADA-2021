#include "ada-hw4-p3.h"
#include <iostream>
using namespace std;
// feel free to use global variables
vector<int> contest, conceal, paired;
vector<bool> is_hidden;

void printVec(vector<int> v) {
    for (auto it=v.begin(); it!=v.end(); ++it)
        cout << *it << " ";
    cout << "\n";
}

vector<int> init(int N) {
    contest.resize(N);
    is_hidden.resize(N);
    paired.resize(N);
    conceal.resize(0);
    for (int i=0; i<N; ++i) {
        contest[i] = i;
        is_hidden[i] = false;
        paired[i] = -1;
    }
    int i=0;
    while (i<(N-1)) {
        if (compare(contest[i], contest[i+1])) { // i < i+1
            i++;
        } else { // i > i+1
            conceal.push_back(contest[i]);
            conceal.push_back(contest[i+1]);
            is_hidden[contest[i]] = true;
            is_hidden[contest[i+1]] = true;
            paired[contest[i]] = contest[i+1];
            paired[contest[i+1]] = contest[i];
            int l=i-1, r=i+2;
            // cout << l << " " << r << endl;
            // cout << contest[l] << " " << contest[r] 
            while (l>=0 && r<N) {
                while (l>=0 && is_hidden[contest[l]])
                    --l;
                if (l<0 || compare(contest[l], contest[r]))
                    break;

                conceal.push_back(contest[l]);
                conceal.push_back(contest[r]);
                is_hidden[contest[l]] = true;
                is_hidden[contest[r]] = true;
                paired[contest[l]] = contest[r];
                paired[contest[r]] = contest[l];
                --l;
                ++r;
                // ++i;
            }
            // i+=2;
            i=r;
        }
    }
    // printVec(contest);
    // printVec(conceal);
    // printVec(paired);
    return conceal;
}

vector<int> insert(int p, int id) {
    contest.insert(contest.begin() + p, id);
    is_hidden.push_back(false);
    paired.push_back(-1);

    int l=p-1, r=p+1, N=contest.size();
    while (l>=0 && is_hidden[contest[l]])
        --l;
    while (r<N && is_hidden[contest[r]])
        ++r;
    
    if (l>=0 && !compare(contest[l], contest[p])) {
        // left neightbor > inserted
        conceal.push_back(contest[l]);
        conceal.push_back(contest[p]);
        is_hidden[contest[l]] = true;
        is_hidden[contest[p]] = true;
        paired[contest[l]] = contest[p];
        paired[contest[p]] = contest[l];
        // printVec(contest);
        // printVec(conceal);
        // printVec(paired);
        return conceal;
    }
    if (r<N && !compare(contest[p], contest[r])) {
        // inserted > right neighbor
        conceal.push_back(contest[p]);
        conceal.push_back(contest[r]);
        is_hidden[contest[p]] = true;
        is_hidden[contest[r]] = true;
        paired[contest[p]] = contest[r];
        paired[contest[r]] = contest[p];
        // printVec(contest);
        // printVec(conceal);
        // printVec(paired);
        return conceal;
    }
    // printVec(contest);
    // printVec(conceal);
    // printVec(paired);
    return conceal;
}

vector<int> remove(int p) {
    int removed = contest[p];
    int m=paired[removed], m_p=0;
    contest.erase(contest.begin() + p);
    paired[removed] = -1;
    is_hidden[removed] = false;
    if (m == -1)
        return conceal;
    paired[m] = -1;
    is_hidden[m] = false;
    for (auto it=conceal.begin(); it!=conceal.end(); ++it) {
        if (*it == removed) {
            conceal.erase(it);
            break;
        }
    }
    for (auto it=conceal.begin(); it!=conceal.end(); ++it) {
        if (*it == m) {
            conceal.erase(it);
            break;
        }
    }
    while (contest[m_p] != m)
        ++m_p;
    
    int l=m_p-1, r=m_p+1, N=contest.size();
    while (l>=0 && is_hidden[contest[l]])
        --l;
    while (r<N && is_hidden[contest[r]])
        ++r;
    

    // cout << l << " " << m_p << " " << r << endl;
    
    if (l>=0 && !compare(contest[l], contest[m_p])) {
        // left neightbor > inserted
        conceal.push_back(contest[l]);
        conceal.push_back(contest[m_p]);
        is_hidden[contest[l]] = true;
        is_hidden[contest[m_p]] = true;
        paired[contest[l]] = contest[m_p];
        paired[contest[m_p]] = contest[l];
        return conceal;
    }
    if (r<N && !compare(contest[m_p], contest[r])) {
        // inserted > right neighbor
        conceal.push_back(contest[m_p]);
        conceal.push_back(contest[r]);
        is_hidden[contest[m_p]] = true;
        is_hidden[contest[r]] = true;
        paired[contest[m_p]] = contest[r];
        paired[contest[r]] = contest[m_p];
        return conceal;
    }
    
    return conceal;
}

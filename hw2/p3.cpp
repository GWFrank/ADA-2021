// Refs & ppl discussed with
// b09902100

#include <bits/stdc++.h>
using namespace std;

#define lli long long int

struct task {
    int st, ed, len, p, len_copy;
    task() = default;
    task(int _st, int _ed, int _len, int _p) : st(_st), ed(_ed), len(_len), p(_p), len_copy(_len) {}
    const bool operator<(const task &t) const {
        return ed > t.ed;
    }
};

bool stCmp(const task &a, const task &b) {
    return a.st < b.st;
}

bool pCmp(const task &a, const task &b) {
    return a.p > b.p;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, maxd=0;
    cin >> n;
    vector<task> all_tasks(n);
    for (int i = 0; i < n; i++) {
        int st, ed, len, p;
        cin >> st >> ed >> len >> p;
        all_tasks[i] = task(st, ed, len, p);
        maxd = max(maxd, ed);
    }
    sort(all_tasks.begin(), all_tasks.end(), pCmp);

    lli all_reward=0;
    int prev_workload=0;

    vector<task> tasks;
    for (int idx=0; idx<n; idx++) {
        tasks.push_back(all_tasks[idx]);
        lli reward = (lli) all_tasks[idx].p;
        while (idx<n-1 && all_tasks[idx+1].p == all_tasks[idx].p) {
            idx++;
            tasks.push_back(all_tasks[idx]);
        }

        sort(tasks.begin(), tasks.end(), stCmp);
        // for (int j=0; j<=idx; j++) {
        //     tasks[j].len = tasks[j].len_copy;
        //     // cout << tasks[j].st << ", " << tasks[j].ed << ", " << tasks[j].len << ", " << tasks[j].p << "\n";
        // }

        int timer=1, workload=0;
        priority_queue<task> q;
        for (int i=0; i<(idx+1); i++) {
            timer = tasks[i].st;
            q.push(tasks[i]);
            while (i<n-1 && tasks[i+1].st == tasks[i].st) {
                i++;
                q.push(tasks[i]);
            }

            int nxt = (i<(idx+1)-1) ? tasks[i+1].st : INT32_MAX;
            while (!q.empty() && timer < nxt) {
                task tp = q.top();
                q.pop();
                int workable = min({nxt-timer, tp.len, tp.ed-timer+1});
                if (workable > 0) {
                    workload += workable;
                    timer += workable;
                    tp.len -= workable;
                    if (tp.len > 0) q.push(tp);
                }
            }
        }
        all_reward += (workload-prev_workload)*reward;
        prev_workload = workload;
    }

    cout << all_reward << endl;
    return 0;
}
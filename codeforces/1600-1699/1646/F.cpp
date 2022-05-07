#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<map<int, int>> V(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val;
            cin >> val;
            val--;
            V[i][val]++;
        }
    }
    vector<vector<int>> res;
    while (true) {
        int idx = -1;
        int the_val;
        for (int i = 0; i < n && idx == -1; i++) {
            if (V[i].size() != n) {
                for (auto it : V[i]) {
                    if (it.second > 1) {
                        idx = i, the_val = it.first;
                        break;
                    }
                }
            }
        }
        if (idx == -1) break;
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            int the_idx = (idx + i) % n;
            ans[the_idx] = the_val;
            V[the_idx][the_val]--;
            if (V[the_idx][the_val] == 0) {
                V[the_idx].erase(the_val);
            }
            int nxt = (the_idx + 1) % n;
            int nxt_val = -1;
            if (i != n - 1) {
                if (V[nxt].size() == n) {
                    // 每个都只有一个  the_val 不变
                    nxt_val = the_val;
                } else {
                    for (auto it : V[nxt]) {
                        if (it.second > 1) {
                            nxt_val = it.first;
                            break;
                        }
                    }
                }
            }
            V[nxt][the_val]++;
            the_val = nxt_val;
        }
        res.push_back(ans);
    }

    for (int i = 1; i < n; i++) {
        int val = n - i;
        for (int t = 1; t <= i; t++) {
            vector<int> ans(n);
            for (int j = 0; j < n; j++) {
                ans[j] = (j + val) % n;
            }
            res.push_back(ans);
        }
    }
    cout << res.size() << endl;
    for (auto v : res) {
        for (auto v2 : v) {
            cout << v2 + 1 << ' ';
        }
        cout << endl;
    }
}
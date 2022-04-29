#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    map<int, vector<int>> M;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        M[a[i]].push_back(i);
    }

    int cnt = 0;
    vector<int> ans(n + 1);
    while (M.size()) {
        debug(M);
        if (M.size() == 1) {
            for (auto it : M) {
                auto v = it.second;
                for (auto idx : v) {
                    ans[idx] = a[idx];
                }
            }
            break;
        }

        vector<int> v;
        for (auto &it : M) {
            int tmp = it.second.back();
            v.push_back(tmp);
            M[it.first].pop_back();
        }
        int sz = v.size();

        for (int i = 0; i < sz; i++) {
            ans[v[i]] = a[v[(i + 1) % sz]];
        }

        map<int, vector<int>>::iterator itor = M.begin();
        for (; itor != M.end();) {
            if (itor->second.size() == 0) {
                itor = M.erase(itor);
            } else {
                itor++;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}
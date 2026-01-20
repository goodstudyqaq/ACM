#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    int n, k;
    cin >> n >> k;
    vector<vector<int>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        V[a].push_back(b);
        V[b].push_back(a);
    }

    long long res = 0;
    function<map<int, int>(int, int, int)> dfs = [&](int u, int pre, int d) -> map<int, int> {
        map<int, int> ans;
        ans[d]++;

        for (auto v : V[u]) {
            if (v == pre) continue;
            auto tmp = dfs(v, u, d + 1);

            if (ans.size() < tmp.size()) {
                swap(ans, tmp);
            }

            for (auto it : tmp) {
                int dis1 = it.first - d;
                int dis2 = k - dis1;
                int need = dis2 + d;

                if (ans.count(need)) {
                    res += 1LL * ans[need] * it.second;
                }
            }

            for (auto it : tmp) {
                ans[it.first] += it.second;
            }
        }
        return ans;
    };
    dfs(0, -1, 0);
    cout << res << '\n';
}
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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;
    vector<vector<int>> V(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }

    function<map<int, int>(int, int, int)> dfs = [&](int u, int pre, int d) -> map<int, int> {
        map<int, int> ans;
        ans[d] = 1;

        vector<int> G;
        for (auto v : V[u]) {
            if (v == pre) continue;
            G.push_back(v);
        }

        if (G.size() == 0) {
            return ans;
        } else if (G.size() == 1) {
            ans[d + 1] = 1;
            return ans;
        } else {
            auto sub_ans1 = dfs(G[0], u, d + 1);
            auto sub_ans2 = dfs(G[1], u, d + 1);

            if (sub_ans1.rbegin()->first < sub_ans2.rbegin()->first) {
                swap(sub_ans1, sub_ans2);
            }
            // sub_ans1 >= sub_ans2

            auto mx = sub_ans2.rbegin()->first + 1;

            while (true) {
                if (sub_ans1.size() == 0) break;
                auto tmp = sub_ans1.rbegin()->first;
                if (tmp > mx) {
                    sub_ans1.erase(prev(sub_ans1.end()));
                } else {
                    break;
                }
            }

            // merge
            if (sub_ans1.size() < sub_ans2.size()) {
                swap(sub_ans1, sub_ans2);
            }

            for (auto it : sub_ans2) {
                sub_ans1[it.first] += it.second;
            }
            sub_ans1[d] = 1;
            return sub_ans1;
        }
    };

    auto mp = dfs(1, -1, 0);

    int ans = 0;
    for (auto it : mp) {
        ans += it.second;
    }
    cout << n - ans << endl;
    return 0;
}
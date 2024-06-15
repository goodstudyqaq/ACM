#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

// #define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif

    int n;
    // cin >> n;

    vector<string> ans{"OX", "XOX", "XXXXXOX"};
    n = ans.size();
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }

    auto cal = [&](int a, int b) {
        string res = ans[a] + ans[b];

        set<string> ans;
        for (int i = 0; i < res.size(); i++) {
            for (int j = i; j < res.size(); j++) {
                ans.insert(res.substr(i, j - i + 1));
            }
        }
        return ans.size();
    };
    map<int, pair<int, int>> res;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val = cal(i, j);
            debug(i, j, val);
            res[cal(i, j)] = {i, j};
        }
    }
    int need = n + n * (n - 1);
    debug(res.size(), need);

    int q;
    // cin >> q;
    // while (q--) {
    //     int p;
    //     cin >> p;
    //     cout << res[p].first + 1 << ' ' << res[p].second + 1 << endl;
    // }
    return 0;
}
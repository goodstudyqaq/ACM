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
    int n;
    cin >> n;
    vector<int> in(n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        in[a[i]]++;
    }

    vector<int> color(n, -1);
    function<bool(int)> dfs = [&](int u) -> bool {
        int go = a[u];
        in[go]--;
        if (color[go] == -1) {
            if (color[u] == 0) {
                color[go] = 1;
                return dfs(go);
            } else {
                // color[u] = 1
                if (in[go] == 0) {
                    color[go] = 0;
                    return dfs(go);
                }
                return true;
            }
        } else {
            // color[go] != -1
            if (color[u] == 0 && color[go] == 0) {
                return false;
            }
            return true;
        }
    };

    for (int i = 0; i < n; i++) {
        if (in[i] == 0 && color[i] == -1) {
            color[i] = 0;
            bool res = dfs(i);
            if (!res) {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            color[i] = 0;
            bool res = dfs(i);
            if (!res) {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            debug(i);
            ans.push_back(a[i]);
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] + 1 << ' ';
    }
    cout << endl;

}
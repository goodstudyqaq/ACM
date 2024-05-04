#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

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
    vector<vector<int>> V(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    // const int mod = 1e9 + 7;
    map<vector<int>, int> M;
    vector<bool> ok;

    function<int(int, int)> dfs = [&](int u, int pre) -> int {
        vector<int> have;
        for (auto v : V[u]) {
            if (v == pre) continue;
            int s = dfs(v, u);
            have.push_back(s);
        }
        sort(have.begin(), have.end());

        if (M.count(have) == 0) {
            M[have] = ok.size();
        }

        int now = 0;
        int sz = have.size();

        while (now + 1 < sz) {
            if (have[now] != have[now + 1]) break;
            now += 2;
        }

        bool flag = false;
        if (now == sz) {
            flag = true;
        } else {
            if (ok[have[now]]) {
                now++;
                while (now + 1 < sz) {
                    if (have[now] != have[now + 1]) break;
                    now += 2;
                }
                if (now == sz) flag = true;
            }
        }
        ok.push_back(flag);
        return M[have];
    };
    int s = dfs(1, 0);
    if (ok[s]) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
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
    return 0;
}
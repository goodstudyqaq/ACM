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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<int> to(n + 1);
    for (int i = 1; i <= n; i++) {
        if (a[i] != b[i]) {
            to[a[i]] = b[i];
        }
    }
    int num = 0;
    vector<bool> vis(n + 1);

    function<void(int)> dfs = [&](int u) {
        vis[u] = 1;
        num++;
        int v = to[u];
        if (vis[v]) return;
        dfs(v);
    };

    int L = 1, R = n;
    ll ans = 0;

    auto get_val = [&](int num) {
        int begin_L = L++;
        int now = 1;
        ll res = 0;
        int last = begin_L;
        while (now < num) {
            int val;
            if (now % 2) {
                val = R--;
            } else {
                val = L++;
            }
            res += abs(val - last);
            last = val;
            now++;
        }
        res += abs(last - begin_L);
        return res;
    };

    vector<int> V2;

    for (int i = 1; i <= n; i++) {
        if (a[i] == b[i]) continue;
        if (vis[a[i]] == 0) {
            num = 0;
            dfs(a[i]);
            V2.push_back(num);
            // ans += get_val(num);
        }
    }

    for (auto num : V2) {
        if (num % 2 == 0) {
            ans += get_val(num);
        } else {
            ans += get_val(num - 1);
        }
    }

    // for (auto num : V2) {
    //     if (num % 2) {
    //         ans += get_val(num - 1);
    //     }
    // }

    cout << ans << endl;
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
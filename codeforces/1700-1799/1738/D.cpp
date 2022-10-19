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
    vector<int> b(n + 1);
    vector<vector<int>> V(n + 1);
    vector<int> vis(n + 1);
    vector<int> to(n + 1);
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        sum += b[i];
        if (b[i] == 0 || b[i] == n + 1) continue;
        V[b[i]].push_back(i);
        to[i]++;
        vis[b[i]] = 1;
        vis[i] = 1;
    }

    if (sum == 0) {
        cout << 0 << endl;
        for (int i = 1; i <= n; i++) {
            cout << i << ' ';
        }
        cout << endl;
        return;
    } else if (sum == 1LL * (n + 1) * n) {
        cout << n << endl;
        for (int i = 1; i <= n; i++) {
            cout << i << ' ';
        }
        cout << endl;
        return;
    }

    queue<pii> Q;
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 1 && to[i] == 0) {
            // 第一个
            Q.push({i, 0});
        }
    }
    vector<int> ans;

    vector<int> color(n + 1);

    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            ans.push_back(i);
            color[i] = 0;
        }
    }

    while (!Q.empty()) {
        auto [u, c] = Q.front();
        Q.pop();
        vector<int> tmp_u;
        tmp_u.push_back(u);

        while (!Q.empty() && Q.front().second == c) {
            tmp_u.push_back(Q.front().first);
            Q.pop();
        }

        // 只有 1 个的 size > 0

        int choose = -1;
        for (auto it : tmp_u) {
            if (V[it].size() > 0) {
                choose = it;
                break;
            }
        }
        for (auto it : tmp_u) {
            if (it != choose) {
                ans.push_back(it);
            }
        }
        if (choose != -1) {
            ans.push_back(choose);
        }
        for (auto it : tmp_u) {
            color[it] = c;
        }
        if (choose != -1) {
            for (auto v : V[choose]) {
                Q.push({v, c ^ 1});
            }
        }
    }
    int the_c = color[1];

    int k = 1;
    for (int i = 1; i <= n; i++) {
        if (color[i] == the_c) {
            k = i;
        }
    }
    cout << k << endl;

    for (auto it : ans) {
        cout << it << ' ';
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
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
    string s;
    cin >> s;
    vector<int> state(n + 1);
    for (int i = 0; i < n; i++) {
        state[i + 1] = s[i] - '0';
    }

    vector<int> a(n + 1);
    vector<vector<pii>> V(n + 1);
    vector<int> in(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        V[i].push_back({a[i], i});
        V[a[i]].push_back({i, i});
        in[i]++;
        in[a[i]]++;
    }

    queue<int> Q;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 1) {
            Q.push(i);
        }
    }
    vector<int> ans(n + 1, -1);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        if (state[u]) {
            // u 这条边需要变
            state[u] = 0;
            ans[u] = 1;
            state[a[u]] ^= 1;
            in[a[u]]--;
        } else {
            ans[u] = 0;
            in[a[u]]--;
        }
        if (in[a[u]] == 1) {
            Q.push(a[u]);
        }
    }

    auto check = [&](int u) -> bool {
        int now = u;
        ans[u] = 0;
        now = a[u];
        int use = 0;
        int cnt = 1;
        vector<int> V;
        V.push_back(u);
        while (now != u) {
            V.push_back(now);
            cnt++;
            if (state[now]) {
                use++;
                ans[now] = 1;
                state[now] = 0;
                state[a[now]] ^= 1;
            } else {
                ans[now] = 0;
            }
            now = a[now];
        }

        if (state[now]) return false;


        int use2 = cnt - use;
        if (use2 < use) {
            // 全部要反过来
            for (auto it : V) {
                ans[it] ^= 1;
            }
        }
        return true;
    };

    // 现在应该留下来的都是度数为 2 的，都是环
    for (int i = 1; i <= n; i++) {
        if (ans[i] == -1) {
            if (!check(i)) {
                cout << -1 << endl;
                return;
            }
        }
    }
    debug(state);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (ans[i]) cnt++;
    }
    cout << cnt << endl;
    for (int i = 1; i <= n; i++) {
        if (ans[i]) {
            cout << i << ' ';
        }
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
    return 0;
}
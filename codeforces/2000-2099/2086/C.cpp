#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    vector<int> vis(n + 1);
    int cnt = 0;
    function<void(int)> dfs = [&](int u) {
        vis[u] = cnt;
        int go = p[u];
        if (vis[go] == 0) {
            dfs(go);
        }
    };

    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            cnt++;
            dfs(i);
        }
    }
    map<int, int> cnt2;
    for (int i = 1; i <= n; i++) {
        cnt2[vis[i]]++;
    }

    int sum = 0;
    set<int> vi2;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        if (!vi2.count(vis[a])) {
            vi2.insert(vis[a]);
            sum += cnt2[vis[a]];
        }
        cout << sum << ' ';
    }
    cout << '\n';
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
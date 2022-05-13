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

typedef pair<int, int> pii;
pii operator+(const pii &a, const pii &b) {
    pii res;
    res.first = a.first + b.first;
    res.second = a.second + b.second;
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> V(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        V[p].push_back(i);
    }
    string s;
    cin >> s;

    int ans = 0;
    function<pii(int)> dfs = [&](int u) -> pii {
        pii res = {0, 0};
        if (s[u] == 'W')
            res.first++;
        else
            res.second++;
        for (auto v : V[u]) {
            res = res + dfs(v);
        }
        if (res.first == res.second) {
            ans++;
        }
        return res;
    };
    dfs(0);
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
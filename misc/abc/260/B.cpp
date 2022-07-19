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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, x, y, z;
    cin >> n >> x >> y >> z;
    vector<int> a(n + 1), b(n + 1);
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    vector<pii> V;
    for (int i = 1; i <= n; i++) {
        V.push_back({a[i], -i});
    }
    sort(V.begin(), V.end());
    reverse(V.begin(), V.end());
    vector<bool> vis(n + 1);
    for (int i = 0; i < x; i++) {
        ans.push_back(-V[i].second);
        vis[-V[i].second] = 1;
    }

    V.clear();
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        V.push_back({b[i], -i});
    }
    sort(V.begin(), V.end());
    reverse(V.begin(), V.end());
    for (int i = 0; i < y; i++) {
        ans.push_back(-V[i].second);
        vis[-V[i].second] = 1;
    }

    V.clear();
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        V.push_back({a[i] + b[i], -i});
    }

    sort(V.begin(), V.end());
    reverse(V.begin(), V.end());
    for (int i = 0; i < z; i++) {
        ans.push_back(-V[i].second);
        vis[-V[i].second] = 1;
    }
    sort(ans.begin(), ans.end());
    for (auto it : ans) {
        cout << it << endl;
    }
    return 0;
}
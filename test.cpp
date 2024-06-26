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
    vector<int> a(n + 1);
    map<int, vector<int>> M;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        M[a[i] / 4].push_back(a[i]);
    }

    for (auto it : M) {
        sort(M[it.first].begin(), M[it.first].end());
    }

    map<int, int> idx;
    vector<int> ans(n + 1);
    for (int i = 1; i <= n; i++) {
        int val = a[i] / 4;
        int the_idx = idx[val];
        ans[i] = M[val][the_idx];
        idx[val]++;
        cout << ans[i] << ' ';
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
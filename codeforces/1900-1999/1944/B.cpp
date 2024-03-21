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
    int n, k;
    cin >> n >> k;
    k *= 2;
    vector<int> a(n * 2 + 1);
    vector<vector<int>> idx(n + 1);
    for (int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
        idx[a[i]].push_back(i);
    }

    vector<int> l, r;
    for (int i = 1; i <= n; i++) {
        if (idx[i][0] <= n && idx[i][1] > n && l.size() < k) {
            l.push_back(idx[i][0]);
            r.push_back(idx[i][1]);
        }
    }

    if ((k - l.size()) % 2) {
        l.pop_back();
        r.pop_back();
    }

    for (int i = 1; i <= n; i++) {
        if (idx[i][0] <= n && idx[i][1] <= n && l.size() < k) {
            l.push_back(idx[i][0]);
            l.push_back(idx[i][1]);
        }
        if (idx[i][0] > n && idx[i][1] > n && r.size() < k) {
            r.push_back(idx[i][0]);
            r.push_back(idx[i][1]);
        }
    }
    for (auto it : l) {
        cout << a[it] << ' ';
    }
    cout << endl;
    for (auto it : r) {
        cout << a[it] << ' ';
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
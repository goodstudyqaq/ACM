#include <bits/stdc++.h>

#include <cstdlib>

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
    int flag[2] = {0, 0};
    int mx = 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (abs(a[i]) > abs(a[mx])) {
            mx = i;
        }
    }

    vector<pii> V;
    for (int i = 1; i <= n; i++) {
        if ((a[mx] < 0) != (a[i] < 0)) {
            V.push_back({i, mx});
            a[i] += a[mx];
        }
    }
    if (a[mx] >= 0) {
        for (int i = 2; i <= n; i++) {
            V.push_back({i, i - 1});
        }
    } else {
        for (int i = n - 1; i >= 1; i--) {
            V.push_back({i, i + 1});
        }
    }
    cout << V.size() << endl;
    for (auto it : V) {
        cout << it.first << ' ' << it.second << endl;
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
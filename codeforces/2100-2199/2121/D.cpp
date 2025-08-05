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
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    vector<pii> ans;

    for (int r = n - 1; r >= 1; r--) {
        for (int i = 0; i < r; i++) {
            if (a[i] > a[i + 1]) {
                ans.push_back({1, i});
                swap(a[i], a[i + 1]);
            }
        }
    }
    for (int r = n - 1; r >= 1; r--) {
        for (int i = 0; i < r; i++) {
            if (b[i] > b[i + 1]) {
                ans.push_back({2, i});
                swap(b[i], b[i + 1]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (a[i] > b[i]) {
            ans.push_back({3, i});
            swap(a[i], b[i]);
        }
    }

    cout << ans.size() << '\n';
    for (auto it : ans) {
        cout << it.first << ' ' << it.second + 1 << '\n';
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
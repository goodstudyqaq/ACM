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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int now = n - 1;

    vector<int> ans(n);
    while (now >= 0) {
        int go = now;
        while (go >= 0 && a[go] == a[now]) go--;
        if (now - go == 1) {
            cout << -1 << endl;
            return;
        }

        for (int i = now; i > go; i--) {
            if (i != go + 1) {
                ans[i] = i - 1;
            } else {
                ans[i] = now;
            }
        }
        now = go;
    }
    for (auto it : ans) {
        cout << it + 1 << ' ';
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
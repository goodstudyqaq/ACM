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
    for (int i = 0; i < n; i++) {
        int idx = i;
        for (int j = i + 1; j < n; j++) {
            if (a[idx] > a[j]) {
                idx = j;
            }
        }
        if (i != idx) {
            ans.push_back({i, idx});
            swap(a[idx], a[i]);
            swap(b[idx], b[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        int idx = i;
        for (int j = i + 1; j < n; j++) {
            if (b[idx] > b[j]) {
                idx = j;
            }
        }

        if (idx != i) {
            if (a[i] != a[idx]) {
                cout << -1 << endl;
                return;
            }
            swap(b[idx], b[i]);
            ans.push_back({i, idx});
        }
    }

    cout << ans.size() << endl;
    for (auto it : ans) {
        cout << it.first + 1 << ' ' << it.second + 1 << endl;
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
}
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
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    map<int, int> M;

    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        if (a[i] != b[i]) {
            M[b[i]]++;
        }
    }

    int m;
    cin >> m;
    vector<int> d(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> d[i];
    }

    vector<int> vis(n + 1);
    int ok = false;
    for (int i = m; i >= 1; i--) {
        if (M[d[i]] > 0) {
            M[d[i]]--;
            ok = true;
        } else {
            if (i == m) {
                for (int j = 1; j <= n; j++) {
                    if (a[j] == b[j] && a[j] == d[i]) {
                        ok = true;
                        break;
                    }
                }
                if (!ok) {
                    cout << "NO" << endl;
                    return;
                }
            } else {
                continue;
            }
        }
    }

    for (auto it : M) {
        if (it.second > 0) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
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
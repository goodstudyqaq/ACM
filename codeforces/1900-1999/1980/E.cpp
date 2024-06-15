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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    vector<vector<int>> b(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> b[i][j];
        }
    }

    set<vector<int>> S;

    for (int i = 1; i <= n; i++) {
        vector<int> V;
        for (int j = 1; j <= m; j++) {
            V.push_back(a[i][j]);
        }
        sort(V.begin(), V.end());
        S.insert(V);
    }

    for (int i = 1; i <= n; i++) {
        vector<int> V;
        for (int j = 1; j <= m; j++) {
            V.push_back(b[i][j]);
        }
        sort(V.begin(), V.end());
        if (S.count(V) == 0) {
            cout << "NO" << endl;
            return;
        }
    }

    S.clear();
    for (int i = 1; i <= m; i++) {
        vector<int> V;
        for (int j = 1; j <= n; j++) {
            V.push_back(a[j][i]);
        }
        sort(V.begin(), V.end());
        S.insert(V);
    }

    for (int i = 1; i <= m; i++) {
        vector<int> V;
        for (int j = 1; j <= n; j++) {
            V.push_back(b[j][i]);
        }
        sort(V.begin(), V.end());
        if (S.count(V) == 0) {
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
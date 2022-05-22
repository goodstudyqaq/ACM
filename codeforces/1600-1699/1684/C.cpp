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
    int n, m;
    cin >> n >> m;
    pii last = {-1, -1};
    vector<vector<int>> a;
    a.resize(n, vector<int>(m));
    vector<int> f(m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            f[j] = j;
        }
        sort(f.begin(), f.end(), [&](int x, int y) {
            return a[i][x] < a[i][y];
        });

        // check 是否只有两个不一样

        vector<int> v;
        for (int j = 0; j < m; j++) {
            if (a[i][f[j]] != a[i][j]) {
                v.push_back(j);
                if (v.size() > 2) {
                    cout << -1 << endl;
                    return;
                }
            }
        }
        if (v.size() == 0) continue;
        pii now = {v[0], v[1]};
        last = now;
        break;
    }

    if (last.first == -1) {
        cout << 1 << ' ' << 1 << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        swap(a[i][last.first], a[i][last.second]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (a[i][j] < a[i][j - 1]) {
                cout << -1 << endl;
                return;
            }
        }
    }
    cout << last.first + 1 << ' ' << last.second + 1 << endl;
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
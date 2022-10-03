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

    auto check = [&](int x, int y) {
        vector<int> v1 = {2, -2};
        vector<int> v2 = {1, -1};
        for (auto it : v1) {
            for (auto it2 : v2) {
                int x2 = x + it;
                int y2 = y + it2;
                if (x2 >= 1 && x2 <= n && y2 >= 1 && y2 <= m) return false;
                y2 = y + it;
                x2 = x + it2;
                if (x2 >= 1 && x2 <= n && y2 >= 1 && y2 <= m) return false;
            }
        }
        return true;
    };

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (check(i, j)) {
                cout << i << ' ' << j << endl;
                return;
            }
        }
    }
    cout << 1 << ' ' << 1 << endl;
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
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

    vector<vector<int>> V(n + 1, vector<int>(2));
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        V[x][y] = 1;
    }

    long long ans = 0;
    for (int i = 0; i <= n; i++) {
        if (V[i][0] == 1 && V[i][1] == 1) {
            ans += n - 2;
        }
    }
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 0; j < 2; j++) {
            if (V[i][j] && V[i - 1][j ^ 1] && V[i + 1][j ^ 1]) {
                ans++;
            }
        }
    }
    cout << ans << endl;
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
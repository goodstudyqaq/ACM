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
    int a_mx = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a_mx = max(a_mx, a[i]);
    }
    int b_mx = 0;
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        b_mx = max(b_mx, b[i]);
    }

    long long ans = 0;
    long long ans2 = 0;

    int LIMIT = sqrt(2 * b_mx) + 1;
    vector<vector<int>> M(LIMIT + 1, vector<int>(b_mx + 1));

    for (int i = 1; i <= n; i++) {
        if (a[i] > LIMIT) continue;
        M[a[i]][b[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        int v1 = a[i];
        // find v2 <= v1
        for (int j = (b[i] - 1) / v1 + 1; j <= LIMIT && j <= v1; j++) {
            int tmp = v1 * j;
            if (v1 == j) {
                if (tmp - b[i] == b[i]) {
                    if (tmp - b[i] <= b_mx)
                        ans2 += M[j][tmp - b[i]] - 1;
                } else {
                    if (tmp - b[i] <= b_mx)
                        ans2 += M[j][tmp - b[i]];
                }
            } else {
                if (tmp - b[i] <= b_mx)
                    ans += M[j][tmp - b[i]];
            }
        }
    }
    cout << ans + ans2 / 2 << endl;
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
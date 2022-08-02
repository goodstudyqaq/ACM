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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;

    map<int, array<vector<int>, 2>> M;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        int x = __builtin_ctz(a[i]);
        M[a[i] >> x][0].push_back(x);
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        int x = __builtin_ctz(b[i]);
        M[b[i] >> x][1].push_back(x);
    }
    int ans = 0;

    while (M.size()) {
        auto [v, f] = *M.rbegin();
        M.erase(v);

        if (f[0].size() < f[1].size()) {
            cout << -1 << endl;
            return 0;
        }

        sort(f[0].begin(), f[0].end(), greater());
        sort(f[1].begin(), f[1].end(), greater());

        int x = __builtin_ctz(v >> 1);
        while (f[0].size() > f[1].size()) {
            auto it = f[0].back();
            f[0].pop_back();
            ans += it + 1;
            M[(v >> 1) >> x][0].push_back(x);
        }

        for (int i = 0; i < f[0].size(); i++) {
            ans += abs(f[0][i] - f[1][i]);
        }
    }
    cout << ans << endl;
    return 0;
}
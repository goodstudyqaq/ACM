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

    int n, m;
    cin >> n >> m;
    vector<ll> s(n);
    for (int i = 1; i <= n - 1; i++) {
        cin >> s[i];
    }
    vector<ll> x(m);
    for (int i = 0; i < m; i++) {
        cin >> x[i];
    }

    vector<ll> a(n + 1);
    a[n] = 0;

    for (int i = n - 1; i >= 1; i--) {
        a[i] = s[i] - a[i + 1];
    }

    map<ll, int> M;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            if ((n - i) % 2) {
                M[-x[j] + a[i]]++;
            } else {
                M[x[j] - a[i]]++;
            }
            // M[x[j] - a[i]]++;
        }
    }
    debug(a);
    debug(M);

    int ans = 0;
    for (auto it : M) {
        ans = max(ans, it.second);
    }
    cout << ans << endl;
}
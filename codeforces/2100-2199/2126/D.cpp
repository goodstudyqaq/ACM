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
    int n, k;
    cin >> n >> k;
    vector<array<int, 3>> v(n);
    for (int i = 0; i < n; i++) {
        int l, r, real;
        cin >> l >> r >> real;
        v[i][0] = l, v[i][1] = r, v[i][2] = real;
    }
    sort(v.begin(), v.end());

    int now = k;
    for (int i = 0; i < n; i++) {
        auto [l, r, real] = v[i];
        if (now >= l && now <= r) {
            now = max(now, real);
        }
    }
    cout << now << endl;

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
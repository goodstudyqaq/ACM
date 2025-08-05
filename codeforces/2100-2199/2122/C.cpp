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
    vector<array<int, 3>> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i][0] >> p[i][1];
        p[i][2] = i + 1;
    }
    sort(p.begin(), p.end());
    vector<array<int, 3>> v1, v2;
    for (int i = 0; i < n / 2; i++) {
        v1.push_back(p[i]);
    }
    for (int i = n / 2; i < n; i++) {
        v2.push_back(p[i]);
    }
    auto cmp = [&](array<int, 3> x, array<int, 3> y) {
        if (x[1] != y[1]) {
            return x[1] < y[1];
        }
        return x[0] < y[0];
    };
    sort(v1.begin(), v1.end(), cmp);
    sort(v2.begin(), v2.end(), cmp);
    long long ans = 0;
    int sz = v2.size();
    for (int i = 0; i < n / 2; i++) {
        // long long tmp = abs(v1[i][0] - v2[sz - 1 - i][0]) + abs(v1[i][1] - v2[sz - 1 - i][1]);
        // ans += tmp;
        cout << v1[i][2] << ' ' << v2[sz - 1 - i][2] << '\n';
    }
    debug(ans);


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
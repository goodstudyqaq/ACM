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
    vector<int> x(n + 1), y(n + 1);
    map<int, int> sum;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
        sum[x[i] + y[i]]++;
    }
    map<int, int> X;
    for (int i = 1; i <= n; i++) {
        X[x[i]]++;
    }
    int ansx = -1, ansy = -1;
    for (auto it : X) {
        if (it.second % 2) {
            ansx = it.first;
            break;
        }
    }

    for (auto it : sum) {
        if (it.second % 2) {
            ansy = it.first - ansx;
        }
    }
    cout << ansx << ' ' << ansy << '\n';

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
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

    cout << n << endl;

    vector<int> V(n);
    iota(V.begin(), V.end(), 0);

    auto out = [&]() {
        for (int i = 0; i < n; i++) {
            cout << V[i] + 1 << ' ';
        }
        cout << endl;
    };

    out();
    swap(V[0], V[1]);
    out();

    for (int i = 2; i < n; i++) {
        swap(V[i], V[i - 1]);
        out();
    }
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
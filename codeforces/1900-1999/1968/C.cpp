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
    vector<int> x(n + 1);
    int sum = 0;
    for (int i = 2; i <= n; i++) {
        cin >> x[i];
        sum += x[i];
    }

    vector<int> a(n + 1);
    a[1] = sum + 1;
    for (int i = 2; i <= n; i++) {
        a[i] = a[i - 1] + x[i];
        debug(i, a[i] % a[i - 1]);
    }
    for (int i = 1; i <= n; i++) {
        cout << a[i] << ' ';
    }

    cout << endl;
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
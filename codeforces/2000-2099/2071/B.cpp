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
    long long sum = 1LL * n * (n + 1) / 2;

    long long s = sqrt(sum);
    if (s * s == sum) {
        cout << -1 << endl;
        return;
    }

    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) {
        v[i] = i;
    }

    sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += v[i];
        s = sqrt(sum);
        if (s * s == sum) {
            sum -= v[i];
            swap(v[i], v[i + 1]);
            sum += v[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << v[i] << ' ';
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
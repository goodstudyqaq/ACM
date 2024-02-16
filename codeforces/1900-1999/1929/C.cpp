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
    int k, x, a;
    cin >> k >> x >> a;

    vector<long long> ct(x + 2);
    ct[1] = 1;
    long long sum = 1;
    for (int i = 2; i <= x + 1; i++) {
        long long v = sum / (k - 1);
        while (v * (k - 1) <= sum) v++;
        ct[i] = v;
        // debug(i, ct[i]);
        sum += v;
        if (sum > a) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
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
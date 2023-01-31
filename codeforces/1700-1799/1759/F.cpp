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
    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    set<int> S;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        S.insert(a[i]);
    }
    if (S.size() == p) {
        cout << 0 << endl;
        return;
    }

    int add = 1;
    // 进位时额外增加 0 和 add
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] != p - 1) {
            add = a[i] + 1;
            break;
        }
    }
    debug(add);

    int val = a[n - 1];
    while (S.count(val)) {
        val = (val - 1 + p) % p;
    }
    debug(val);
    if (val == 0) {
        cout << p - a[n - 1] << endl;
    } else if (val == add) {
        if (add < a[n - 1]) {
            //
            val--;
            while (val && S.count(val)) {
                val--;
            }
            debug(val);
            cout << (val - a[n - 1] + p) % p << endl;
        } else {
            cout << add - a[n - 1] << endl;
        }
    } else {
        cout << (val - a[n - 1] + p) % p << endl;
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
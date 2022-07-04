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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (n % 2) {
        cout << "NO" << endl;
        return;
    }

    sort(a.begin(), a.end());

    vector<int> new_a(n);

    int beg1 = 0, beg2 = n / 2;

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            new_a[i] = a[beg1++];
        } else {
            new_a[i] = a[beg2++];
        }
    }

    for (int i = 0; i < n; i++) {
        int last = (i - 1 + n) % n;
        int next = (i + 1) % n;

        int x = new_a[i], y = new_a[last], z = new_a[next];
        if (x > y && x > z) continue;
        if (x < y && x < z) continue;
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
    for (auto v : new_a) {
        cout << v << ' ';
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
}
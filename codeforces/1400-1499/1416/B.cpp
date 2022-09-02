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
struct Op {
    ll i, j, x;
};

void solve() {
    int n;
    cin >> n;
    ll sum = 0;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    if (sum % n) {
        cout << -1 << endl;
        return;
    }
    vector<Op> V;

    for (int i = 2; i <= n; i++) {
        if (a[i] % i == 0) {
            V.push_back((Op){i, 1, a[i] / i});
        } else {
            int tmp = i - a[i] % i;
            V.push_back((Op){1, i, tmp});
            V.push_back((Op){i, 1, a[i] / i + 1});
        }
    }

    ll need = sum / n;
    for (int i = 2; i <= n; i++) {
        V.push_back((Op){1, i, need});
    }
    cout << V.size() << endl;
    for (auto it : V) {
        cout << it.i << ' ' << it.j << ' ' << it.x << endl;
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
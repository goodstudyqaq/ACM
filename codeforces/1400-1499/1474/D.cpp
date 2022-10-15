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
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    auto check = [&](vector<ll> &v) -> bool {
        ll now = v[0];
        for (int i = 1; i < v.size(); i++) {
            if (now > v[i]) {
                return 0;
            }
            now = v[i] - now;
        }
        return now == 0;
    };

    if (check(a)) {
        cout << "YES" << endl;
        return;
    }

    swap(a[0], a[1]);
    if (check(a)) {
        cout << "YES" << endl;
        return;
    }

    swap(a[0], a[1]);
    swap(a[n - 2], a[n - 1]);
    if (check(a)) {
        cout << "YES" << endl;
        return;
    }
    swap(a[n - 2], a[n - 1]);

    vector<ll> pre(n), lxt(n);
    auto work = [&](vector<ll> &a) -> vector<ll> {
        vector<ll> res(n);
        res[0] = a[0];
        for (int i = 1; i < n; i++) {
            if (res[i - 1] == -1 || res[i - 1] > a[i]) {
                res[i] = -1;
            } else {
                res[i] = a[i] - res[i - 1];
            }
        }
        return res;
    };
    pre = work(a);
    reverse(a.begin(), a.end());
    lxt = work(a);
    reverse(lxt.begin(), lxt.end());
    reverse(a.begin(), a.end());

    for (int i = 1; i < n - 2; i++) {
        if (pre[i - 1] != -1 && lxt[i + 2] != -1) {
            vector<ll> c = {pre[i - 1], a[i + 1], a[i], lxt[i + 2]};
            if (check(c)) {
                cout << "YES" << endl;
                return;
            }
        }
    }
    cout << "NO" << endl;
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
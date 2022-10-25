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
    int num[2] = {0, 0};
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        num[a[i] > 0]++;
    }

    if (n % 2) {
        cout << -1 << endl;
        return;
    }
    if (num[0] == num[1]) {
        cout << n << endl;
        for (int i = 1; i <= n; i++) {
            cout << i << ' ' << i << endl;
        }
        return;
    }
    bool f = (num[0] < num[1]);
    int cnt = (num[f] - num[f ^ 1]) / 2;

    int now = 0;
    vector<pii> res;
    for (int i = 0; i < n; i++) {
        debug(i, cnt);
        if (cnt == 0) {
            res.push_back({i, i});
        } else {
            if (((a[i] > 0) == f) && ((a[i + 1] > 0) == f)) {
                res.push_back({i, i + 1});
                cnt--;
                i++;
            } else {
                res.push_back({i, i});
            }
        }
    }
    cout << res.size() << endl;
    for (auto it : res) {
        cout << it.first + 1 << ' ' << it.second + 1 << endl;
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
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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<pii> res;

    int now = 0;
    while (now < n) {
        int go = now;
        while (go < n && a[go] != 0) go++;
        if (go == n) break;

        if (go + 1 < n) {
            int times = res.size();
            res.push_back({go - times, go + 1 - times});
            now = go + 2;
        } else {
            int times = res.size();
            res.push_back({go - times - 1, go - times});
            now = go + 1;
        }
    }

    int times = res.size();
    res.push_back({0, n - times - 1});
    cout << res.size() << '\n';
    for (auto it : res) {
        cout << it.first + 1 << ' ' << it.second + 1 << '\n';
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
    return 0;
}
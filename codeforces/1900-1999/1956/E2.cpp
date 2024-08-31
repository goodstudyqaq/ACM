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

    auto work = [&]() {
        for (int i = 0; i < n; i++) {
            int r = (i + 1) % n;
            a[r] = max(0, a[r] - a[i]);
        }
    };
    for (int i = 0; i < 2000; i++) {
        work();
    }

    vector<int> ans;

    for (int i = 0; i < n; i++) {
        if (a[i]) continue;

        vector<int> v;
        for (int j = (i + 1) % n; a[j]; j = (j + 1) % n) {
            v.push_back(j);
        }
        if (v.size() == 0) continue;
        assert(v.size() <= 3);

        ans.push_back(v[0]);
        if (v.size() == 3) {
            long long l = a[v[1]] % a[v[0]];
            long long r = a[v[1]] - a[v[0]];
            long long times = (r - l) / a[v[0]] + 1;
            long long ct = (l + r) * times / 2;
            if (v[0] == n - 1) {
                ct += a[0];
            }
            if (a[v[2]] > ct) {
                ans.push_back(v[2]);
            }
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto it : ans) {
        cout << it + 1 << ' ';
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
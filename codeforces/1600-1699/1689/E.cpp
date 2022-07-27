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
#define lowbit(x) x & -x

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    int ans = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == 0) {
            a[i]++;
            ans++;
        }
    }
    debug(ans);
    auto check = [&]() {
        vector<int> f(n);
        iota(f.begin(), f.end(), 0);

        function<int(int)> find = [&](int u) {
            return f[u] == u ? u : f[u] = find(f[u]);
        };
        auto Union = [&](int x, int y) {
            int fx = find(x), fy = find(y);
            f[fx] = fy;
        };

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (a[i] & a[j]) {
                    Union(i, j);
                }
            }
        }

        int res = 0;
        for (int i = 0; i < n; i++) {
            if (f[i] == i) res++;
        }

        return (res == 1);
    };

    auto out = [&]() {
        cout << ans << endl;
        for (auto it : a) {
            cout << it << ' ';
        }
        cout << endl;
    };

    if (check()) {
        out();
        return;
    }

    for (int i = 0; i < n; i++) {
        a[i]++;
        if (check()) {
            ans++;
            out();
            return;
        }
        a[i]--;

        if (a[i] > 1) {
            a[i]--;
            if (check()) {
                ans++;
                out();
                return;
            }
            a[i]++;
        }
    }

    ans += 2;
    vector<int> f(n);
    iota(f.begin(), f.end(), 0);
    sort(f.begin(), f.end(), [&](int x, int y) {
        return lowbit(a[x]) > lowbit(a[y]);
    });
    debug(f);
    a[f[0]]--;
    a[f[1]]++;
    out();
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
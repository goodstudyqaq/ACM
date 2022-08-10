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

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> stk;
    vector<int> mx(n + 1, n + 1), mi(n + 1, n + 1);
    for (int i = n; i >= 1; i--) {
        while (stk.size() && a[stk.back()] < a[i]) {
            stk.pop_back();
        }
        if (stk.size()) {
            mx[i] = stk.back();
        }
        stk.push_back(i);
    }
    stk.clear();
    for (int i = n; i >= 1; i--) {
        while (stk.size() && a[stk.back()] > a[i]) {
            stk.pop_back();
        }
        if (stk.size()) {
            mi[i] = stk.back();
        }
        stk.push_back(i);
    }

    int now = 1;
    int ans = 0;
    // debug("zz");
    while (now < n) {
        // debug(now);
        ans++;
        int limit;
        if (now == n - 1) break;
        if (a[now] < a[now + 1]) {
            // now 是小的，要找大的
            limit = mi[now];
            int go = now + 1;
            while (go <= n && mx[go] != n + 1 && mx[go] <= limit) {
                go = mx[go];
            }
            now = go;
        } else {
            limit = mx[now];
            int go = now + 1;
            while (go <= n && mi[go] != n + 1 && mi[go] <= limit) {
                go = mi[go];
            }
            now = go;
        }
    }
    cout << ans << endl;
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
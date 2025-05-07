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
    vector<int> a(n + 1), b(n + 1);
    vector<int> idx(n + 1);
    vector<int> idx2(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        idx[a[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        idx2[b[i]] = i;
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        int _a = a[i];
        int _b = b[i];
        if (_a == _b) {
            cnt++;
            continue;
        }

        // a[i] -> b[i]
        int _idx = idx[b[i]];
        int _c = b[_idx];
        if (_a != _c) {
            cout << -1 << '\n';
            return;
        }
    }

    if (n % 2 && cnt != 1) {
        cout << -1 << '\n';
        return;
    }

    if (n % 2 == 0 && cnt != 0) {
        cout << -1 << '\n';
        return;
    }

    vector<pair<int, int>> ans;

    auto work = [&](int i, int j) {
        swap(idx[a[i]], idx[a[j]]);
        swap(idx2[b[i]], idx2[b[j]]);
        swap(a[i], a[j]);
        swap(b[i], b[j]);
        ans.push_back({i, j});
    };

    for (int i = 1; i <= n; i++) {
        int val = a[i];
        int val2 = b[i];
        if (val == val2) continue;

        int idx1 = idx[val2];
        debug(i, idx1);
        if (i + idx1 != n + 1) {
            // 把 idx1 和 n - i + 1 交换位置
            work(idx1, n - i + 1);
        }
    }

    cout << ans.size() << '\n';
    for (auto it : ans) {
        cout << it.first << ' ' << it.second << '\n';
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
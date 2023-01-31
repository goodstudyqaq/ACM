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
    vector<int> a(n / 2 + 1);
    set<int> S;
    for (int i = 1; i <= n; i++) {
        S.insert(-i);
    }

    for (int i = 1; i <= n / 2; i++) {
        cin >> a[i];
        S.erase(-a[i]);
    }
    map<int, int> M;
    for (int i = 1; i <= n / 2; i++) {
        M[a[i]] = i;
    }

    set<int> S2;
    vector<int> res(n + 1);

    for (int i = 2; i <= n; i += 2) {
        res[i] = a[i / 2];
    }

    while (S.size()) {
        int val = *S.begin();
        val = -val;
        debug(val);
        while (M.size()) {
            auto it = prev(M.end());
            if (it->first > val) {
                S2.insert(it->second);
                M.erase(it);
            } else {
                break;
            }
        }

        if (S2.size() == 0) {
            cout << -1 << endl;
            return;
        }

        auto it = prev(S2.end());
        int idx = *it * 2 - 1;
        debug(val, idx);
        res[idx] = val;
        S.erase(S.begin());
        S2.erase(it);
    }

    for (int i = 1; i <= n; i++) {
        cout << res[i] << ' ';
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
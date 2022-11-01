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
    set<int> S;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        S.insert(a[i]);
    }

    vector<int> ans(n + 1);

    for (int i = 1; i < n; i++) {
        if (a[i] > a[i + 1]) {
            int tmp = a[i] - a[i + 1];
            auto it = S.lower_bound(tmp);
            ans[*it] = i + 1;
            S.erase(it);
        }
    }
    while (S.size()) {
        ans[*S.begin()] = 1;
        S.erase(S.begin());
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
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
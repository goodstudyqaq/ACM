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
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    const int MAX = 4 * n;
    vector<vector<int>> idx(MAX + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        idx[a[i]].push_back(i);
    }
    set<int> S;
    int now = 1;
    int ans = 0;
    while (now <= MAX) {
        int go = now;
        int res = 0;
        while (go <= MAX) {
            for (auto j : idx[go]) {
                S.insert(j);
            }
            if (S.size() <= k) {
                S.clear();
                break;
            }
            res++;
            S.erase(S.begin());
            go++;
        }
        ans = max(ans, res);
        now = go + 1;
    }
    cout << ans << '\n';
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
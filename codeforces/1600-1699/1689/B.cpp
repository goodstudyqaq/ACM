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
    vector<int> p(n);
    set<int> S;
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        S.insert(i);
    }

    if (n == 1) {
        cout << -1 << endl;
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        auto it = S.begin();
        while (*it == p[i]) {
            it++;
        }
        ans[i] = *it;
        S.erase(it);
    }
    ans[n - 1] = *S.begin();

    if (ans[n - 1] == p[n - 1]) {
        swap(ans[n - 1], ans[n - 2]);
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << ' ';
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
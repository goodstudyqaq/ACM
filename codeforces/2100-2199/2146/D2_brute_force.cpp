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
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int l, r;
    cin >> l >> r;
    int n = r - l + 1;
    vector<int> ans(n);

    for (int i = 0; i < n; i++) {
        ans[i] = l + i;
    }

    vector<int> res;
    ll score = 0;
    do {
        ll now = 0;
        for (int i = 0; i < n; i++) {
            now += ((l + i) ^ ans[i]);
        }
        if (now > score) {
            score = now;
            res = ans;
        }

    } while (next_permutation(ans.begin(), ans.end()));

    cout << score << '\n';
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
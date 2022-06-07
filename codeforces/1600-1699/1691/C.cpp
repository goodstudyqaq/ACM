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
    int n, k;
    string s;
    cin >> n >> k >> s;

    vector<int> V;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            V.push_back(i);
        }
    }

    if (V.size() == 0) {
        cout << 0 << endl;
        return;
    } else if (V.size() == 1) {
        int tmp1 = V[0];
        int tmp2 = n - V[0] - 1;

        if (k >= tmp2) {
            cout << 1 << endl;
        } else if (k >= tmp1) {
            cout << 10 << endl;
        } else {
            cout << 11 << endl;
        }
        return;
    }
    int sz = V.size();
    int last_one_idx = V.back();
    int need_move = n - last_one_idx - 1;
    int ans = 10 * sz + sz;
    if (k >= need_move) {
        ans -= 10;
        k -= need_move;
    }

    int first_one_idx = V[0];
    if (k >= first_one_idx) {
        ans -= 1;
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
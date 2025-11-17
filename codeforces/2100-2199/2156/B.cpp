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
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;

    bool has_b = false;
    for (auto it : s) {
        if (it == 'B') {
            has_b = true;
        }
    }

    auto work = [&](int val) {
        if (!has_b) {
            cout << val << '\n';
            return;
        }

        int now = 0;
        int ans = 0;
        while (val) {
            if (s[now] == 'A') {
                val--;
            } else {
                val = val / 2;
            }
            ans++;
            now = (now + 1) % n;
        }
        cout << ans << '\n';
    };

    for (int i = 0; i < q; i++) {
        int a;
        cin >> a;
        work(a);
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
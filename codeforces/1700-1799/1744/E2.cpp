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
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    map<int, int> M;
    int x = a;
    for (int i = 2; 1LL * i * i <= x; i++) {
        if (x % i == 0) {
            while (x % i == 0) {
                M[i]++;
                x /= i;
            }
        }
    }

    if (x != 1) {
        M[x]++;
    }

    x = b;
    for (int i = 2; 1LL * i * i <= x; i++) {
        if (x % i == 0) {
            while (x % i == 0) {
                M[i]++;
                x /= i;
            }
        }
    }
    if (x != 1) {
        M[x]++;
    }

    auto work = [&](ll val, ll l, ll r) -> ll {
        ll tmp1 = (l + 1) / val, tmp2 = r / val;
        if (tmp1 != tmp2) {
            return tmp2 * val;
        } else {
            if (tmp1 * val > l && tmp1 * val <= r) {
                return tmp1 * val;
            }
            return -1;
        }
    };

    function<bool(ll x, map<int, int>::iterator now)> dfs = [&](ll now_val, auto now) -> bool {
        if (now == M.end()) {
            ll x = work(now_val, a, c);
            ll y = work(a * b / now_val, b, d);
            if (x > 0 && y > 0) {
                cout << x << ' ' << y << endl;
                return true;
            }
            return false;
        }

        auto [val, num] = *now;

        for (int i = 0; i <= num; i++) {
            if (dfs(now_val, next(now))) return true;
            now_val *= val;
        }

        return false;
    };

    if (!dfs(1, M.begin())) {
        cout << -1 << ' ' << -1 << endl;
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
}
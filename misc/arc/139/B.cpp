#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    ll N, A, B, X, Y, Z;
    cin >> N >> A >> B >> X >> Y >> Z;

    if (X * A <= Y && X * B <= Z) {
        cout << N * X << endl;
    } else if (X * A <= Y) {
        ll tmp = N / B;
        cout << tmp * Z + (N % B) * X << endl;
    } else if (X * B <= Z) {
        ll tmp = N / A;
        cout << tmp * Y + (N % A) * X << endl;
    } else {
        if (Y * B > A * Z) {
            swap(A, B);
            swap(Y, Z);
        }
        ll tmp1 = N / A;
        ll tmp2 = A - 1;
        if (tmp1 <= tmp2) {
            ll ans = 1e18 + 10;
            for (ll i = 0; i <= tmp1; i++) {
                ll use = i * A;
                ll ct = i * Y;
                if (use > N) break;
                ll have = N - use;
                ans = min(ans, ct + (have / B) * Z + (have % B) * X);
            }
            cout << ans << endl;
        } else {
            ll ans = 1e18 + 10;
            for (ll i = 0; i <= tmp2; i++) {
                ll use = i * B;
                ll ct = i * Z;
                if (use > N) break;
                ll have = N - use;
                ans = min(ans, ct + (have / A) * Y + (have % A) * X);
            }
            cout << ans << endl;
        }
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
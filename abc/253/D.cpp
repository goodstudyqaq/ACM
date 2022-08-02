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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    ll N, A, B;
    cin >> N >> A >> B;
    ll ans = N * (N + 1) / 2;

    auto get_num = [&](ll val) -> ll {
        ll num = N / val;
        ll res = num * (num + 1) / 2 * val;
        return res;
    };

    ans = ans - get_num(A) - get_num(B) + get_num(A * B / __gcd(A, B));
    cout << ans << endl;
}
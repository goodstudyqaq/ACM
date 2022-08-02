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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int N;
    cin >> N;

    ll ans = 0;

    vector<ll> V;

    for (ll i = 1; i <= N; i++) {
        V.push_back(i * i);
    }

    auto cal = [&](int a) -> int {
        ll new_a2 = a;
        ll new_a = 1;
        for (int i = 2; i * i <= a; i++) {
            if (a % i == 0) {
                int cnt = 0;
                while (a % i == 0) {
                    a /= i;
                    cnt++;
                }
                if (cnt % 2) new_a *= i;
            }
        }

        if (a != 1) {
            new_a *= a;
        }
        ll other = N / new_a;

        int idx = upper_bound(V.begin(), V.end(), other) - V.begin();
        return idx;
    };

    for (int i = 1; i <= N; i++) {
        int res = cal(i);
        debug(i, res);
        ans += res;
    }

    cout << ans << endl;
}
#include <bits/stdc++.h>

#include <queue>

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
    int n;
    long long k;
    cin >> n >> k;

    vector<int> a(n);
    priority_queue<pll, vector<pll>, greater<>> Q;

    auto work = [&](long long val) -> long long {
        for (int i = 0; i < 60; i++) {
            if ((val >> i) & 1) {
                continue;
            }
            return 1LL << i;
        }
    };
    int ans = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        Q.push({work(a[i]), a[i]});
        ans += __builtin_popcount(a[i]);
    }

    while (!Q.empty()) {
        auto [need, val] = Q.top();
        Q.pop();

        if (k < need) {
            break;
        }
        k -= need;

        val += need;

        ans++;
        Q.push({work(val), val});

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
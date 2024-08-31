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
    vector<int> a(n);
    vector<long long> b(n);
    vector<vector<int>> V(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        V[p].push_back(i);
    }

    long long ans = 0;

    auto get_sum = [&](int u) {
        long long sum = 0;
        for (auto it : V[u]) {
            sum += a[it];
        }
        return sum;
    };
    for (int i = 0; i < n; i++) {
        if (V[i].size() == 0) {
            b[i] = 1e10;
        } else {
            b[i] = get_sum(i) - a[i];
        }
    }

    auto work = [&](int u) {
        queue<pii> Q;
        Q.push({u, 0});
        long long need = abs(b[u]);

        while (!Q.empty() && need) {
            auto [u, d] = Q.front();
            Q.pop();
            if (b[u] > 0) {
                long long tmp = min(need, b[u]);
                ans += 1LL * tmp * d;
                b[u] -= tmp;
                need -= tmp;
            }

            for (auto it : V[u]) {
                Q.push({it, d + 1});
            }
        }
        b[u] = 0;
    };

    for (int i = n - 1; i >= 0; i--) {
        if (b[i] < 0) {
            work(i);
        }
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
    return 0;
}
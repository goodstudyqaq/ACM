#include <bits/stdc++.h>

#include <algorithm>
#include <numeric>

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

struct Prime {
    vector<int> primes;
    vector<int> min_factor;
    vector<int> euler_phi;
    vector<int> mobius;
    vector<int> prm_num;

    vector<int> max_prm;
    // O(n)
    int n;
    Prime(int n) : n(n) {
        min_factor.resize(n + 1);
        euler_phi.resize(n + 1);
        mobius.resize(n + 1);
        prm_num.resize(n + 1);
        euler_phi[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (min_factor[i] == 0) {
                min_factor[i] = i;
                primes.push_back(i);
                euler_phi[i] = i - 1;
                mobius[i] = -1;
                prm_num[i] = 1;
            }
            for (int j = 0; j < primes.size() && primes[j] <= min_factor[i] && i * primes[j] <= n; j++) {
                min_factor[i * primes[j]] = primes[j];
                if (min_factor[i] == primes[j]) {
                    euler_phi[i * primes[j]] = euler_phi[i] * primes[j];
                    mobius[i * primes[j]] = 0;
                    prm_num[i * primes[j]] = prm_num[i];
                } else {
                    euler_phi[i * primes[j]] = euler_phi[i] * (primes[j] - 1);
                    mobius[i * primes[j]] = -mobius[i];
                    prm_num[i * primes[j]] = prm_num[i] + 1;
                }
            }
        }
    }

    void init_max_prm() {
        // 预处理 [2, n] 每个数的最大质因数
        for (int i = 2; i <= n; i++) {
            if (min_factor[i] == i) {
                // 质数
                max_prm[i] = i;
            }
            max_prm[i] = max_prm[i / min_factor[i]];
        }
    }
} P(1e5);

void solve() {
    int n;
    cin >> n;
    int half = n / 2;

    int p = *lower_bound(P.primes.begin(), P.primes.end(), half);
    vector<int> ans(n);
    iota(ans.begin(), ans.end(), 1);

    sort(ans.begin(), ans.end(), [&](int x, int y) {
        int dis = abs(x - p);
        int dis2 = abs(y - p);
        if (dis != dis2) {
            return dis < dis2;
        }
        return x < y;
    });
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
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
#include <bits/stdc++.h>

#include <utility>

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
} Prime(2000001);

void solve() {
    int n, m;
    cin >> n >> m;
    if (n > m) swap(n, m);
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= m; j++) {
    //         int g = __gcd(i, j);
    //         if ((j * g) % (i + j) == 0) {
    //             debug(i, j);
    //         }
    //     }
    // }


    auto work2 = [&](int g, int k) -> long long {
        int x = g / k;

        int k1_limit = min(n / g, x - 1);
        int k2_limit = min(m / g, x - 1);
        if (k1_limit == x - 1 && k2_limit == x - 1) {
            return Prime.euler_phi[x];
        }

        // 求 k1 + k2 = x 的个数，且 k1 <= k1_limit, k2 <= k2_limit gcd(k1, k2) = 1
        // int res = work3(k1_limit, x) - work3(x - k2_limit - 1, x);
        int res = 0;
        for (int k1 = x - k2_limit; k1 <= k1_limit; k1++) {
            int k2 = x - k1;
            if (__gcd(k1, k2) == 1) res++;
        }
        return res;
    };

    int mi = min(n, m);
    auto work = [&](int k) -> int {
        int res = 0;

        for (int g = k + k; g <= mi; g += k) {
            res += work2(g, k);
        }
        return res;
    };

    int ans = 0;
    for (int k = 1; k <= mi; k++) {
        ans += work(k);
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
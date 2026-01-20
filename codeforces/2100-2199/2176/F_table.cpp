#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;


/*
cnt[i] i 的个数, 返回 g，g[i] 表示两两求 gcd 等于 i 的个数
*/
vector<long long> get_gcd_cnt(vector<int> cnt) {
    int n = cnt.size();
    for (int i = 1; i < n; i++) {
        for (int j = i + i; j < n; j += i) {
            cnt[i] += cnt[j];
        }
    }
    vector<long long> g(n);
    for (int i = 1; i < n; i++) {
        g[i] = 1LL * cnt[i] * (cnt[i] - 1) / 2;
    }
    for (int i = n - 1; i >= 1; i--) {
        for (int j = i + i; j < n; j += i) {
            g[i] -= g[j];
        }
    }
    return g;
}

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
} Primes(2e5);



int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    auto p = Primes.primes;

    long long now = 1;
    for (int i = 0; i < p.size(); i++) {
        now *= p[i];
        debug(now);
        if (now > 2e5) {
            cout << i << '\n';
            break;
        }
    }



}
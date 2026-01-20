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
} Primes(5000);

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;

    const int maxm = 1.5e7;
    vector<int> cnt(maxm + 1);
    vector<int> a(n);
    int g = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        g = gcd(g, a[i]);
    }
    sort(a.begin(), a.end());
    if (a[0] == a[n - 1]) {
        cout << -1 << '\n';
        return 0;
    }
    for (int i = 0; i < n; i++) {
        a[i] /= g;
    }

    map<int, int> M;
    auto& primes = Primes.primes;
    int tot = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 1) continue;
        tot++;
        for (int j = 0; primes[j] * primes[j] <= a[i]; j++) {
            if (a[i] % primes[j] == 0) {
                M[primes[j]]++;
                while (a[i] % primes[j] == 0) {
                    a[i] /= primes[j];
                }
            }
        }
        if (a[i] != 1) {
            M[a[i]]++;
        }
    }

    int mx = 0;
    for (auto it : M) {
        mx = max(mx, it.second);
    }
    cout << n - mx << '\n';
}
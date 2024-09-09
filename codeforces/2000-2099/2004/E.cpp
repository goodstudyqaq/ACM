#include <bits/stdc++.h>

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
    vector<int> id;
    // O(n)
    int n;
    Prime(int n) : n(n) {
        min_factor.resize(n + 1);
        euler_phi.resize(n + 1);
        mobius.resize(n + 1);
        prm_num.resize(n + 1);
        id.resize(n + 1);
        int num = 0;
        for (int i = 2; i <= n; i++) {
            if (min_factor[i] == 0) {
                min_factor[i] = i;
                primes.push_back(i);
                euler_phi[i] = i - 1;
                mobius[i] = -1;
                prm_num[i] = 1;
                id[i] = ++num;
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
} Primes(1e7 + 1);

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> sg(n);
    int res = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] % 2 == 0) continue;
        if (a[i] == 1) {
            sg[i] = 1;
        } else {
            sg[i] = Primes.id[Primes.min_factor[a[i]]];
        }
        debug(i, sg[i]);
        res ^= sg[i];
    }

    if (res) {
        cout << "Alice" << endl;
    } else {
        cout << "Bob" << endl;
    }

    // int n = 50;
    // vector<int> sg(n + 1);
    // sg[0] = 0;
    // for (int i = 1; i <= n; i++) {
    //     set<int> v;
    //     for (int j = 1; j <= i; j++) {
    //         if (gcd(i, j) == 1) {
    //             v.insert(sg[i - j]);
    //         }
    //     }
    //     sg[i] = 0;
    //     while (v.count(sg[i])) sg[i]++;
    // }
    // for (int i = 1; i <= 50; i += 2) {
    //     debug(i, sg[i]);
    // }
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
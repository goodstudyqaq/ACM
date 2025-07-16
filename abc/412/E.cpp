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

typedef long long ll;
const int MAXN = 10000000 + 5;
ll is_prime1[MAXN];
ll is_prime2[MAXN];

void get_primes(ll a, ll b) {
    // ------------初始化 --------------
    for (ll i = 0; i * i < b; i++)
        is_prime1[i] = 1;
    is_prime1[0] = is_prime1[1] = 0;

    for (ll i = a; i < b; i++)
        is_prime2[i - a] = 1;
    // ---------------------------------

    for (ll i = 2; i * i < b; i++) {
        if (is_prime1[i]) {
            // 筛is_primes1
            for (ll j = (ll)2 * i; j * j < b; j += i)
                is_prime1[j] = 0;

            // 筛is_primes2
            for (ll j = (ll)(a - 1 + i) / i * i; j < b; j += i)
                is_prime2[j - a] = 0;
        }
    }
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
        euler_phi[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (min_factor[i] == 0) {
                min_factor[i] = i;
                primes.push_back(i);
                euler_phi[i] = i - 1;
                mobius[i] = -1;
                prm_num[i] = 1;
            }
            for (int j = 0; j < primes.size() && primes[j] <= min_factor[i] && 1LL * i * primes[j] <= n; j++) {
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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    long long L, R;
    cin >> L >> R;

    get_primes(L, R + 1);
    long long ans = 0;
    bool add = false;
    for (long long i = L; i <= R; i++) {
        if (is_prime2[i - L]) {
            if (i == L) {
                add = true;
            }
            ans++;
        }
    }
    debug(ans);

    auto &ps = Primes.primes;
    for (auto p : ps) {
        if (p > R) break;
        long long now = p;
        while (now < L) now *= p;
        if (now == L) {
            add = true;
        }

        int num = 0;
        while (now <= R) {
            num++;
            now *= p;
        }

        if (1LL * p >= L) num--;

        ans += num;
    }
    if (!add) ans++;
    cout << ans << '\n';
}
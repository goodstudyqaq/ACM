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
const int maxn = 1e5;
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
        mobius[1] = 1;
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
} Primes(maxn);
// vector<int> prime;
// const int N = 1e5 + 10;
// bool zs[N];
// int phi[N];
// void get_phi() {
//     phi[1] = 1;
//     for (int i = 2; i <= N - 5; i++) {
//         if (!zs[i]) zs[i] = true, prime.push_back(i), phi[i] = i - 1;
//         for (int j = 0; j < prime.size() && prime[j] * i <= N - 5; j++) {
//             auto h = prime[j];
//             zs[i * h] = true;
//             if (!(i % h)) {
//                 phi[i * h] = phi[i] * h;
//                 break;
//             }
//             phi[i * h] = phi[i] * phi[h];
//         }
//     }
//     return;
// }

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    long long ans = 0;
    vector<int> cnt(maxn + 1);
    for (int i = 0; i < n - 1; i++) {
        int val = a[i];
        long long sub = 0;
        for (int j = 1; j * j <= val; j++) {
            if (val % j == 0) {
                sub += 1LL * Primes.euler_phi[j] * cnt[j];
                cnt[j]++;
                if (j * j != val) {
                    int j2 = val / j;
                    sub += 1LL * Primes.euler_phi[j2] * cnt[j2];
                    cnt[j2]++;
                }
            }
        }
        ans += sub * (n - i - 1);
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    // get_phi();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
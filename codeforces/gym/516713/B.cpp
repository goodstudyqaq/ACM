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

// 时间复杂度O(n)
const int maxn = 2e7 + 5;
struct Prime {
    vector<int> primes;
    vector<int> min_factor;
    vector<int> euler_phi;
    vector<int> mobius;
    vector<int> prm_num;
    // O(n)
    Prime(int n) {
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
} Prime(maxn);

int two[26];


int work2(int k, int g) {
    return two[Prime.prm_num[k]];
    // return ans;
}

void solve() {
    int c, d, x;
    cin >> c >> d >> x;

    long long ans = 0;

    auto work = [&](int g) {
        int k2 = x / g;
        if ((k2 + d) % c == 0) {
            int k = (k2 + d) / c;
            ans += work2(k, g);
        }
    };

    // 1e4
    for (int g = 1; g * g <= x; g++) {
        if (x % g == 0) {
            work(g);
            if (x / g != g) {
                work(x / g);
            }
        }
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    two[0] = 1;
    for (int i = 1; i < 26; i++) two[i] = two[i - 1] * 2;

    // for (int i = 1; i < maxn; i++) {
    //     work2(i, 1);
    // }

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
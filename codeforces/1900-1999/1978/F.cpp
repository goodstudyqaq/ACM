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
} Prime(1e6);

struct DSU {
    std::vector<int> f;
    DSU(int n) : f(n) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        if (f[x] == x) {
            return x;
        }
        int y = leader(f[x]);
        f[x] = y;
        return f[x];
    }
    bool merge(int a, int b) {
        auto x = leader(a);
        auto y = leader(b);
        if (x == y) {
            return false;
        }
        f[x] = y;
        return true;
    }
};

void solve() {
    long long n, k;
    cin >> n >> k;
    vector<int> a(n * 2 + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[n + i] = a[i];
    }

    map<int, vector<int>> V;
    for (int i = 2; i <= n * 2; i++) {
        int val = a[i];

        for (int j = 0; j < Prime.primes.size() && 1LL * Prime.primes[j] * Prime.primes[j] <= val; j++) {
            if (val % Prime.primes[j] == 0) {
                V[Prime.primes[j]].push_back(i);
                while (val % Prime.primes[j] == 0) {
                    val /= Prime.primes[j];
                }
            }
        }
        if (val != 1) {
            V[val].push_back(i);
        }
    }

    DSU dsu(2 * n + 1);
    for (auto it : V) {
        int sz = it.second.size();
        for (int i = 0; i < sz - 1; i++) {
            int x = it.second[i], y = it.second[i + 1];
            if (y - x <= k) {
                dsu.merge(x, y);
            }
        }
    }

    set<int> S;
    int one = 0;
    for (int i = 2; i <= 2 * n; i++) {
        if (a[i] == 1) {
            continue;
        }
        S.insert(dsu.leader(i));
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) one++;
    }
    debug(S);
    cout << 1LL * S.size() + 1LL * one * n << endl;
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
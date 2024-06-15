#include <bits/stdc++.h>

#include <functional>

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

struct edge {
    int to;
    bool exists;
    int revref;

    bool operator<(const edge& b) const { return to < b.to; }
};

const int maxn = 2e3 + 5;
vector<edge> beg[maxn];
int cnt[maxn];

stack<int> ans;

void Hierholzer(int x, int d) {  // 关键函数
    debug(x, d);
    for (int& i = cnt[x]; i < (int)beg[x].size();) {
        if (beg[x][i].exists) {
            edge e = beg[x][i];
            beg[x][i].exists = 0;
            beg[e.to][e.revref].exists = 0;
            ++i;
            Hierholzer(e.to, d + 1);
        } else {
            ++i;
        }
    }
    ans.push(x);
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
} Prime(1e5);

void solve() {
    int n;
    cin >> n;
    int now = 1;
    debug(Prime.primes.size());

    function<long long(int)> f = [&](int x) {
        if (x == 1)
            return 1LL;
        else if (x == 2)
            return 3LL;
        if (x % 2) {
            return x + 1LL * x * (x - 1) / 2;
        } else {
            return 1LL * x * (x - 1) / 2 - (x - 2) / 2 + x;
        }
    };

    while (f(now) < n - 1) {
        now++;
    }
    debug(now);

    auto work = [&](int num) {
        for (int i = 1; i <= num; i++) {
            beg[i].clear();
            cnt[i] = 0;
        }
        while (ans.size()) {
            ans.pop();
        }

        if (num % 2) {
            // 完全图
            for (int i = 1; i <= num; i++) {
                beg[i].push_back(edge{i, 1, 0});
            }

            for (int i = 1; i <= num; i++) {
                for (int j = i + 1; j <= num; j++) {
                    int sz1 = beg[i].size();
                    int sz2 = beg[j].size();
                    beg[i].push_back(edge{j, 1, sz2});
                    beg[j].push_back(edge{i, 1, sz1});
                }
            }
        } else {
            for (int i = 1; i <= num; i++) {
                beg[i].push_back(edge{i, 1, 0});
            }
            int remove = (num - 2) / 2;
            for (int i = 1; i <= num; i++) {
                for (int j = i + 1; j <= num; j++) {
                    if (i > 2 && i % 2 == 0 && j == i + 1) {
                        continue;
                    }

                    int sz1 = beg[i].size();
                    int sz2 = beg[j].size();
                    beg[i].push_back(edge{j, 1, sz2});
                    beg[j].push_back(edge{i, 1, sz1});
                }
            }
        }
        debug("zzz");
        Hierholzer(1, 1);
    };
    work(now);
    vector<int> res;
    int nn = n;
    while (ans.size() && n) {
        // cout << ans.top() << ' ';
        // res.push_back(Prime.primes[ans.top()]);
        cout << Prime.primes[ans.top()] << ' ';
        ans.pop();
        n--;
    }
    cout << endl;

    // set<int> S;
    // set<pair<int, int>> S2;
    // for (int i = 0; i < nn - 1; i++) {
    //     int mi = min(res[i], res[i + 1]);
    //     int mx = max(res[i], res[i + 1]);
    //     if (S2.count({mi, mx})) {
    //         debug(mi, mx);
    //     } else {
    //         S2.insert({mi, mx});
    //     }
    //     S.insert(res[i] * res[i + 1]);
    // }
    // debug(S.size(), nn);
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
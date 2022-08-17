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

template <typename T>
struct Fenwick {
#define lowbit(x) x & -x
    const int n;
    vector<T> a;
    Fenwick(int n) : n(n), a(n + 1) {}
    void add(int x, T v) {
        while (x <= n) {
            a[x] += v;
            x += lowbit(x);
        }
    }

    T query(int x) {
        T res = 0;
        while (x) {
            res += a[x];
            x -= lowbit(x);
        }
        return res;
    }
};
const int MAXN = 2e5;
int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    vector<vector<int>> fac;
    fac.resize(2 * MAXN + 1);
    for (int i = 1; i <= MAXN; i++) {
        for (int j = 2 * i; j <= MAXN; j += i) {
            fac[j].push_back(i);
        }
    }

    int T;
    cin >> T;
    vector<vector<pii>> query;
    query.resize(MAXN + 1);
    vector<ll> ans;
    ans.resize(T);
    for (int i = 0; i < T; i++) {
        int l, r;
        cin >> l >> r;
        query[r].push_back({l, i});
        ll x = r - l + 1;
        ans[i] = x * (x - 1) * (x - 2) / 6;
    }
    Fenwick<ll> fen(MAXN);

    for (int k = 2; k <= MAXN; k++) {
        for (int i = 0; i < fac[2 * k].size(); i++) {
            int val_i = fac[2 * k][i];
            if (val_i >= k) break;
            int cnt = 0;
            for (int j = i + 1; j < fac[2 * k].size(); j++) {
                int val_j = fac[2 * k][j];
                if (val_j >= k) break;
                if ((k % val_i == 0 && k % val_j == 0) || val_i + val_j > k) {
                    cnt++;
                }
            }
            fen.add(val_i, cnt);
        }

        for (auto it : query[k]) {
            ans[it.second] -= fen.query(k) - fen.query(it.first - 1);
        }
    }

    for (int i = 0; i < T; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
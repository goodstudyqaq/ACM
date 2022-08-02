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
int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<pii> V(n + 1);
    map<int, vector<int>> M;
    for (int i = 1; i <= n; i++) {
        cin >> V[i].first;
    }
    for (int i = 1; i <= n; i++) {
        cin >> V[i].second;
    }

    for (int i = 1; i <= n; i++) {
        M[V[i].first].push_back(V[i].second);
        M[0].push_back(V[i].second);
    }

    auto work = [&](vector<int> &V) {
        int n = V.size();

        vector<int> x(n);
        for (int i = 0; i < n; i++) {
            x[i] = V[i];
        }
        sort(x.begin(), x.end());
        x.resize(unique(x.begin(), x.end()) - x.begin());
        Fenwick<int> fen(x.size());

        ll ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            int val = V[i];
            int idx = lower_bound(x.begin(), x.end(), val) - x.begin() + 1;
            ans += fen.query(idx - 1);
            fen.add(idx, 1);
        }
        return ans;
    };
    ll ans = work(M[0]);

    for (auto V : M) {
        if (V.first == 0) continue;
        ans -= work(V.second);
    }
    cout << ans << endl;
    return 0;
}
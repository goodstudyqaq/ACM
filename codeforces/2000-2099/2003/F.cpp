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

template <class T>
auto vect(const T& v, int n) { return vector<T>(n, v); }
template <class T, class... D>
auto vect(const T& v, int n, D... m) {
    return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}

template <typename T>
static constexpr T inf = numeric_limits<T>::max() / 2;
mt19937_64 mrand(random_device{}());
long long rnd(long long x) { return mrand() % x; }
int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef pair<int, int> pii;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

template <typename T>
struct BIT {
#define lowbit(x) x & -x
    int n;
    vector<T> a;
    // [1, n]
    BIT(int n) : n(n), a(n + 1) {}
    BIT() {}

    void init(int _n) {
        n = _n;
        a = vector<T>(n + 1);
    }
    void add(int x, T v) {
        while (x <= n) {
            a[x] += v;
            x += lowbit(x);
        }
    }

    // [1, x]
    T query(int x) {
        T res = -1e9;
        while (x) {
            res += a[x];
            x -= lowbit(x);
        }
        return res;
    }

    static int largest_bit(int x) {
        return 31 - __builtin_clz(x);
    }
};

struct Max {
    int v;
    Max(int x = -1E9) : v{x} {}

    Max& operator+=(Max a) {
        v = std::max(v, a.v);
        return *this;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1), b(n + 1), c(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    vector<int> d(n + 1), e(n + 1);

    vector<BIT<Max>> bits(1 << m);

    int ans = -1;
    for (int t = 1; t <= 300; t++) {
        for (int i = 1; i <= n; i++) {
            d[i] = rnd(m);
        }

        for (int i = 1; i <= n; i++) {
            e[i] = d[b[i]];
        }
        // debug(e);

        for (int i = 0; i < (1 << m); i++) {
            bits[i].init(n);
        }

        bits[0].add(1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < (1 << m); j++) {
                int type = e[i];
                if ((j >> type) & 1) continue;
                bits[j + (1 << type)].add(a[i], bits[j].query(a[i]).v + c[i]);
            }
        }
        ans = max(ans, bits[(1 << m) - 1].query(n).v);
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
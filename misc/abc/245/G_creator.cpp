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

int main() {
#ifdef LOCAL
    // freopen("data.in", "w", stdout);
#endif
    int n = rnd(10) + 1;
    int mx = n * (n - 1) / 2;
    int m = rnd(mx) + 1;
    int k = rnd(n) + 1;
    int l = rnd(n) + 1;
    cout << n << ' ' << m << ' ' << k << ' ' << l << endl;

    for (int i = 1; i <= n; i++) {
        cout << rnd(k) + 1 << ' ';
    }
    cout << endl;

    for (int i = 1; i <= l; i++) {
        cout << rnd(n) + 1 << ' ';
    }
    cout << endl;

    for (int i = 1; i <= m; i++) {
        int u = rnd(n) + 1;
        int v;
        do {
            v = rnd(n) + 1;
        } while (v == u);

        int c = rnd(20) + 1;
        cout << u << ' ' << v << ' ' << c << endl;
    }
}

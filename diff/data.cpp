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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, q;
    n = 5;
    q = 5;
    cout << n << ' ' << q << endl;
    for (int i = 0; i < n; i++) {
        int l = rnd(10), r = rnd(10);
        int flagl = rnd(2), flagr = rnd(2);
        l *= (flagl ? -1 : 1);
        r *= (flagr ? -1 : 1);
        if (l > r) swap(l, r);
        int x = rnd(10), y = rnd(10);
        int flagx = rnd(2), flagy = rnd(2);
        cout << l << ' ' << r << ' ' << x * (flagx ? -1 : 1) << ' ' << y * (flagy ? -1 : 1) << endl;
    }
    for (int i = 0; i < q; i++) {
        int flag = rnd(2);
        cout << flag << ' ';
        if (flag == 0) {
            int l = rnd(10), r = rnd(10);
            int flagl = rnd(2), flagr = rnd(2);
            l *= (flagl ? -1 : 1);
            r *= (flagr ? -1 : 1);
            if (l > r) swap(l, r);
            int x = rnd(10), y = rnd(10);
            int flagx = rnd(2), flagy = rnd(2);
            cout << l << ' ' << r << ' ' << x * (flagx ? -1 : 1) << ' ' << y * (flagy ? -1 : 1) << endl;

        } else {
            int p = rnd(10);
            int flagp = rnd(2);
            cout << p * (flagp ? -1 : 1) << endl;
        }
    }
}
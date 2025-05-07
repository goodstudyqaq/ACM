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
    freopen("./data.in", "w", stdout);
#endif
    cout << 1 << endl;
    int n = rnd(10000);
    int k = rnd(1000000) + 1;
    vector<int> v(n);
    cout << n << ' ' << k << endl;
    for (int i = 0; i < n; i++) {
        v[i] = rnd(2);
        cout << v[i];
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        if (v[i] == 0) {
            cout << 0 << ' ';
        } else {
            int flag = rnd(2);
            cout << (flag ? -1 : 1) * rnd(100000) << ' ';
        }
    }
    cout << endl;
}
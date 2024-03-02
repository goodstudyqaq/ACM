#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif
    freopen("./data.in", "w", stdout);

    cout << 1 << endl;
    int n = 200000;
    cout << n << endl;
    for (int i = 1; i <= n / 2; i++) {
        cout << 1 << ' ';
    }

    for (int i = 1; i <= n / 2; i++) {
        cout << 2 << ' ';
    }

    cout << endl;
    for (int i = 1; i <= n; i++) {
        cout << 1 << ' ';
    }
    cout << endl;
    return 0;
}
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

template <typename T>
struct Fenwick {
#define lowbit(x) x & -x
    const int n;
    vector<T> a;
    // [1, n]
    Fenwick(int n) : n(n), a(n + 1) {}
    void add(int x, T v) {
        while (x <= n) {
            a[x] += v;
            x += lowbit(x);
        }
    }

    // [1, x]
    T query(int x) {
        T res = 0;
        while (x) {
            res += a[x];
            x -= lowbit(x);
        }
        return res;
    }
};

const int maxT = 30;
const int N = 3e5 + 5;
const int Q = 3e5 + 5;

bitset<N + Q + 1> guess[maxT + 1];

void init() {
    for (int i = 1; i <= maxT; i++) {
        for (int j = 1; j <= N + Q; j++) {
            if (mrand() % 2) {
                guess[i][j] = 1;
            }
        }
    }
}

map<int, int> M;
int mcnt;
int ID(int x) {
    if (M.count(x) == 0) {
        M[x] = ++mcnt;
    }
    return M[x];
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    init();
    debug("init done");
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);

    vector<Fenwick<int>> fen = vector(maxT + 1, Fenwick<int>(n));

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        int the_id = ID(a[i]);
        for (int j = 1; j <= maxT; j++) {
            if (guess[j][the_id] == 1) {
                fen[j].add(i, 1);
            }
        }
    }

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, x;
            cin >> i >> x;
            int old_id = ID(a[i]);
            int new_id = ID(x);
            a[i] = x;
            for (int j = 1; j <= maxT; j++) {
                if (guess[j][old_id]) {
                    fen[j].add(i, -1);
                }
                if (guess[j][new_id]) {
                    fen[j].add(i, 1);
                }
            }
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            if (k == 1) {
                cout << "YES" << endl;
                continue;
            } else if ((r - l + 1) % k) {
                cout << "NO" << endl;
                continue;
            }
            bool flag = true;
            for (int j = 1; j <= maxT; j++) {
                int cnt = fen[j].query(r) - fen[j].query(l - 1);
                if (cnt % k) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

// #define endl '\n'
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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    vector<vector<int>> V(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        for (int j = 0; j < m; j++) {
            V[i][j] = s[i][j] - '0';
        }
    }
    vector<long long> hash(n);
    for (int i = 0; i < n; i++) {
        hash[i] = mrand();
    }

    map<long long, int> cnt;
    map<long long, pair<int, int>> mp;
    for (int j = 0; j < m; j++) {
        long long h = 0;
        for (int i = 0; i < n; i++) {
            if (V[i][j]) {
                h ^= hash[i];
            }
        }

        for (int i = 0; i < n; i++) {
            h ^= hash[i];
            cnt[h]++;
            mp[h] = {i, j};
            h ^= hash[i];
        }
    }

    long long state = cnt.begin()->first;
    for (auto it : cnt) {
        if (it.second > cnt[state]) {
            state = it.first;
        }
    }

    auto [x, y] = mp[state];
    vector<int> way(n);

    for (int i = 0; i < n; i++) {
        if (V[i][y] == 1) {
            way[i] = 1;
        }
    }
    way[x] ^= 1;

    cout << cnt[state] << endl;
    for (int i = 0; i < n; i++) {
        cout << way[i];
    }
    cout << endl;
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
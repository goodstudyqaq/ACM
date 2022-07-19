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

#include <functional>
// from boost (functional/hash):
// see http://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html template
template <typename T>
inline void hash_combine(std::size_t& seed, const T& val) {
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
// auxiliary generic functions to create a hash value using a seed
template <typename T>
inline void hash_val(std::size_t& seed, const T& val) {
    hash_combine(seed, val);
}
template <typename T, typename... Types>
inline void hash_val(std::size_t& seed, const T& val, const Types&... args) {
    hash_combine(seed, val);
    hash_val(seed, args...);
}

template <typename... Types>
inline std::size_t hash_val(const Types&... args) {
    std::size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        return hash_val(p.first, p.second);
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int s, t, m;
    cin >> s >> t >> m;
    vector<vector<int>> V(s + t + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    vector<vector<int>> vis;
    vis.resize(t + 1, vector<int>(t + 1, 0));

    for (int i = 1; i <= s; i++) {
        int sz = V[i].size();
        for (int j = 0; j < sz; j++) {
            for (int k = j + 1; k < sz; k++) {
                int u = V[i][j], v = V[i][k];

                u -= s, v -= s;

                if (u > v) {
                    swap(u, v);
                }
                if (vis[u][v] != 0) {
                    cout << i << ' ' << vis[u][v] << ' ' << u + s << ' ' << v + s << endl;
                    return 0;
                }
                vis[u][v] = i;
            }
        }
    }
    cout << -1 << endl;
}
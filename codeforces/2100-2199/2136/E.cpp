#include <bits/stdc++.h>

#include "graph/graph-template.hpp"
#include "graph/others/low-link.hpp"
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

template <typename T = int>
struct BiConnectedComponents : LowLink<T> {
   public:
    using LowLink<T>::LowLink;
    using LowLink<T>::g;
    using LowLink<T>::dfn;
    using LowLink<T>::low;

    vector<vector<Edge<T>>> bc;

    void build() override {
        LowLink<T>::build();
        vis.assign(g.size(), 0);
        for (int i = 0; i < g.size(); i++) {
            if (vis[i] == 0) {
                dfs(i, -1);
            }
        }
    }

    explicit BiConnectedComponents(const Graph<T> &g) : Graph<T>(g) {}

   private:
    vector<int> vis;
    vector<Edge<T>> tmp;

    void dfs(int u, int pre) {
        vis[u] = 1;
        bool beet = false;  // beet 检查是否有跟父亲的重边
        for (auto &v : g[u]) {
            if (v == pre && exchange(beet, true) == false) continue;
            if (!vis[v] || dfn[v] < dfn[u]) {  // dfn[v] < dfn[u] 感觉只有跟父亲有重边时会加进来
                tmp.emplace_back(v);
            }

            if (!vis[v]) {
                dfs(v, u);
                if (low[v] >= dfn[u]) {
                    bc.emplace_back();
                    while (true) {
                        auto e = tmp.back();
                        bc.back().emplace_back(e);
                        tmp.pop_back();
                        if (v.idx == e.idx) break;
                    }
                }
            }
        }
    }
};

void solve() {
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
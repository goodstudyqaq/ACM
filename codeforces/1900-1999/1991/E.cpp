#include <bits/stdc++.h>

#include "./graph/bipartite-graph/bipartite-graph.hpp"

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// struct fast_ios {
//     fast_ios() {
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(10);
//     };
// } fast_ios_;

void solve() {
    int n, m;
    cin >> n >> m;
    BipartiteGraph<> bg(n);
    bg.read(m);

    // check 是否是二分图
    if (bg.bipartite_graph_coloring()) {
        // Bob 必胜
        cout << "Bob" << endl;
        vector<vector<int>> color_index(2);
        for (int i = 0; i < n; i++) {
            color_index[bg.color(i)].push_back(i);
        }

        auto bob_out = [&]() {
            int a, b;
            cin >> a >> b;
            a--, b--;
            if (a > b) swap(a, b);
            int i, c;

            if (b == 1) {
                if (color_index[0].size()) {
                    i = color_index[0].back() + 1;
                    c = 1;
                    color_index[0].pop_back();
                } else {
                    i = color_index[1].back() + 1;
                    c = 2;
                    color_index[1].pop_back();
                }
            } else {
                if (color_index[a].size()) {
                    i = color_index[a].back() + 1;
                    c = a + 1;
                    color_index[a].pop_back();
                } else {
                    int f = a ^ 1;
                    // i = f + 1;
                    i = color_index[f].back() + 1;
                    c = 3;
                    color_index[f].pop_back();
                }
            }
            cout << i << ' ' << c << endl;
        };

        for (int i = 0; i < n; i++) {
            bob_out();
        }

    } else {
        // Alice 必胜
        cout << "Alice" << endl;
        auto alice_out = [&](int a, int b) {
            cout << a << ' ' << b << endl;
            int i, c;
            cin >> i >> c;
            return pair<int, int>{i, c};
        };
        for (int i = 0; i < n; i++) {
            alice_out(1, 2);
        }
    }
}



int main() {
// #ifdef LOCAL
//     freopen("./data.in", "r", stdin);
// #endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
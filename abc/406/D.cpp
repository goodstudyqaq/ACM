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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int h, w, n;
    cin >> h >> w >> n;

    vector<set<int>> S(h + 1), S2(w + 1);

    vector<pair<int, int>> p(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        p[i] = {x, y};
        S[x].insert(i);
        S2[y].insert(i);
    }

    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            cin >> x;
            cout << S[x].size() << '\n';

            for (auto idx : S[x]) {
                int y = p[idx].second;
                S2[y].erase(idx);
            }
            S[x].clear();
        } else {
            int y;
            cin >> y;
            cout << S2[y].size() << '\n';
            for (auto idx : S2[y]) {
                int x = p[idx].first;
                S[x].erase(idx);
            }
            S2[y].clear();
        }
    }
    return 0;
}
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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    map<int, vector<int>> M;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        M[v].push_back(i);
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;
        if (M[x].size() == 0) {
            cout << 0 << endl;
            continue;
        }
        int idx1 = lower_bound(M[x].begin(), M[x].end(), l) - M[x].begin();
        int idx2 = upper_bound(M[x].begin(), M[x].end(), r) - M[x].begin();
        cout << idx2 - idx1 << endl;
    }
    return 0;
}
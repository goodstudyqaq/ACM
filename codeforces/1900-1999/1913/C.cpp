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

    int m;
    cin >> m;
    vector<int> num(30);
    while (m--) {
        int t, v;
        cin >> t >> v;
        if (t == 1) {
            num[v]++;
        } else {
            for (int i = 29; i >= 0; i--) {
                int val = 1 << i;
                int need = min(num[i], v / val);
                v -= need * val;
            }
            if (v == 0) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
}
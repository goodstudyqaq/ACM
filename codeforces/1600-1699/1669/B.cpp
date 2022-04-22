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
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        map<int, int> m;
        for (int i = 1; i <= n; i++) {
            int a;
            cin >> a;
            m[a]++;
        }
        bool flag = false;
        for (auto it : m) {
            if (it.second >= 3) {
                cout << it.first << endl;
                flag = true;
                break;
            }
        }
        if (!flag) {
            cout << -1 << endl;
        }
    }
    return 0;
}
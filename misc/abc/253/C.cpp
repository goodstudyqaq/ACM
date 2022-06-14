
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

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

    int Q;
    cin >> Q;
    map<int, int> M;
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            cin >> x;
            M[x]++;
        } else if (t == 2) {
            int x, c;
            cin >> x >> c;
            int m = min(M[x], c);
            M[x] -= m;
            if (M[x] == 0) M.erase(x);
        } else {
            auto it = M.rbegin();
            auto it2 = M.begin();
            cout << it->first - it2->first << endl;
        }
    }
    return 0;
}
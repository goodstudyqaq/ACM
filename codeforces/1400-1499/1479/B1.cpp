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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> pos(n + 1);
    for (int i = 0; i <= n; i++) {
        pos[i] = n + 1;
    }
    vector<int> nxt(n + 1);
    for (int i = n; i >= 0; i--) {
        nxt[i] = pos[a[i]];
        pos[a[i]] = i;
    }

    int x = 0, y = 0;
    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == a[x]) {
            res += (a[i] != a[y]);
            y = i;
        } else if (a[i] == a[y]) {
            res += (a[i] != a[x]);
            x = i;
        } else {
            int tmp1 = nxt[x], tmp2 = nxt[y];
            if (tmp1 < tmp2) {
                res += 1;
                x = i;
            } else {
                res += 1;
                y = i;
            }
        }
    }
    cout << res << endl;
    return 0;
}
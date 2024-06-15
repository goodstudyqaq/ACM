#include <bits/stdc++.h>

#include <set>

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

void solve() {
    int m, x;
    cin >> m >> x;
    vector<int> c(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> c[i];
    }
    multiset<int> S;
    int now = x;
    for (int i = 2; i <= m; i++) {
        int val = c[i];
        if (now >= val) {
            now -= val;
            S.insert(val);
        } else {
            if (S.size()) {
                int tmp = *S.rbegin();
                if (tmp > val) {
                    now += tmp - val;
                    S.erase(prev(S.end()));
                    S.insert(val);
                }
            }
        }
        now += x;
    }
    cout << S.size() << endl;
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
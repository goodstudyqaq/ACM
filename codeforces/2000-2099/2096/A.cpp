#include <bits/stdc++.h>

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

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> ans(n);
    ans[0] = 0;

    set<int> S;
    S.insert(0);

    int mi = 0;
    for (int i = 1; i < n; i++) {
        char it = s[i - 1];
        int val = ans[i - 1];
        if (it == '>') {
            int go = val + 1;
            while (S.count(go)) go++;
            ans[i] = go;
            S.insert(go);
        } else {
            int go = val - 1;
            while (S.count(go)) go--;
            ans[i] = go;
            S.insert(go);
        }
        mi = min(mi, ans[i]);
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] + abs(mi) + 1 << ' ';
    }
    cout << '\n';
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
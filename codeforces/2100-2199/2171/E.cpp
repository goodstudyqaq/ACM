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
    vector<int> prm = {2, 3};
    vector<int> invalid;

    vector<int> vis(n + 1, 1);
    for (int i = 0; i < prm.size(); i++) {
        for (int j = prm[i]; j <= n; j += prm[i]) {
            vis[j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (vis[i]) {
            invalid.push_back(i);
        }
    }
    debug(invalid);

    for (int i = 0; i < prm.size(); i++) {
        vector<int> have;
        for (int j = 1; j <= n; j++) {
            if (vis[j] == 0 && (j % prm[i] == 0)) {
                vis[j] = 1;
                have.push_back(j);
            }
        }

        int sz1 = have.size();
        int sz2 = invalid.size();

        int ct = min(sz1 / 2, sz2);

        while (ct) {
            cout << invalid.back() << ' ' << have.back() << ' ' << have[have.size() - 2] << ' ';
            invalid.pop_back();
            have.pop_back();
            have.pop_back();
            ct--;
        }
        for (auto it : have) {
            vis[it] = 0;
        }
    }
    for (auto it : invalid) {
        vis[it] = 0;
    }

    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            cout << i << ' ';
        }
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
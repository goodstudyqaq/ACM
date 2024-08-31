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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> V;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        int l = (i + n - 1) % n;
        if (a[i] == 0 || a[l] == 0) continue;
        V.push_back(i);
    }

    while (V.size()) {
        vector<int> V2;
        debug(a);
        int itor = 0;
        bool have_zero = (V[0] == 0);
        if (have_zero) itor++;
        for (; itor != V.size(); itor++) {
            auto it = V[itor];
            int l = (it + n - 1) % n;
            int r = (it + 1) % n;
            int val = max(0, a[it] - a[l]);
            if (a[it] == val) {
                continue;
            } else {
                int l2 = (l + n - 1) % n;
                if (a[l2] == 0 && a[r] == 0) {
                    a[it] = 0;
                } else {
                    V2.push_back(it);
                    a[it] = val;
                }
            }
        }
        if (have_zero) {
            int l = n - 1;
            int val = max(0, a[0] - a[l]);
            if (a[0] == val) {
            } else {
                V2.push_back(0);
                a[0] = val;
            }
        }
        V = V2;
    }
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (a[i]) {
            ans.push_back(i + 1);
        }
    }
    cout << ans.size() << endl;
    for (auto it : ans) {
        cout << it << ' ';
    }
    cout << endl;
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
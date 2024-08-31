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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int f = a[0] % 2;
    for (int i = 1; i < n; i++) {
        if (a[i] % 2 != f) {
            cout << -1 << endl;
            return;
        }
    }

    int use = 40;
    vector<int> ans;
    while (use--) {
        sort(a.begin(), a.end());
        a.resize(unique(a.begin(), a.end()) - a.begin());
        bool flag = true;
        n = a.size();
        for (int i = 0; i < n; i++) {
            if (a[i] != 0) {
                flag = false;
                break;
            }
        }
        if (flag) {
            break;
        }

        int l = a[0], r = a.back();
        int m = l + r >> 1;
        ans.push_back(m);

        for (int i = 0; i < n; i++) {
            a[i] = abs(a[i] - m);
        }
    }
    bool flag = true;
    for (int i = 0; i < n; i++) {
        if (a[i] != 0) {
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << ans.size() << endl;
        for (auto it : ans) {
            cout << it << ' ';
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }
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
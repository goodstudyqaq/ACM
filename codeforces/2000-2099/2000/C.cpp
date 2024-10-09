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
    vector<int> a(n), pre(n, -1);
    map<int, int> idx;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (idx.count(a[i])) {
            pre[i] = idx[a[i]];
        }
        idx[a[i]] = i;
    }

    int m;
    cin >> m;
    while (m--) {
        string s;
        cin >> s;
        if (s.size() != n) {
            cout << "NO" << endl;
            continue;
        }

        vector<int> pre2(n, -1);
        map<int, int> idx;
        for (int i = 0; i < n; i++) {
            if (idx.count(s[i])) {
                pre2[i] = idx[s[i]];
            }
            idx[s[i]] = i;
        }
        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (pre[i] != pre2[i]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
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
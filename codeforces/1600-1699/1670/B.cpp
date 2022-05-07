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

void solve() {
    int n;
    string s;
    cin >> n >> s;
    int t;
    cin >> t;
    vector<bool> vis(26, 0);
    for (int i = 0; i < t; i++) {
        char c;
        cin >> c;
        vis[c - 'a'] = 1;
    }
    int ans = 0;
    vector<int> V;
    for (int i = 0; i < n; i++) {
        if (vis[s[i] - 'a']) {
            V.push_back(i);
        }
    }
    if (V.size() == 0) {
        cout << 0 << endl;
        return;
    }

    int bef_val = 0;
    for (int i = 0; i < V.size(); i++) {
        int idx = V[i];
        if (idx == 0) continue;
        if (i == 0) {
            bef_val = idx;
        } else {
            int bef = V[i - 1];
            int tmp = idx - bef;
            if (tmp >= bef_val) {
                bef_val = tmp;
            }
        }
    }
    cout << bef_val << endl;
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
}
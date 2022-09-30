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
    string s;
    cin >> s;
    int n = s.size();
    vector<int> nxt(n);

    for (int i = n - 1; i >= 0; i--) {
        nxt[i] = i;
        if (i != n - 1) {
            if (s[i] > s[nxt[i + 1]]) {
                nxt[i] = nxt[i + 1];
            }
        }
    }
    map<int, int> M;
    vector<int> ans;
    int now = 0;
    debug("zzz");
    while (now < n) {
        int idx = nxt[now];
        int val = s[idx] - '0';

        // 后面最小的是 val
        int go = now;
        while (go < n && go < idx) {
            M[min(9, s[go] - '0' + 1)]++;
            go++;
        }
        for (auto it : M) {
            if (it.first > val) break;
            for (int j = 0; j < it.second; j++) {
                ans.push_back(it.first);
            }
            M[it.first] = 0;
        }
        ans.push_back(val);
        now = idx + 1;
    }
    for (auto it : M) {
        for (int j = 0; j < it.second; j++) {
            ans.push_back(it.first);
        }
    }

    for (auto it : ans) {
        cout << it;
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
}
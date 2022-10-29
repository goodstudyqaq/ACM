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
    string s;
    cin >> n >> s;

    int cnt = 0;
    for (int i = 0; i < 2 * n; i++) {
        cnt += s[i] - '0';
    }
    if (cnt % 2) {
        cout << -1 << endl;
        return;
    }

    vector<int> V;
    for (int i = 0; i < n; i++) {
        if (s[i * 2] != s[i * 2 + 1]) {
            V.push_back(i * 2);
        }
    }
    int sz = V.size();
    vector<int> res;
    for (int i = 0; i < sz; i++) {
        int num = (i % 2);
        if (s[V[i]] - '0' == num) {
            res.push_back(V[i]);
        } else {
            res.push_back(V[i] + 1);
        }
    }

    cout << res.size() << ' ';
    for (auto it : res) {
        cout << it + 1 << ' ';
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << 2 * i + 1 << ' ';
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
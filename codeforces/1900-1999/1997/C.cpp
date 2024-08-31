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
    vector<int> stk;
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            if (stk.size()) {
                res += i - stk.back();
                stk.pop_back();
            } else {
                stk.push_back(i);
            }
        } else {
            if (s[i] == '(') {
                stk.push_back(i);
            } else {
                res += i - stk.back();
                stk.pop_back();
            }
        }
    }
    cout << res << endl;
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
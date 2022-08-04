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

vector<int> ans;
void init() {
    ans.resize(46, -1);
    function<void(int, int, int)> dfs = [&](int d, int val, int sum) {
        if (d == 10) {
            if (ans[sum] == -1)
                ans[sum] = val;
            else
                ans[sum] = min(ans[sum], val);
            return;
        }
        dfs(d + 1, val * 10 + d, sum + d);
        dfs(d + 1, val, sum);
    };
    dfs(1, 0, 0);
}

void solve() {
    int s;
    cin >> s;
    cout << ans[s] << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    init();
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}
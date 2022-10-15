
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
vector<int> vis;
vector<int> v;
int cnt;
int n, k;
// 当前下标为 d, 前面是否是相等的， 前缀数字是 num
bool dfs(int d, bool equal, int num) {
    if (d == -1) {
        cout << num << endl;
        return true;
    }
    int BEGIN = equal ? v[d] : 0;

    for (int i = BEGIN; i <= 9; i++) {
        vis[i]++;
        if (vis[i] == 1) {
            cnt++;
        }
        if (cnt <= k && dfs(d - 1, equal && (i == BEGIN), num * 10 + i)) {
            return true;
        }
        vis[i]--;
        if (vis[i] == 0) {
            cnt--;
        }
    }
    return false;
}

void solve() {
    cin >> n >> k;
    int x = n;
    vis = vector<int>(10, 0);
    cnt = 0;
    v.clear();
    while (x) {
        v.push_back(x % 10);
        x /= 10;
    }
    int m = v.size();
    if (dfs(m - 1, 1, 0))
        return;
    else {
        debug("error", n, k);
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
}
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

const int maxn = 2e5 + 5;
int sum[maxn];

#define lowbit(x) x & -x
void add(int x, int val) {
    while (x < maxn) {
        sum[x] += val;
        x += lowbit(x);
    }
}

int query(int x) {
    int res = 0;
    while (x) {
        res += sum[x];
        x -= lowbit(x);
    }
    return res;
}

void solve() {
    ll ans = 0;
    int n;
    cin >> n;
    for (int i = 0; i <= n; i++) {
        sum[i] = 0;
    }
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        int v1 = query(n);
        int v3 = query(a[i] - 1);
        ans += v1 - v3;
        add(a[i], 1);
    }
    cout << ans << endl;
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
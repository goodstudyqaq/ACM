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
    vector<int> cnt(n + 1);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        cnt[a]++;
    }

    int mex = 0;
    while (cnt[mex] > 0) mex++;

    vector<int> ans(n + 2);

    int sum = 0;

    for (int i = 0; i <= mex; i++) {
        int l = cnt[i];
        int r = n - i;
        ans[l]++;
        ans[r + 1]--;
    }

    cout << ans[0] << ' ';
    for (int i = 1; i <= n; i++) {
        ans[i] += ans[i - 1];
        cout << ans[i] << ' ';
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
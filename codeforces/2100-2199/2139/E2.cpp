#include <bits/stdc++.h>

#include <istream>

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

const int maxn = 2e5 + 1;
bitset<maxn> dp;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> V(n);
    vector<int> dep(n);
    dep[0] = 1;
    vector<int> cnt(n + 1);
    cnt[1] = 1;

    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        dep[i] = dep[p] + 1;
        cnt[dep[i]]++;
        V[p].push_back(i);
    }

    int mi = n;
    for (int i = 0; i < n; i++) {
        if (V[i].size() == 0) {
            mi = min(mi, dep[i]);
        }
    }

    vector<int> cnt2(n + 1);
    int tot = 0;

    for (int i = 1; i <= mi; i++) {
        tot += cnt[i];
        cnt2[cnt[i]]++;
    }

    dp.reset();
    dp[0] = 1;
    /*

    */
    for (int i = 1; i <= n; i++) {
        if (cnt2[i] == 0) continue;
        // i 有 cnt2[i] 个
        for (int j = 1; j <= cnt2[i]; j *= 2) {
            dp |= (dp << (i * j));
            cnt2[i] -= j;
        }
        dp |= (dp << (i * cnt2[i]));
    }

    for (int i = 0; i <= k; i++) {
        int other = tot - i;
        if (dp[i] && other <= n - k) {
            cout << mi << '\n';
            return;
        }
    }
    cout << mi - 1 << '\n';
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
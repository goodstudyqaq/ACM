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
    long long n, c;
    cin >> n >> c;
    vector<vector<int>> v(2);
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;
        v[s % 2].push_back(s);
    }

    long long ans = 1LL * (c + 1 + 1) * (c + 1) / 2;
    for (int i = 0; i < 2; i++) {
        for (auto it : v[i]) {
            // y - x = it
            // x = [0, n - it]
            ans -= c - it + 1;

            // y + x = it
            // x = [0, it / 2]
            ans -= it / 2 + 1;
            
            // 多算了一个
            ans++;
        }
    }
    int sz = v[0].size();
    ans += 1LL * sz * (sz - 1) / 2;
    sz = v[1].size();
    ans += 1LL * sz * (sz - 1) / 2;
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
    return 0;
}
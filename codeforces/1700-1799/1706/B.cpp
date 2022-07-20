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
    cin >> n;
    vector<int> a(n + 1);
    vector<vector<int>> cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]].push_back(i);
    }

    for (int i = 1; i <= n; i++) {
        bool flag[2] = {false, false};

        int sz = cnt[i].size();

        int ans = 0;
        for (int j = 0; j < sz; j++) {
            int val = cnt[i][j];
            if (flag[val % 2]) continue;
            flag[val % 2] = true;
            int last = val;
            int tmp_ans = 1;
            for (int k = j + 1; k < sz; k++) {
                int val2 = cnt[i][k];
                if ((val2 - last) % 2) {
                    tmp_ans++;
                    last = val2;
                }
            }
            ans = max(ans, tmp_ans);
        }
        cout << ans << ' ';
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
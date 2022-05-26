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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, int> M;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        M[a[i]]++;
    }
    int sz = M.size();
    int ans = 0;
    int left_cnt = 0, right_cnt = 0;

    int now = 0;
    for (auto it : M) {
        now++;
        // if (now == sz) break;
        if (it.second == 1) {
            if (left_cnt <= right_cnt) {
                left_cnt++;
            } else {
                right_cnt++;
            }
        } else {
            left_cnt++;
            right_cnt++;
        }
    }

    ans = max(left_cnt, right_cnt);
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
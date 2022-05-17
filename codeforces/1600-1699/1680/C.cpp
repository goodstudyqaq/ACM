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
    string s;
    cin >> s;

    int n = s.size();
    int l = 0;
    while (l < n && s[l] == '0') l++;
    if (l == n) {
        cout << 0 << endl;
        return;
    }

    vector sum = vector(n + 1, 0);
    vector<int> IDX;
    for (int i = n - 1; i >= 0; i--) {
        sum[i] = sum[i + 1];
        if (s[i] == '1') {
            sum[i]++;
            IDX.push_back(i);
        }
    }

    int r = n - 1;
    while (s[r] == '0') r--;

    int left_cnt = 0;

    auto check = [&](int l, int r, int val) {
        int have = sum[r + 1] + val;
        int idx = IDX[have] + 1;

        int one_cnt = sum[l] - sum[idx];
        int zero_cnt = idx - l - one_cnt;
        if (zero_cnt <= val + left_cnt) return true;
        return false;
    };

    auto work = [&](int l, int r) {
        int L = 0, R = sum[l] - sum[r + 1];
        int ans = -1;
        while (L <= R) {
            int mid = L + R >> 1;
            if (check(l, r, mid)) {
                ans = mid;
                R = mid - 1;
            } else {
                L = mid + 1;
            }
        }
        return ans;
    };

    int ans = work(l, r);

    for (int i = l; i <= r; i++) {
        if (s[i] == '1') left_cnt++;
        ans = min(ans, work(i + 1, r) + left_cnt);
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
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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    auto work = [&]() {
        vector<int> ans(n);
        map<int, int> M;
        for (int i = 0; i < n; i++) {
            M[a[i]]++;
        }
        int mex = 0;
        while (M.count(mex)) {
            mex++;
        }

        for (int i = 0; i < n; i++) {
            if (a[i] > mex) {
                ans[i] = mex;
            } else {
                int cnt = M[a[i]] - 1;
                if (cnt == 0) {
                    ans[i] = a[i];
                } else {
                    ans[i] = mex;
                }
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    };

    a = work();
    k--;
    if (k == 0) {
        long long res = 0;
        for (int i = 0; i < n; i++) {
            res += a[i];
        }
        cout << res << '\n';
        return;
    }
    a = work();
    k--;
    if (k % 2 == 0) {
        long long res = 0;
        for (int i = 0; i < n; i++) {
            res += a[i];
        }
        cout << res << '\n';
        return;
    }
    a = work();
    long long res = 0;
    for (int i = 0; i < n; i++) {
        res += a[i];
    }
    cout << res << '\n';
    return;
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
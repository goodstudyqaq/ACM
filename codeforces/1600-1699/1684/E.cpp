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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    map<int, int> M;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        M[a[i]]++;
    }
    multiset<int> S1, S2;
    for (auto it : M) {
        S2.insert(it.second);
    }
    int hole = 0;
    int sum = 0;
    int ans = 1e9;
    for (int mex = 0; mex <= n; mex++) {
        while (S2.size() && sum + (*S2.begin()) <= k) {
            int val = *S2.begin();
            sum += val;
            S1.insert(val);
            S2.erase(S2.begin());
        }

        if (hole <= k) {
            int sz = S2.size();
            ans = min(ans, sz);
        }

        if (M.count(mex)) {
            int cnt = M[mex];
            if (S1.count(cnt)) {
                sum -= cnt;
                S1.erase(S1.find(cnt));
            } else {
                S2.erase(S2.find(cnt));
            }
        } else {
            hole++;
        }
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
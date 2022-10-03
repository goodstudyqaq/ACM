#define PROBLEM "https://codeforces.com/contest/1738/problem/A"
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
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> v(2);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        v[a[i]].push_back(b[i]);
    }
    sort(v[0].rbegin(), v[0].rend());
    sort(v[1].rbegin(), v[1].rend());

    auto work = [&](vector<int> &v1, vector<int> &v2) -> ll {
        // debug(v1, v2);
        if (v1.size() == 0) {
            return accumulate(v2.begin(), v2.end(), 0LL);
        }
        int v1_sz = v1.size();
        int v2_sz = v2.size();

        ll ans = v1[v1_sz - 1];
        int cnt = min(v1_sz - 1, v2_sz);

        for (int i = 0; i < cnt; i++) {
            ans += 2LL * v1[i];
            ans += 2LL * v2[i];
        }

        if (cnt < v2.size()) {
            ans += 2LL * v2[cnt];
        }

        // debug(ans);

        int now_v1 = cnt;
        while (now_v1 < v1_sz - 1) {
            ans += v1[now_v1];
            now_v1++;
        }

        int now_v2 = cnt + 1;
        while (now_v2 < v2_sz) {
            ans += v2[now_v2];
            now_v2++;
        }
        return ans;
    };

    ll ans = work(v[0], v[1]);
    ans = max(ans, work(v[1], v[0]));
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
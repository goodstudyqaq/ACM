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
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    vector<int> ans;
    long long res = 0;
    multiset<int> S;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] == x) {
            ans.push_back(x);
            res += x;
        } else {
            S.insert(a[i]);
        }
    }
    long long now = 0;

    while (S.size()) {
        auto mx = *S.rbegin();
        while (now + mx < x && S.size() > 1) {
            auto it = *S.begin();
            now += it;
            ans.push_back(it);
            S.erase(S.begin());
        }
        ans.push_back(mx);
        S.erase(S.find(mx));
        if (now + mx >= x) {
            res += mx;
            now = (now + mx) % x;
        }
    }
    cout << res << '\n';
    for (auto it : ans) {
        cout << it << ' ';
    }
    cout << '\n';
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
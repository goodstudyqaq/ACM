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
    vector<int> s(n), t(n);
    map<int, int> S, T;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        S[s[i] % k]++;
    }
    for (int i = 0; i < n; i++) {
        cin >> t[i];
        T[t[i] % k]++;
    }

    for (auto it : S) {
        int cnt1 = it.second;
        int v1 = it.first;
        int v2 = k - v1;

        if (v1 != 0 && S.count(v2)) {
            cnt1 += S[v2];
        }

        int cnt2 = 0;
        if (T.count(v1)) {
            cnt2 += T[v1];
        }
        if (v1 != 0 && T.count(v2)) {
            cnt2 += T[v2];
        }
        if (cnt1 != cnt2) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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
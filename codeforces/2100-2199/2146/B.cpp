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
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> S(n);
    set<int> all;
    vector<int> cnt(m + 1);
    for (int i = 0; i < n; i++) {
        int l;
        cin >> l;
        for (int j = 0; j < l; j++) {
            int a;
            cin >> a;
            all.insert(a);
            S[i].push_back(a);
            cnt[a]++;
        }
    }

    if (all.size() != m) {
        cout << "NO\n";
        return;
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        int sz = S[i].size();
        bool ok = true;
        for (int j = 0; j < sz; j++) {
            if (cnt[S[i][j]] == 1) {
                ok = false;
                break;
            }
        }
        if (ok) {
            res++;
        }
    }
    if (res >= 2) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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
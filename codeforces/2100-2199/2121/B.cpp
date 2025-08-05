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
    string s;
    int n;
    cin >> n >> s;

    set<char> S;
    S.insert(s[0]);
    for (int i = 1; i < n - 1; i++) {
        if (S.count(s[i])) {
            cout << "Yes\n";
            return;
        }
        S.insert(s[i]);
    }

    S.clear();
    S.insert(s[n - 1]);
    for (int i = n - 2; i > 0; i--) {
        if (S.count(s[i])) {
            cout << "Yes\n";
            return;
        }
        S.insert(s[i]);
    }
    cout << "No\n";
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
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
    cin >> s;
    vector<int> cnt(26);
    for (int i = 0; i < s.size(); i++) {
        cnt[s[i] - 'A']++;
    }

    for (int i = 0; i < cnt['T' - 'A']; i++) {
        cout << 'T';
    }
    cnt['T' - 'A'] = 0;

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < cnt[i]; j++) {
            cout << char('A' + i);
        }
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
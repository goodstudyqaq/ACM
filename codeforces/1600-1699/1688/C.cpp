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
    vector<string> s(n * 2 + 1);
    vector<int> num(26);
    for (int i = 1; i <= n * 2; i++) {
        cin >> s[i];
        int m = s[i].size();
        for (int j = 0; j < m; j++) {
            num[s[i][j] - 'a']++;
        }
    }

    string s2;
    cin >> s2;
    for (int i = 0; i < s2.size(); i++) {
        num[s2[i] - 'a']--;
    }

    for (int i = 0; i < 26; i++) {
        if (num[i] % 2) {
            cout << char('a' + i) << endl;
            return;
        }
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
}
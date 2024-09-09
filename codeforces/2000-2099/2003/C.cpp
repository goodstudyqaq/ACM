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
    int n;
    string s;
    cin >> n >> s;
    vector<int> cnt(26);
    int mx_idx = 0;
    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (cnt[mx_idx] < cnt[i]) {
            mx_idx = i;
        }
    }

    vector<string> v(cnt[mx_idx]);
    int c = cnt[mx_idx];

    for (int i = 0; i < c; i++) {
        v[i].push_back(mx_idx + 'a');
    }

    cnt[mx_idx] = 0;

    int now = 0;
    for (int i = 0; i < 26; i++) {
        while (cnt[i] > 0) {
            v[now].push_back(i + 'a');
            now++;
            now %= c;
            cnt[i]--;
        }
    }

    for (int i = 0; i < c; i++) {
        cout << v[i];
    }
    cout << endl;
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
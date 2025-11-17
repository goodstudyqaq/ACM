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
    int n = s.size();

    if (n == 1) {
        cout << 1 << '\n';
        return;
    }

    int left = 0;
    while (left < n && s[left] == '<') left++;
    int go = left;

    while (go < n && s[go] == '*') go++;

    int right = go;

    while (right < n && s[right] == '>') right++;

    if (go - left > 1) {
        cout << -1 << '\n';
    } else if (right == n) {
        int left_num = left;
        int right_num = n - go;
        int mid = go - left;
        cout << max(left_num, right_num) + mid << '\n';
    } else {
        cout << -1 << '\n';
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
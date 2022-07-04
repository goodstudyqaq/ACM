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
    string s;
    cin >> n >> s;
    int mx_idx = 0;
    int mx_val = -2;
    int first_idx = n * 2, last_idx = -1;

    int sum = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            sum++;
        } else {
            sum--;
        }
        if (sum < 0) {
            first_idx = min(first_idx, i);
            last_idx = max(last_idx, i);
        }
        if (mx_val < sum) {
            mx_val = sum;
            mx_idx = i;
        }
    }

    if (last_idx == -1) {
        cout << 0 << endl;
        return;
    }

    auto get_idx = [&](int l, int r) {
        int mx_idx = l, mx_val = -2;
        int now = 0;
        for (int i = l; i <= r; i++) {
            if (s[i] == '(')
                now++;
            else
                now--;
            if (mx_val < now) {
                mx_val = now;
                mx_idx = i;
            }
        }
        return mx_idx;
    };

    auto check = [&](string s) {
        int now = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(')
                now++;
            else
                now--;
            if (now < 0) return false;
        }
        return true;
    };

    int L = (first_idx == 0 ? 0 : get_idx(0, first_idx) + 1);
    int R = get_idx(last_idx, n * 2 - 1);
    debug(first_idx, last_idx);
    debug(L, R);

    string tmp = s.substr(L, R - L + 1);
    reverse(tmp.begin(), tmp.end());

    string s2 = s.substr(0, L) + tmp + s.substr(R + 1, n * 2 - (R + 1));
    if (check(s2)) {
        cout << 1 << endl;
        cout << L + 1 << ' ' << R + 1 << endl;
    } else {
        cout << 2 << endl;
        cout << 1 << ' ' << mx_idx + 1 << endl;
        cout << mx_idx + 2 << ' ' << n * 2 << endl;
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
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
    cin >> n;
    string s, t;
    cin >> s >> t;

    if (s == t) {
        cout << 0 << '\n';
        return;
    }

    vector<int> sb(n), tb(n);
    for (int i = 0; i < n; i++) {
        sb[i] = s[i] - '0';
        tb[i] = t[i] - '0';
    }

    auto check1 = [&](vector<int>& s) {
        for (int i = 1; i < n; i++) {
            if (s[i] == s[i - 1]) return false;
        }
        return true;
    };

    typedef array<int, 2> a2;
    auto change = [&](vector<int>& sb, int l, int r) {
        for (int i = l; i <= r; i++) {
            sb[i] ^= 1;
        }
    };

    auto work1 = [&](vector<int>& s) {
        debug(s);
        vector<a2> op;
        int i = 0;
        while (s[i] != s[i + 1]) i++;

        // s[i] = s[i + 1]

        int l = i;
        int r = i;
        while (r < n && s[r] == s[i]) r++;
        r--;
        // [l, r]
        debug(l, r);

        int val = s[i];
        while (l != 0 || r != n - 1) {
            int gol = l - 1;

            while (gol >= 0 && s[gol] != val) gol--;
            int gor = r + 1;
            while (gor < n && s[gor] != val) gor++;
            op.push_back({l, r});
            debug(l, r, gol, gor, s);

            l = gol + 1;
            r = gor - 1;
            val ^= 1;
        }

        debug(val);
        if (val == 1) {
            op.push_back({0, n - 1});
        }
        debug(op);
        return op;
    };

    // 先把 s 变成 0000

    bool flag = false;
    if (check1(sb)) {
        flag = true;
        change(sb, 0, 2);
    }
    auto op1 = work1(sb);
    if (flag) {
        op1.insert(op1.begin(), {0, 2});
    }
    debug(op1);

    flag = false;
    if (check1(tb)) {
        flag = true;
        change(tb, 0, 2);
    }
    auto op2 = work1(tb);
    if (flag) {
        op2.insert(op2.begin(), {0, 2});
    }

    reverse(op2.begin(), op2.end());

    cout << op1.size() + op2.size() << '\n';
    for (int i = 0; i < op1.size(); i++) {
        cout << op1[i][0] + 1 << ' ' << op1[i][1] + 1 << '\n';
    }
    debug("zz");
    for (int i = 0; i < op2.size(); i++) {
        cout << op2[i][0] + 1 << ' ' << op2[i][1] + 1 << '\n';
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
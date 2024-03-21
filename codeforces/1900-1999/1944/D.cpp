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

struct Manacher {
    string s;
    vector<int> Mp;
    Manacher(string& _s) {
        s = "";
        int n = _s.size();
        s += "$";
        s += "#";
        for (int i = 0; i < n; i++) {
            s += _s[i];
            s += "#";
        }
        s += "?";
        int id = 0, mx = 0;
        int l = s.size();
        Mp.resize(l);
        for (int i = 0; i < l - 1; i++) {
            Mp[i] = mx > i ? min(Mp[2 * id - i], mx - i) : 1;
            while (i + Mp[i] < l && i - Mp[i] >= 0 && s[i + Mp[i]] == s[i - Mp[i]]) Mp[i]++;
            if (i + Mp[i] > mx) {
                mx = i + Mp[i];
                id = i;
            }
        }
    }
    Manacher() {}

    int query(int l, int r) {
        // l = r 那么就表示以 l 为中心的最长回文串
        // l + 1 = r 那么就表示以 l 和 r 中间为中心的最长回文串
        // 返回长度, 如 "aabaa", l = r = 2, 即以 b 位中心的回文串长度，返回 3. 如 "abba", l = 1, r = 2, 返回 2
        int idx = (l + 1) * 2;
        if (l != r) {
            idx++;
        }
        int length = Mp[idx];
        return length / 2;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    Manacher manacher(s);

    vector<vector<int>> same(n, vector<int>(2, -1));

    for (int i = 1; i < n; i++) {
        if (s[i] == s[i - 1]) {
            same[i][0] = same[i - 1][0];
        } else {
            same[i][0] = i - 1;
        }
        if (i - 2 >= 0) {
            if (s[i] == s[i - 2]) {
                same[i][1] = same[i - 2][1];
            } else {
                same[i][1] = i - 2;
            }
        }
    }

    auto work = [&](int l, int r) {
        long long ans = 0;
        int len = r - l + 1;
        if (same[r][0] >= l) {
            // 说明有不相等的
            // 2 4 6 ...
            int ed = len % 2 ? len - 1 : len - 2;
            ans += 1LL * (2 + ed) * ed / 4;
        }
        debug(ans);

        if (same[r][1] >= l || same[r - 1][1] >= l) {
            // 不相等
            // 3 5
            int ed = len % 2 ? len - 2 : len - 1;
            ans += 1LL * (3 + ed) * (ed - 1) / 4;
        }
        debug(ans);

        int p = l + r >> 1;
        int q = p;
        if (len % 2 == 0) q++;
        int tmp = manacher.query(p, q) * 2 - (len % 2);
        debug(tmp);
        if (tmp < len) {
            ans += len;
        }
        return ans;
    };

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        // debug(l, r);
        cout << work(l, r) << endl;
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
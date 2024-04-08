#include <bits/stdc++.h>

#include <algorithm>

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
    Manacher(string &_s) {
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
    string s;
    cin >> s;
    int n = s.size();
    vector<int> same(n);

    for (int i = 1; i < n; i++) {
        if (s[i] == s[i - 1])
            same[i] = same[i - 1];
        else {
            same[i] = i;
        }
    }

    bool eq = true;
    for (int i = 1; i < n; i++) {
        if (s[i] != s[i - 1]) {
            eq = false;
            break;
        }
    }
    if (eq) {
        cout << "NO" << endl;
        return;
    }

    Manacher ma(s);

    vector<int> valid;
    valid.push_back(-1);
    vector<int> pre(n);
    for (int i = 0; i < n; i++) {
        bool flag = false;
        int last = -1;
        int times = 100;
        for (auto idx : valid) {
            if (idx >= same[i]) break;
            times--;
            if (times == -1) break;
            // [idx + 1, i]
            int l = idx + 1, r = i;
            int a = l + r >> 1;
            int b = a;
            int len = r - l + 1;
            if (len % 2 == 0) b++;

            int ma_len = ma.query(a, b) * 2;
            if (a == b) ma_len--;
            if (ma_len < len) {
                flag = true;
                last = idx;
                break;
            }
        }
        if (flag) {
            valid.push_back(i);
            pre[i] = last;
        }
    }

    if (valid.back() != n - 1) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;
    // 最后一个一定等于 n - 1
    int now = n - 1;
    vector<string> ans;
    while (now != -1) {
        debug(now);
        int go = pre[now];
        string tmp = "";
        for (int i = go + 1; i <= now; i++) {
            tmp += s[i];
        }
        ans.push_back(tmp);
        now = go;
    }
    reverse(ans.begin(), ans.end());

    cout << ans.size() << endl;
    for (auto it : ans) {
        cout << it << ' ';
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
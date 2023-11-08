#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

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

vector<int> z_function(const string &s) {
    int n = s.size();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        debug(i, l, r);
    }
    return z;
}
int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    string s, t;
    cin >> s >> t;
    reverse(s.begin(), s.end());
    Manacher ma(s);
    int n = s.size();
    vector<int> cnt(n);

    for (int i = 0; i < n; i++) {
        int tmp = ma.query(i, i);
        cnt[i + tmp - 1]++;
        if (i - 1 >= 0) {
            cnt[i - 1]--;
        }
        if (i != n - 1) {
            tmp = ma.query(i, i + 1);
            if (tmp > 0) {
                cnt[i + tmp]++;
                cnt[i]--;
            }
        }
    }
    for (int i = n - 2; i >= 0; i--) {
        cnt[i] += cnt[i + 1];
    }

    string s2 = t + "#" + s;
    auto z = z_function(s2);
    debug(s2);
    debug(z);

    int tsz = t.size();

    long long ans = 0;
    for (int i = 1; i < n; i++) {
        int idx = tsz + i + 1;
        int val = z[idx];
        if (val) {
            debug(i, val);
            ans += 1LL * cnt[i - 1] * val;
        }
    }
    cout << ans << endl;
    return 0;
}
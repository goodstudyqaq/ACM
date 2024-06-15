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

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    vector<int> cnt(26);
    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'a']++;
    }

    if (cnt[0] == n) {
        cout << n - 1 << endl;
        return;
    }

    map<int, int> divd;
    int num = 0;
    for (int i = 1; i < 26; i++) {
        if (cnt[i]) {
            num++;
            for (int j = 1; j * j <= cnt[i]; j++) {
                if (cnt[i] % j == 0) {
                    divd[j]++;
                    int o = cnt[i] / j;
                    if (o != j) {
                        divd[o]++;
                    }
                }
            }
        }
    }
    debug(divd);

    long long ans = 0;
    for (auto it : divd) {
        if (it.second == num) {
            debug(it, ans);
            vector<int> need(26);

            int need_num = 0;
            for (int i = 1; i < 26; i++) {
                need[i] = cnt[i] / it.first;
                need_num += need[i];
            }

            set<string> S;

            int now = 0;
            vector<int> valid_begin, valid_end;
            bool ok = true;
            while (now < n) {
                // debug(now);
                if (S.size() > 1) break;
                int go = now;
                while (go < n && s[go] == 'a') go++;
                if (go == n) break;

                vector<int> tmp = need;

                int go2 = go;
                int tmp_num = need_num;
                bool flag = true;
                valid_begin.push_back(go2);
                while (tmp_num) {
                    if (s[go2] == 'a') {
                        go2++;
                        continue;
                    }

                    tmp[s[go2] - 'a']--;
                    if (tmp[s[go2] - 'a'] < 0) {
                        flag = false;
                        break;
                    }
                    tmp_num--;
                    go2++;
                }

                if (flag) {
                    S.insert(s.substr(go, go2 - go));
                } else {
                    ok = false;
                    break;
                }
                valid_end.push_back(go2);
                now = go2;
            }
            if (ok == false) {
                continue;
            }

            if (S.size() == 1) {
                // 有效
                if (valid_begin.size() == 1) {
                    ans += 1LL * (valid_begin[0] + 1) * (n - valid_end[0] + 1);
                } else {
                    int mi = 1e9;
                    for (int i = 0; i < valid_begin.size() - 1; i++) {
                        mi = min(mi, valid_begin[i + 1] - valid_end[i]);
                    }

                    int left_mx = valid_begin[0];
                    int right_mx = n - valid_end.back();
                    // l + r <= mi
                    debug(left_mx, right_mx, mi);

                    for (int l = 0; l <= left_mx && l <= mi; l++) {
                        int r = min(right_mx, mi - l);
                        debug(l, r);
                        ans += r + 1;
                    }
                }
            }
        }
    }
    cout << ans << endl;
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
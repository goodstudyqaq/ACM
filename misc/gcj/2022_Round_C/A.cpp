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

#include <stdio.h>

#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<string> s(n);

    vector<string> single_s(26);

    vector<vector<int>> start(26);

    auto check = [&](string &s) {
        int n = s.size();
        for (int i = 1; i < n; i++) {
            if (s[i] != s[i - 1]) {
                return false;
            }
        }
        return true;
    };

    bool flag = true;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        int idx = s[i][0] - 'A';
        if (check(s[i])) {
            single_s[idx] += s[i];
        } else {
            if (s[i][0] == s[i].back()) flag = false;
            start[idx].push_back(i);
        }
    }

    if (!flag) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }

    for (int i = 0; i < 26; i++) {
        if (start[i].size() >= 2) {
            cout << "IMPOSSIBLE" << endl;
            return;
        }
    }

    string ans = "";
    vector<bool> vis(26);
    vector<bool> to(26);

    for (int i = 0; i < 26; i++) {
        if (start[i].size()) {
            int idx = start[i][0];
            to[s[idx].back() - 'A'] = true;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (start[i].size() && vis[i] == 0 && to[i] == false) {
            string tmp = "";
            int now = i;
            while (start[now].size()) {
                vis[now] = 1;
                tmp += single_s[now] + s[start[now][0]];
                int last = s[start[now][0]].back() - 'A';
                if (vis[last] == 1) {
                    cout << "IMPOSSIBLE" << endl;
                    return;
                }
                now = last;
            }

            if (single_s[now].size()) {
                tmp += single_s[now];
                vis[now] = 1;
            }
            ans += tmp;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (vis[i] == 0 && single_s[i].size() > 0) {
            ans += single_s[i];
        }
    }

    for (int i = 0; i < 26; i++) {
        if (vis[i] == 0 && start[i].size()) {
            cout << "IMPOSSIBLE" << endl;
            return;
        }
    }

    auto check2 = [&](string &s) {
        int n = s.size();
        vector<vector<int>> tmp(26);

        for (int i = 0; i < n; i++) {
            tmp[s[i] - 'A'].push_back(i);
        }
        for (int i = 0; i < 26; i++) {
            if (tmp[i].size()) {
                int lst = tmp[i][0];
                for (int j = 1; j < tmp[i].size(); j++) {
                    if (tmp[i][j] != lst + 1) {
                        return false;
                    }
                    lst = tmp[i][j];
                }
            }
        }
        return true;
    };
    debug(ans);
    if (check2(ans)) {
        cout << ans << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cout << "Case #" << t << ": ";
        solve();
    }
}
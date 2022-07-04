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
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    string s;
    cin >> s;

    int a_num = a + c + d;
    int b_num = b + c + d;
    int n = s.size();

    for (int i = 0; i < n; i++) {
        if (s[i] == 'A')
            a_num--;
        else
            b_num--;
    }
    if (a_num || b_num) {
        cout << "NO" << endl;
        return;
    }
    a_num = a + c + d;
    b_num = b + c + d;

    int now = 0;
    vector<pii> V;
    while (now < n) {
        int go = now + 1;
        while (go < n && s[go] != s[go - 1]) {
            go++;
        }

        if (go - now == 1) {
            // now 肯定是单独的
            if (s[now] == 'A') {
                if (a == 0) {
                    cout << "NO" << endl;
                    return;
                }
                a--;
            } else {
                if (b == 0) {
                    cout << "NO" << endl;
                    return;
                }
                b--;
            }
            now = go;
        }

        V.push_back({now, go});
        now = go;
    }
    int sz = V.size();
    int ab = 0, ba = 0;

    vector<bool> vis(sz);

    for (int i = 0; i < sz; i++) {
        int len = V[i].second - V[i].first;
        if (len % 2) {
            vis[i] = true;
            char it = s[V[i].first];
            if (it == 'A') {
                if (a == 0) {
                    cout << "NO" << endl;
                    return;
                }
                a--;
            } else {
                if (b == 0) {
                    cout << "NO" << endl;
                    return;
                }
                b--;
            }
            V[i].second--;
            continue;
        }
        len = V[i].second - V[i].first;
        if (s[V[i].first] == 'A') {
            ab += len / 2;
        } else {
            ba += len / 2;
        }
    }
    debug(c, d, ab, ba);

    if (c <= ab && d <= ba) {
        cout << "YES" << endl;
        return;
    }

    // if (c >= ab && d >= ba) {
    //     cout << "YES" << endl;
    //     return;
    // }

    auto check = [&](string ss, int num1, int num2, int need_help) -> bool {
        int aa = a, bb = b;
        int help_num = 0;
        vector<int> f;
        for (int i = 0; i < sz; i++) {
            if (num1 == num2) break;
            if (vis[i]) continue;

            if (s[V[i].first] == ss[0]) {
                int len = V[i].second - V[i].first;
                if (len > 2) {
                    f.push_back(i);
                }
            }
        }

        sort(f.begin(), f.end(), [&](int x, int y) {
            int l1 = V[x].second - V[x].first;
            int l2 = V[y].second - V[y].first;
            return l1 > l2;
        });

        for (auto i : f) {
            int len = V[i].second - V[i].first;
            if (aa == 0 || bb == 0) break;
            if (num1 == num2) break;
            int h = min(len / 2 - 1, num1 - num2);
            num1 -= h;
            help_num += h + 1;
            aa--, bb--;
        }

        if (help_num >= need_help) return true;
        int need = need_help - help_num;
        if (aa >= need && bb >= need) return true;
        return false;
    };

    if (c >= ab) {
        if (check("BA", c, ab, ba - d)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    } else {
        if (check("AB", d, ba, ab - c)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
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
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
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    string s, t;
    cin >> s >> t;
    vector<int> s_cnt(26, 0), t_cnt(26, 0);
    for (int i = 0; i < s.size(); i++) {
        s_cnt[s[i] - 'a']++;
    }
    for (int i = 0; i < t.size(); i++) {
        t_cnt[t[i] - 'a']++;
    }

    vector<int> left(26, 0);
    for (int i = 0; i < 26; i++) {
        left[i] = t_cnt[i] - s_cnt[i];
        if (left[i] < 0) {
            cout << "Impossible\n";
            return;
        }
    }

    debug(left, t_cnt);

    int s_now = 0;

    for (int i = 0; i < 26; i++) {
        if (s_now == s.size()) {
            for (int j = 0; j < left[i]; j++) {
                cout << char('a' + i);
            }
            continue;
        }

        int sc = s[s_now] - 'a';
        if (sc == i) {
            int go = s_now;
            while (go < s.size() && s[go] == s[s_now]) go++;
            if (go == s.size()) {
                for (int j = 0; j < left[i]; j++) {
                    cout << char('a' + i);
                }
                while (s_now < s.size() && s[s_now] - 'a' <= i) {
                    cout << s[s_now];
                    s_now++;
                }
            } else {
                if (s[go] > s[s_now]) {
                    for (int j = 0; j < left[i]; j++) {
                        cout << char('a' + i);
                    }
                    while (s_now < s.size() && s[s_now] - 'a' <= i) {
                        cout << s[s_now];
                        s_now++;
                    }
                } else {
                    while (s_now < s.size() && s[s_now] - 'a' <= i) {
                        cout << s[s_now];
                        s_now++;
                    }
                    for (int j = 0; j < left[i]; j++) {
                        cout << char('a' + i);
                    }
                }
            }
        } else {
            for (int j = 0; j < left[i]; j++) {
                cout << char('a' + i);
            }
        }
    }
    cout << '\n';
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
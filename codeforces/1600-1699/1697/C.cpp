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
void no() {
    cout << "NO" << endl;
}

void yes() {
    cout << "YES" << endl;
}

void solve() {
    int n;
    string s, t;
    cin >> n >> s >> t;
    int a = count(s.begin(), s.end(), 'a');
    int b = count(s.begin(), s.end(), 'b');
    int c = count(s.begin(), s.end(), 'c');
    int at = count(t.begin(), t.end(), 'a');
    int bt = count(t.begin(), t.end(), 'b');
    int ct = count(t.begin(), t.end(), 'c');

    if (a != at || b != bt || c != ct) {
        cout << "NO" << endl;
        return;
    }

    string ss = "", tt = "";

    for (int i = 0; i < n; i++) {
        if (s[i] != 'b') {
            ss += s[i];
        }
        if (t[i] != 'b') {
            tt += t[i];
        }
    }
    if (ss != tt) {
        no();
        return;
    }

    int b_num = 0;
    int now2 = 0;
    int now = 0;
    for (int i = 0; i < n; i++) {
        if (t[i] == 'a') {
            if (s[i] == 'b') b_num++;
            if (b_num > 0) {
                no();
                return;
            }
        } else if (t[i] == 'b') {
            if (s[i] == 'b') b_num++;
            b_num--;
        } else {
            if (b_num < 0) {
                no();
                return;
            }
            if (s[i] == 'b') b_num++;
        }
    }
    yes();
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
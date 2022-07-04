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

    if (count(s.begin(), s.end(), 'A') != a + c + d) {
        cout << "NO" << endl;
        return;
    }

    int now = 0;
    int n = s.size();

    vector<int> all, ab, ba;
    while (now < n) {
        int go = now;
        while (go + 1 < n && s[go] != s[go + 1]) {
            go++;
        }

        int len = go - now + 1;
        if (len % 2 == 0) {
            if (s[now] == 'A') {
                ab.push_back(len / 2);
            } else {
                ba.push_back(len / 2);
            }
        } else {
            all.push_back(len / 2);
        }
        now = go + 1;
    }

    sort(all.begin(), all.end(), greater<int>());
    sort(ab.begin(), ab.end(), greater<int>());
    sort(ba.begin(), ba.end(), greater<int>());

    int cur_ab = 0, cur_ba = 0;

    for (int i = 0; i < ab.size(); i++) {
        cur_ab += ab[i];
    }
    for (int i = 0; i < ba.size(); i++) {
        cur_ba += ba[i];
    }

    for (int i = 0; i < all.size(); i++) {
        int t = min(max(c - cur_ab, 0), all[i]);
        cur_ab += t;
        cur_ba += all[i] - t;
    }

    for (int i = 0; i < ab.size(); i++) {
        if (cur_ab > c) {
            cur_ab--;
            int x = ab[i] - 1;
            int t = min(x, cur_ab - c);
            cur_ab -= t;
            cur_ba += t;
        }
    }

    for (int i = 0; i < ba.size(); i++) {
        if (cur_ba > d) {
            cur_ba--;
            int x = ba[i] - 1;
            int t = min(x, cur_ba - d);
            cur_ba -= t;
            cur_ab += t;
        }
    }

    if (cur_ab >= c && cur_ba >= d) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
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
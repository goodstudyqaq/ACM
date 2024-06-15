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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    if (n == k) {
        for (int i = 0; i < n; i++) {
            if (s[i] != s[0]) {
                cout << -1 << endl;
                return;
            }
        }
        cout << 1 << endl;
        return;
    }

    vector<int> cnt(2);
    for (int i = 0; i < n; i++) {
        cnt[s[i] - '0']++;
    }
    if (cnt[0] % k) {
        cout << -1 << endl;
        return;
    }
    int block_num = n / k;

    if (block_num % 2 == 0) {
        if (cnt[0] != cnt[1]) {
            cout << -1 << endl;
            return;
        }
    } else {
        if (abs(cnt[0] - cnt[1]) != k) {
            cout << -1 << endl;
            return;
        }
    }

    auto check = [&](string &s) {
        for (int i = 0; i < k; i++) {
            if (s[i] != s[0]) return false;
        }
        for (int i = 0; i + k < n; i++) {
            if (s[i] == s[i + k]) return false;
        }
        return true;
    };

    if (check(s)) {
        // 已经可以了
        debug("ok");
        cout << n - k << endl;
        return;
    }

    int now = 0;
    while (now < n) {
        char it;
        if (now == 0)
            it = s[0];
        else
            it = ((s[now - k] - '0') ^ 1) + '0';

        int go = now;
        while (go < n && s[go] == it) go++;
        int num = go - now;

        if (num == k) {
            now = go;
            continue;
        } else if (num > k) {
            string news = s.substr(now + k);
            for (int j = now + k - 1; j >= 0; j--) {
                news += s[j];
            }

            if (check(news)) {
                cout << now + k << endl;
                return;
            } else {
                news = s.substr(go - k);
                for (int j = go - k - 1; j >= 0; j--) {
                    news += s[j];
                }
                if (check(news)) {
                    cout << go - k << endl;
                    return;
                } else {
                    cout << -1 << endl;
                    return;
                }
            }

        } else {
            string news = s.substr(go);
            for (int j = go - 1; j >= 0; j--) {
                news += s[j];
            }
            if (check(news)) {
                cout << go << endl;
                return;
            } else {
                cout << -1 << endl;
                return;
            }
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
    return 0;
}
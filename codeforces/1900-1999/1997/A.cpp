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

    if (n == 1) {
        if (s[0] == 'a') {
            cout << "ab" << endl;
        } else {
            cout << string("a") + s[0] << endl;
        }
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            for (int j = 0; j <= i; j++) {
                cout << s[j];
            }
            if (s[i] == 'a')
                cout << 'b';
            else
                cout << 'a';
            for (int j = i + 1; j < n; j++) {
                cout << s[j];
            }
            cout << endl;
            return;
        }
    }

    cout << s[0];
    char now = 'a';
    while (now == s[0] || now == s[1]) now++;
    cout << now;
    for (int i = 1; i < n; i++) {
        cout << s[i];
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
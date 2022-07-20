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
    int n;
    string s;
    cin >> n >> s;
    vector<int> num(n);
    for (int i = 0; i < n; i++) {
        num[i] = s[i] - '0';
    }

    vector<int> ans(n);
    if (num[0] < 9) {
        for (int i = 0; i < n; i++) {
            ans[i] = 9 - num[i];
        }
    } else {
        bool flag = false;
        if (num[n - 1] > 1) {
            flag = true;
            ans[n - 1] = 11 - num[n - 1];
        } else {
            ans[n - 1] = 1 - num[n - 1];
        }

        for (int i = n - 2; i >= 0; i--) {
            int val = num[i] + flag;
            if (val <= 1) {
                ans[i] = 1 - val;
                flag = false;
            } else {
                ans[i] = 11 - val;
                flag = true;
            }
        }
    }

    for (auto it : ans) {
        cout << it;
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
}
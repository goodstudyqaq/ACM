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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    auto get_val = [&](char it) {
        if (it == 'W') {
            return 0;
        } else if (it == 'L') {
            return 1;
        } else {
            return 2;
        }
    };

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int val = get_val(s[i][j]);
            int val2 = get_val(s[j][i]);
            if (val == 2 && val2 == 2) {
                continue;
            } else if (val + val2 == 1) {
                continue;
            } else {
                cout << "incorrect" << endl;
                return 0;
            }
        }
    }
    cout << "correct" << endl;
}
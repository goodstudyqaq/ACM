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
    string s;
    cin >> n >> s;

    int idx = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        cout << 0 << endl;
        return 0;
    }

    int idx2 = -1;
    for (int i = idx; i < n; i++) {
        if (s[i] == '0') {
            idx2 = i;
            break;
        }
    }
    if (idx2 == -1) {
        for (int i = idx; i < n; i++) {
            cout << 1;
        }
        cout << endl;
        return 0;
    }

    // 第一个下标为 idx2

    string res(n - idx2, '0');
    int c_idx = -1;
    for (int i = 0; i < idx2; i++) {
        int len2 = n - idx2;
        int len3 = 40;
        int len = min({len2, len3});

        string tmp(len, '0');
        for (int j = 0; j < len; j++) {
            auto it1 = s[idx2 + j] - '0';
            auto it2 = s[i + j] - '0';
            tmp[j] = (it1 | it2) + '0';
        }

        if (res < tmp) {
            res = tmp;
            c_idx = i;
        }
    }
    // 第二个下标为 c_idx

    string ans(n - idx, '0');

    for (int i = idx; i < idx2; i++) {
        ans[i - idx] = '1';
    }

    for (int i = idx2; i < n; i++) {
        auto it1 = s[i] - '0';
        auto it2 = s[i - idx2 + c_idx] - '0';
        ans[i - idx] = (it1 | it2) + '0';
    }

    cout << ans << endl;
}
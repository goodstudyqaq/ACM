#include <bits/stdc++.h>

#include <cstdio>

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
    string a, b;
    cin >> n >> a >> b;

    bool a_have_one = false, b_have_one = false;
    bitset<2001> sa, clear;
    for (int i = 0; i < n; i++) {
        if (a[i] == '1') a_have_one = true;
        if (b[i] == '1') b_have_one = true;
    }
    for (int i = 0; i < n; i++) {
        sa[i] = a[i] - '0';
        clear[i] = 1;
    }

    if (a_have_one != b_have_one) {
        cout << -1 << endl;
        return;
    }

    if (!a_have_one) {
        cout << 0 << endl;
        return;
    }

    int first_one = -1;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (a[i] == '1') {
            first_one = i;
            break;
        }
    }

    int b_first_one = -1;
    for (int i = 0; i < n; i++) {
        if (b[i] == '1') {
            b_first_one = i;
            break;
        }
    }

    if (first_one > b_first_one) {
        ans.push_back(first_one - b_first_one);
        sa ^= (sa >> (first_one - b_first_one));
        sa &= clear;
    }
    int start = min(first_one, b_first_one);

    for (int i = start + 1; i < n; i++) {
        if (sa[i] != b[i] - '0') {
            ans.push_back(-1 * (i - start));
            sa ^= (sa << (i - start));
            sa &= clear;
        }
    }

    if (first_one < b_first_one) {
        int last_one = -1;
        for (int i = n - 1; i >= 0; i--) {
            if (b[i] == '1') {
                last_one = i;
                break;
            }
        }

        for (int i = first_one; i >= 0; i--) {
            if (sa[i] != b[i] - '0') {
                ans.push_back(last_one - i);
                sa ^= (sa >> (last_one - i));
                sa &= clear;
            }
        }
    }

    debug(sa);
    cout << ans.size() << endl;
    if (ans.size() > 0) {
        for (auto it : ans) {
            cout << it << ' ';
        }
        cout << endl;
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
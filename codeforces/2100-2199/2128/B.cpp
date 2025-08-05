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
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> q;
    int l = 1, r = n;
    q.push_back(a[l]);
    l++;

    vector<char> ans;
    ans.push_back('L');
    while (q.size() != n) {
        if (l == r) {
            q.push_back(a[l]);
            ans.push_back('L');
            break;
        }
        int val = q.back();
        int val2 = a[l];
        int val3 = a[r];

        bool f1 = (val < val2);
        bool f2 = (val2 < val3);
        if (f1 != f2) {
            q.push_back(val2);
            q.push_back(val3);
            l++, r--;
            ans.push_back('L');
            ans.push_back('R');
        } else {
            q.push_back(val3);
            q.push_back(val2);
            l++, r--;
            ans.push_back('R');
            ans.push_back('L');
        }
    }

    debug(q);
    for (auto it : ans) {
        cout << it;
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
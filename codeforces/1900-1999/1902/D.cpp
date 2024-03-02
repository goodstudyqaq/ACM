#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

typedef pair<int, int> pii;

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<pii> pre(n + 1);
    pre[0] = {0, 0};
    pii now = {0, 0};

    auto work = [&](pii p, char it) -> pii {
        if (it == 'U') {
            return {p.first, p.second + 1};
        } else if (it == 'D') {
            return {p.first, p.second - 1};
        } else if (it == 'L') {
            return {p.first - 1, p.second};
        } else {
            return {p.first + 1, p.second};
        }
    };
    const int mx = 1e6;
    map<pii, vector<int>> M;
    M[{0, 0}].push_back(0);
    for (int i = 0; i < n; i++) {
        now = work(now, s[i]);
        pre[i + 1] = now;
        M[pre[i + 1]].push_back(i + 1);
    }

    auto check = [&](pii it, int l, int r) {
        if (M.count(it) == 0) return false;
        auto it2 = lower_bound(M[it].begin(), M[it].end(), l);
        if (it2 != M[it].end() && *it2 <= r) return true;
        return false;
    };

    for (int i = 0; i < q; i++) {
        int x, y, l, r;
        cin >> x >> y >> l >> r;
        pii c = {x, y};
        pii c2 = {pre[r].first + pre[l - 1].first - x, pre[r].second + pre[l - 1].second - y};
        if (check(c, 0, l - 1)) {
            cout << "YES" << endl;
        } else if (check(c, r, n)) {
            cout << "YES" << endl;
        } else if (check(c2, l, r)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }


    return 0;
}
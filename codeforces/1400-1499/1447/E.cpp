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

int solve(vector<int> &v, int b) {
    if (v.size() <= 3) {
        return 0;
    }

    vector<int> v0, v1;
    int sz = v.size();
    for (int i = 0; i < sz; i++) {
        int f = (v[i] >> b) & 1;
        if (f)
            v0.push_back(v[i]);
        else
            v1.push_back(v[i]);
    }
    return min(solve(v0, b - 1) + max(0, (int)v1.size() - 1), solve(v1, b - 1) + max(0, (int)v0.size() - 1));
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    cout << solve(v, 29) << endl;
    return 0;
}
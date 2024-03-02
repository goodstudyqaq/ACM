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
    long long n, m;
    cin >> n >> m;

    const int LIMIT = 60;
    auto get_v = [&](long long x) {
        vector<int> v(LIMIT);
        for (int i = 0; i < LIMIT; i++) {
            v[i] = ((x >> i) & 1);
        }
        reverse(v.begin(), v.end());
        return v;
    };

    vector<int> v1 = get_v(n);
    vector<int> v2 = get_v(m);
    debug(v1, v2);
    int first = 0;
    while (v1[first] == 0) first++;

    int same_idx = first;
    while (same_idx < LIMIT && v1[same_idx] == v2[same_idx]) same_idx++;
    debug(first, same_idx);

    if (same_idx != first) {
        cout << 1 << endl;
        cout << n << " " << m << endl;
    } else {
        int first_one = 0;
        while (first_one < LIMIT && v2[first_one] == 0) first_one++;
        int one_num = 0;
        for (int i = 0; i <= first_one; i++) {
            if (v1[i]) one_num++;
        }

        if (one_num == 1) {
            cout << -1 << endl;
            return;
        }

        int last_one = first_one;
        while (last_one >= 0 && v1[last_one] == 0) last_one--;
        if (last_one == first_one) {
            cout << 1 << endl;
            cout << n << " " << m << endl;
        } else {
            cout << 2 << endl;
            long long ans = 0;
            for (int i = 0; i < LIMIT; i++) {
                if (i < last_one) {
                    ans = ans * 2 + v1[i];
                } else if (i == last_one) {
                    ans = ans * 2 + 0;
                } else {
                    ans = ans * 2 + (v1[i] ^ v2[i]);
                }
            }

            cout << n << " " << ans << " " << m << endl;
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
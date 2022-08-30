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
    string s;
    cin >> s;

    int n = s.size();

    auto work = [&](char it) -> pll {
        ll even = 0, odd = 0;

        vector<ll> num(2);
        for (int i = 0; i < n; i++) {
            if (s[i] == it) {
                num[i % 2]++;
            }
        }

        even = num[0] * num[1];
        odd = num[0] + num[1];
        if (num[0] > 1) {
            odd += num[0] * (num[0] - 1) / 2;
        }
        if (num[1] > 1) {
            odd += num[1] * (num[1] - 1) / 2;
        }
        return {even, odd};
    };

    auto [even1, odd1] = work('a');
    auto [even2, odd2] = work('b');

    cout << even1 + even2 << ' ' << odd1 + odd2 << endl;
    return 0;
}
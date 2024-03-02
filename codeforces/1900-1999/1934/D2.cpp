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
    fast_ios(){
        // cin.tie(nullptr);
        // ios::sync_with_stdio(false);
        // cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    long long n;
    cin >> n;

    int one_num = __builtin_popcountll(n);

    long long p1, p2;
    if (one_num % 2 == 0) {
        cout << "first" << endl;
        fflush(stdout);
        p1 = n, p2 = 0;
    } else {
        cout << "second" << endl;
        fflush(stdout);
        cin >> p1 >> p2;
    }

    auto out = [&](long long val) -> pll {
        debug(val);
        vector<int> v;
        long long cval = val;
        while (val) {
            v.push_back(val % 2);
            val /= 2;
        }
        reverse(v.begin(), v.end());
        debug(v);
        long long ans1 = 0, ans2 = 0;
        int one_num = 0;
        for (int i = 0; i < v.size(); i++) {
            if (v[i]) one_num++;
            if (v[i] && one_num == 2) {
                ans2 = 1;
            } else {
                ans2 *= 2;
            }
        }
        ans1 = cval - ans2;
        cout << ans1 << " " << ans2 << endl;
        fflush(stdout);
        cin >> ans1 >> ans2;
        return pll(ans1, ans2);
    };

    while (true) {
        if (p1 == 0 && p2 == 0) {
            break;
        }
        if (p1 == -1 && p2 == -1) {
            break;
        }

        int p1_one_num = __builtin_popcountll(p1);
        int p2_one_num = __builtin_popcountll(p2);
        if (p1_one_num % 2 == 1) {
            swap(p1, p2);
        }
        auto tmp = out(p1);
        p1 = tmp.first, p2 = tmp.second;
    }
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
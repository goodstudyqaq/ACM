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

// struct fast_ios {
//     fast_ios() {
//         cin.tie(nullptr);
//         ios::sync_with_stdio(false);
//         cout << fixed << setprecision(10);
//     };
// } fast_ios_;

int out(int val) {
    cout << val << endl;
    fflush(stdout);
    int res;
    cin >> res;
    return res;
}

void solve() {
    int n, k;
    cin >> n >> k;

    int f = out(0);
    int now = 0;
    int last = 0;

    auto del = [&](int a, int b) -> int {
        debug("del", a, b);
        vector<int> v1, v2;
        while (a) {
            v1.push_back(a % k);
            a /= k;
        }
        while (b) {
            v2.push_back(b % k);
            b /= k;
        }

        while (v1.size() < v2.size()) {
            v1.push_back(0);
        }
        while (v2.size() < v1.size()) {
            v2.push_back(0);
        }

        int sz = v1.size();
        int ans = 0;
        for (int i = sz - 1; i >= 0; i--) {
            int tmp = (v1[i] - v2[i] + k) % k;
            ans = ans * k + tmp;
        }
        return ans;
    };

    auto add = [&](int a, int b) -> int {
        debug("add", a, b);
        vector<int> v1, v2;
        while (a) {
            v1.push_back(a % k);
            a /= k;
        }
        while (b) {
            v2.push_back(b % k);
            b /= k;
        }

        while (v1.size() < v2.size()) {
            v1.push_back(0);
        }
        while (v2.size() < v1.size()) {
            v2.push_back(0);
        }
        int sz = v1.size();
        int ans = 0;
        for (int i = sz - 1; i >= 0; i--) {
            int tmp = (v1[i] + v2[i]) % k;
            ans = ans * k + tmp;
        }
        return ans;
    };

    while (!f) {
        now++;
        if (now % 2) {
            // (last - x)
            int tmp = del(now - 1, now);
            f = out(tmp);
        } else {
            // x - last
            int tmp = del(now, now - 1);
            f = out(tmp);
        }
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
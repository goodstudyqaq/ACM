#include <bits/stdc++.h>

#include <cstdio>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

void solve() {
    long long n;
    cin >> n;

    auto add = [&](long long y) {
        cout << "add " << y << '\n';
        fflush(stdout);
        int res;
        cin >> res;
        return res;
    };

    auto mul = [&](long long y) {
        cout << "mul " << y << '\n';
        fflush(stdout);
        int res;
        cin >> res;
        return res;
    };
    auto div = [&](long long y) {
        cout << "div " << y << '\n';
        fflush(stdout);
        int res;
        cin >> res;
        return res;
    };

    auto digit = [&]() {
        cout << "digit\n";
        fflush(stdout);
        int res;
        cin >> res;
        return res;
    };
    auto ok = [&]() {
        cout << "!\n";
        fflush(stdout);
        int res;
        cin >> res;
        return res;
    };

    // x <= 1e9
    mul(999999999);
    digit();
    if (n == 81) {
        ok();
        return;
    }
    add(n - 81);
    ok();
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
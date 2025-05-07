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
    long long num1 = 0, num2 = 0;
    int N = 30;
    for (int i = 0; i < N; i += 2) {
        num1 += (1LL << i);
    }
    for (int i = 1; i < N; i += 2) {
        num2 += (1LL << i);
    }

    auto ask = [&](long long val) {
        cout << val << endl;
        fflush(stdout);
        long long res;
        cin >> res;
        return res;
    };

    long long res1 = ask(num1);
    long long res2 = ask(num2);

    cout << "!" << endl;
    fflush(stdout);
    long long m;
    cin >> m;

    long long ans = 0;

    auto check = [&](long long res, int idx) -> long long {
        if ((res >> (idx + 1)) & 1) {
            if ((res >> idx) & 1) {
                return 1LL << (idx + 1);
            }
            return 1LL << idx;
        } else {
            return 0;
        }
    };

    for (int i = 0; i < N; i++) {
        if ((m >> i) & 1) {
            ans += (1LL << (i + 1));
        } else {
            if (i == 0) {
                if ((res2 >> i) & 1) {
                    ans += 1LL << i;
                } else {
                    if ((res2 >> (i + 1)) & 1) {
                        ans += (1LL << (i + 1));
                    } 
                }

            } else {
                if (i % 2 == 1) {
                    long long tmp = check(res1, i);
                    ans += tmp;
                } else {
                    long long tmp = check(res2, i);
                    ans += tmp;
                }
            }
        }
    }

    cout << ans << endl;
    fflush(stdout);
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
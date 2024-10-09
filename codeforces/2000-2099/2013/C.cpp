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
    int n;
    cin >> n;

    auto ask = [&](string &t) {
        cout << "? " << t << endl;
        fflush(stdout);
        int res;
        cin >> res;
        return res;
    };

    string now = "";
    while (now.size() < n) {
        bool ok = false;
        for (char i = '0'; i < '2'; i++) {
            string go = now + i;
            int res = ask(go);
            if (res) {
                ok = true;
                now = go;
                break;
            }
        }
        if (ok == false) break;
    }

    while (now.size() < n) {
        for (char i = '0'; i < '2'; i++) {
            string go = i + now;

            if (go.size() == n && i == '1') {
                now = go;
                break;
            }

            int res = ask(go);
            if (res) {
                now = go;
                break;
            }
        }
    }
    cout << "! " << now << endl;
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
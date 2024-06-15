#include <bits/stdc++.h>

#include <algorithm>
#include <string>

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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    long long p, q;
    cin >> p >> q;
    if (p == 0 && q == 0) {
        cout << 0 << endl;
        return 0;
    }
    if ((abs(p) % 2) != (abs(q) % 2)) {
        cout << "12+";
        p -= 12;
        q -= 21;
    }
    if (abs(p) % 2) {
        cout << "1+";
        p -= 1;
        q -= 1;
    }
    // debug(p, q);
    while (abs(p) % 10 == 0 || abs(q) % 10 == 0) {
        cout << "2+";
        p -= 2;
        q -= 2;
    }

    auto work = [&](long long val) -> string {
        if (val == 0) {
            return "0";
        }
        if (val > 0) {
            string s = to_string(val / 2) + "+" + to_string(val / 2) + "-0";
            return s;
        } else {
            val = abs(val);
            string s = "0-" + to_string(val / 2) + "-" + to_string(val / 2);
            return s;
        }
    };

    auto work2 = [&](long long val) -> string {
        if (val == 0) {
            return "0";
        } else if (val > 0) {
            string tmp = to_string(val / 2);
            reverse(tmp.begin(), tmp.end());
            string s = "0-" + tmp + "+" + tmp;
            return s;
        } else {
            val = abs(val);
            string tmp = to_string(val / 2);
            reverse(tmp.begin(), tmp.end());
            string s = tmp + "-" + tmp + "-0";
            return s;
        }
    };

    string s = work(p);
    cout << s;
    cout << "+";
    string s2 = work2(q);
    cout << s2 << endl;
}
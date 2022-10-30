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
    string s, t;
    cin >> s >> t;

    auto work = [&](char a, char b) {
        map<char, int> M = {{'M', 0}, {'L', 1}, {'S', -1}};
        bool f = (M[a] < M[b]);
        if (f) {
            cout << "<" << endl;
        } else {
            cout << ">" << endl;
        }
    };

    if (s.back() != t.back()) {
        work(s.back(), t.back());
        return;
    }

    if (s.size() == t.size()) {
        cout << "=" << endl;
        return;
    }

    if (s.back() == 'L') {
        // X 越多越大
        if (s.size() > t.size()) {
            cout << ">" << endl;
        } else {
            cout << "<" << endl;
        }
    } else {
        if (s.size() > t.size()) {
            cout << "<" << endl;
        } else {
            cout << ">" << endl;
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
}
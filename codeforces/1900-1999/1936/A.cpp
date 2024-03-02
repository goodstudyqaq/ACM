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
    int n;
    cin >> n;
    // 0 ~ n - 1

    auto ask = [&](int a, int b, int c, int d) {
        cout << "? " << a << " " << b << " " << c << " " << d << endl;
        fflush(stdout);
        string s;
        cin >> s;
        return s;
    };

    int now = 0;

    for (int i = 1; i < n; i++) {
        string ans = ask(now, now, i, i);
        if (ans == "<") {
            now = i;
        }
    }

    int now2 = 0;
    vector<int> v;
    v.push_back(0);
    for (int i = 1; i < n; i++) {
        string ans = ask(now, now2, now, i);
        if (ans == "<") {
            now2 = i;
            v.clear();
            v.push_back(i);
        } else if (ans == "=") {
            v.push_back(i);
        }
    }

    now2 = 0;
    for (int i = 1; i < v.size(); i++) {
        string ans = ask(v[now2], v[now2], v[i], v[i]);
        if (ans == ">") {
            now2 = i;
        }
    }

    cout << "! " << now << ' ' << v[now2] << endl;
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
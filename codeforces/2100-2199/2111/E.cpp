#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    const int m = 3;

    set<int> S[m][m];
    for (int i = 0; i < q; i++) {
        char x, y;
        cin >> x >> y;
        int _x = x - 'a';
        int _y = y - 'a';
        S[_x][_y].insert(i);
    }

    for (int i = 0; i < n; i++) {
        if (s[i] == 'a') {
            continue;
        } else if (s[i] == 'b') {
            if (S[1][0].size()) {
                // b -> a
                s[i] = 'a';
                S[1][0].erase(S[1][0].begin());
            } else {
                // b -> c -> a
                if (S[1][2].size()) {
                    auto it = *S[1][2].begin();
                    auto it2 = S[2][0].upper_bound(it);
                    if (it2 != S[2][0].end()) {
                        s[i] = 'a';
                        S[1][2].erase(S[1][2].begin());
                        S[2][0].erase(it2);
                    }
                }
            }
        } else {
            if (S[2][0].size()) {
                // c -> a
                s[i] = 'a';
                S[2][0].erase(S[2][0].begin());
            } else if (S[2][1].size()) {
                // c -> b -> a
                auto it = *S[2][1].begin();
                auto it2 = S[1][0].upper_bound(it);
                if (it2 != S[1][0].end()) {
                    s[i] = 'a';
                    S[2][1].erase(S[2][1].begin());
                    S[1][0].erase(it2);
                } else {
                    s[i] = 'b';
                    S[2][1].erase(S[2][1].begin());
                }
            }
        }
    }
    cout << s << '\n';
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
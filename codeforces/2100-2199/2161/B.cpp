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
    int n;
    cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    typedef array<int, 2> a2;
    vector<a2> V;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[i][j] == '#') {
                V.push_back({i, j});
            }
        }
    }
    if (V.size() <= 1) {
        cout << "YES\n";
        return;
    }
    sort(V.begin(), V.end());

    int x = V[0][0], y = V[0][1];

    if (V.size() == 4) {
        int y2 = y + 1;
        if (V[1][0] == x && V[1][1] == y2 && V[2][0] == x + 1 && V[2][1] == y && V[3][0] == x + 1 && V[3][1] == y2) {
            cout << "YES\n";
            return;
        }
    }
    set<int> S;
    for (auto it : V) {
        int dx = x - it[0];
        int dy = y - it[1];
        // +
        if (dx + dy == 0) continue;
        S.insert(dx + dy);
    }
    if (S.size() == 0) {
        cout << "YES\n";
        return;
    }

    if (S.size() == 1 && (S.count(1) || S.count(-1))) {
        cout << "YES\n";
        return;
    }
    S.clear();
    for (auto it : V) {
        int dx = x - it[0];
        int dy = y - it[1];
        // -
        if (dx - dy == 0) continue;
        S.insert(dx - dy);
    }
    if (S.size() == 0) {
        cout << "YES\n";
        return;
    }
    if (S.size() == 1 && (S.count(1) || S.count(-1))) {
        cout << "YES\n";
        return;
    }
    cout << "NO\n";
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
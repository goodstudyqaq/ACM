#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

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
    int H, W;
    cin >> H >> W;
    vector<pair<int, int>> V;
    for (int i = 0; i < H; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < W; j++) {
            if (s[j] == 'o') {
                V.push_back({i, j});
            }
        }
    }

    cout << abs(V[0].first - V[1].first) + abs(V[0].second - V[1].second) << endl;
    return 0;
}
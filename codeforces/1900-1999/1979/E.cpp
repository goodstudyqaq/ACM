#include <bits/stdc++.h>

#include <algorithm>

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
typedef pair<pii, int> piii;

void solve() {
    int n, d;
    cin >> n >> d;
    vector<pii> V(n);
    int A = -1, B = -1, C = -1;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        V[i] = {x, y};
    }

    vector<pii> V2(n);

    auto check = [&]() -> bool {
        // debug(V2);
        map<pii, int> M;
        map<int, vector<piii>> M2;
        for (int i = 0; i < n; i++) {
            auto [x, y] = V2[i];
            M[{x, y}] = i;
            M2[x + y].push_back({{x, y}, i});
        }
        for (auto it : M2) {
            sort(M2[it.first].begin(), M2[it.first].end());
        }
        int halfd = d / 2;


        for (int i = 0; i < n; i++) {
            auto [x, y] = V2[i];

            int x2 = x + halfd;
            int y2 = y - halfd;
            if (M.count({x2, y2})) {
                int tmp = x + y2 - halfd;
                // debug(i, M[{x2, y2}]);
                if (M2.count(tmp)) {
                    int idx = upper_bound(M2[tmp].begin(), M2[tmp].end(), piii(pii(x, 1e9), 0)) - M2[tmp].begin();
                    idx--;
                    if (idx >= 0) {
                        auto it = M2[tmp][idx];
                        auto [x3, y3] = it.first;
                        if (x >= x3 && y2 >= y3) {
                            A = i + 1;
                            B = M[{x2, y2}] + 1;
                            C = it.second + 1;
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < n; j++) {
            auto [x, y] = V[j];
            if (i % 2) {
                x *= -1;
            }
            if ((i >> 1) % 2) {
                y *= -1;
            }
            V2[j] = {x, y};
        }

        if (check()) {
            cout << A << ' ' << B << ' ' << C << endl;
            return;
        }
    }
    cout << 0 << ' ' << 0 << ' ' << 0 << endl;
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
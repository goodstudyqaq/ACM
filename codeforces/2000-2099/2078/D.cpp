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
    vector<vector<pair<int, int>>> V(n, vector<pair<int, int>>(2));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            char it;
            int num;
            cin >> it >> num;
            if (it == '+') {
                V[i][j] = {0, num};
            } else {
                V[i][j] = {1, num};
            }
        }
    }

    long long num[2] = {1, 1};

    auto get_choose = [&](int idx) -> int {
        if (idx == n - 1) {
            return 0;
        }

        for (int i = idx + 1; i < n; i++) {
            if (V[i][0].first != V[i][1].first) {
                if (V[i][0].first) return 0;
                return 1;
            } else if (V[i][0].first == 1) {
                if (V[i][0].second != V[i][1].second) {
                    return V[i][0].second < V[i][1].second;
                }
            }
        }
        return 0;
    };

    for (int i = 0; i < n; i++) {
        long long more = 0;
        for (int j = 0; j < 2; j++) {
            if (V[i][j].first == 0) {
                more += V[i][j].second;
            } else {
                more += num[j] * (V[i][j].second - 1);
            }
        }
        int choose = get_choose(i);
        num[choose] += more;
    }
    cout << num[0] + num[1] << '\n';
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
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

class Solution {
   public:
    int reservoir(vector<string>& s) {
        int n = s.size();
        int m = s[0].size();
        vector ans = vector(n, vector(m, vector(2, 0)));

        auto go = [&](int x, int y, int last_x, int last_y) -> pii {
            if (s[x][y] == 'l') {
            }
        };

        auto work = [&](int x, int y) {
            vector vis = vector(n, vector(m, 0));

            function<void(int x, int y)> go = [&](int x, int y) {

            };
        };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (s[i][j] == 'l' && s[i][j + 1] == 'r') {
                    work(i, j);
                }
            }
        }

        int res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res += ans[i][j][0] + ans[i][j][1];
            }
        }
        return res;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
}
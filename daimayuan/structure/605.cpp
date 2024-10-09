#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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
    int n, q;
    cin >> n >> q;
    int B = 500;
    vector<vector<long long>> sum(B + 1, vector<long long>(B + 1));
    vector<vector<int>> p(n + 1);
    vector<int> big;
    for (int i = 1; i <= q; i++) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int x, y;
            cin >> x >> y;
            if (p[x].size() <= B) {
                int sz = p[x].size();
                for (int j = 0; j < sz; j++) {
                    sum[sz][j] -= p[x][j];
                }
            }
            p[x].push_back(y);
            if (p[x].size() <= B) {
                int sz = p[x].size();
                for (int j = 0; j < sz; j++) {
                    sum[sz][j] += p[x][j];
                }
            } else if (p[x].size() == B + 1) {
                big.push_back(x);
            }
        } else {
            int z;
            cin >> z;
            long long ans = 0;
            for (int j = 1; j <= B; j++) {
                ans += sum[j][z % j];
            }
            for (auto idx : big) {
                int sz = p[idx].size();
                ans += p[idx][z % sz];
            }
            cout << ans << '\n';
        }
    }
}
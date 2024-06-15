#include <bits/stdc++.h>

#include <algorithm>
#include <numeric>

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
    string a;
    cin >> a;
    int n = a.size();

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = string("ANOT").find(a[i]);
    }
    vector<vector<int>> sum(4, vector<int>(n));
    for (int i = n - 1; i >= 0; i--) {
        if (i != n - 1) {
            for (int j = 0; j < 4; j++) {
                sum[j][i] = sum[j][i + 1];
            }
        }
        sum[v[i]][i]++;
    }

    vector<int> p = {0, 1, 2, 3};
    string s = "ANOT";
    long long ans = -1;
    string anss = "";
    do {
        long long res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; p[j] != v[i]; j++) {
                res += sum[p[j]][i];
            }
        }
        if (res > ans) {
            ans = res;
            string ress = "";

            for (int i = 0; i < 4; i++) {
                int idx = p[i];
                char it = s[idx];
                int num = sum[idx][0];
                for (int j = 0; j < num; j++) {
                    ress += it;
                }
            }
            anss = ress;
        }

    } while (next_permutation(p.begin(), p.end()));
    cout << anss << endl;
    debug(ans);
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
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
struct DSU2 {
    std::vector<int> f;
    DSU2(int n) : f(n) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        if (f[x] == x) {
            return x;
        }
        int y = leader(f[x]);
        f[x] = y;
        return f[x];
    }
    bool merge(int a, int b) {
        auto x = leader(a);
        auto y = leader(b);
        if (x == y) {
            return false;
        }
        f[x] = y;
        return true;
    }
};
void solve() {
    int n;
    string s;
    cin >> n >> s;

    DSU2 dsu(26);

    vector<int> ans;
    map<int, int> M;
    vector<bool> vis(26);
    for (int i = 0; i < n; i++) {
        int now = s[i] - 'a';
        if (M.count(now)) {
            ans.push_back(M[now] + 'a');
        } else {
            bool flag = 0;
            for (int j = 0; j < 26; j++) {
                if (vis[j] == 0 && dsu.merge(now, j)) {
                    ans.push_back('a' + j);
                    vis[j] = 1;
                    M[now] = j;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                for (int j = 0; j < 26; j++) {
                    if (vis[j] == 0) {
                        ans.push_back('a' + j);
                        vis[j] = 1;
                        M[now] = j;
                    }
                }
            }
        }
    }
    for (auto it : ans) {
        cout << char(it);
    }
    cout << endl;
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
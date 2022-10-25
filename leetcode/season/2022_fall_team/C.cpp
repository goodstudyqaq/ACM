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
    int beautifulBouquet(vector<int>& f, int cnt) {
        int n = f.size();
        map<int, int> M;
        int r = 0;
        const int mod = 1e9 + 7;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            while (r < n && M[f[r]] < cnt) {
                M[f[r]]++;
                r++;
            }
            (ans += r - i) %= mod;
            M[f[i]]--;
        }
        return ans;
    }
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
}
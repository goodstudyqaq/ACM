#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

// 时间复杂度O(n)
const int maxn = 1e5 + 5;
bool is[maxn];
int prm[maxn], id;
// 每个数的最小质因子
int minp[maxn];
void get_prime() {
    /*
    数被筛掉的顺序：3 -> 3^2 -> 2*3^2 -> 2^2 * 3^2
    即从最大的质数去填
    */
    int k = 0;
    memset(is, 1, sizeof(is));
    is[0] = is[1] = 0;
    for (int i = 2; i < maxn; ++i) {
        if (is[i]) {
            prm[k++] = i;
            minp[i] = i;
        }
        for (int j = 0; j < k && (i * prm[j] < maxn); ++j) {
            is[i * prm[j]] = 0;
            minp[i * prm[j]] = prm[j];
            if (i % prm[j] == 0) break;
        }
    }
    id = k;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    get_prime();
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    map<int, int> mp;

    for (int i = 0; i < id; i++) {
        mp[prm[i]] = i;
    }

    vector<int> last(id, n + 1);
    const int LIMIT = 17;
    vector<vector<int>> go(n + 2, vector<int>(LIMIT));

    auto get_factor = [&](int val) {
        vector<int> ans;

        for (int i = 0; i < id && prm[i] * prm[i] <= val; i++) {
            if (val % prm[i] == 0) {
                ans.push_back(prm[i]);
                while (val % prm[i] == 0) val /= prm[i];
            }
        }
        if (val != 1) ans.push_back(val);

        return ans;
    };

    for (int i = n; i >= 1; i--) {
        vector<int> factor = get_factor(a[i]);
        if (i != n) {
            if (__gcd(a[i], a[i + 1]) != 1) {
                go[i][0] = i + 1;
            } else {
                int res = go[i + 1][0];
                for (auto it : factor) {
                    res = min(res, last[mp[it]]);
                }
                go[i][0] = res;
            }
        } else {
            go[i][0] = i + 1;
        }
        debug(i, go[i][0]);
        for (auto it : factor) {
            last[mp[it]] = i;
        }
    }

    for (int i = 0; i < LIMIT; i++) go[n + 1][i] = n + 1;

    for (int i = 1; i < LIMIT; i++) {
        for (int j = 1; j <= n; j++) {
            int go1 = go[j][i - 1];
            go[j][i] = go[go1][i - 1];
        }
    }

    vector<int> two(LIMIT);
    two[0] = 1;
    for (int i = 1; i < LIMIT; i++) two[i] = two[i - 1] * 2;

    auto work = [&](int l, int r) {
        int now = l;
        int ans = 0;
        for (int i = LIMIT - 1; i >= 0; i--) {
            if (go[now][i] <= r) {
                ans += two[i];
                now = go[now][i];
            }
        }
        if (now <= r) ans++;
        return ans;
    };

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << work(l, r) << endl;
    }

    return 0;
}
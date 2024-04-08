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

// 时间复杂度O(n)
const int maxn = 2e5 + 5;
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

void solve() {
    // debug(id);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 0;

    auto check = [&](int val) {
        int g = 0;
        for (int j = val; j < n; j++) {
            g = __gcd(g, abs(a[j] - a[j - val]));
        }
        debug(val, g);

        if (g != 1) {
            return true;
        }
        return false;
    };

    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            if (check(i)) ans++;
            if (i * i != n && check(n / i)) ans++;
        }
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    get_prime();

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
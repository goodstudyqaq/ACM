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

#define lowbit(x) x & -x

const int maxn = 5005;
int sum[maxn];
void add(int x, int val) {
    while (x < maxn) {
        sum[x] += val;
        x += lowbit(x);
    }
}

int query(int x) {
    int res = 0;
    while (x) {
        res += sum[x];
        x -= lowbit(x);
    }
    return res;
}

void solve() {
    memset(sum, 0, sizeof(sum));
    int n;
    cin >> n;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    ll ans = 0;

    for (int j = n - 1; j >= 3; j--) {
        int nxt = j + 1;
        for (int i = 1; i < nxt; i++) {
            if (p[i] > p[nxt]) {
                add(i, 1);
            }
        }

        int sum1 = query(j - 1);

        for (int i = 1; i < j; i++) {
            if (p[i] < p[j]) {
                int tmp = query(i);
                ans += sum1 - tmp;
            }
        }
    }
    cout << ans << endl;
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
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
template <typename T>
struct Fenwick {
#define lowbit(x) x & -x
    const int n;
    vector<T> a;
    Fenwick(int n) : n(n), a(n + 1) {}
    void add(int x, T v) {
        while (x <= n) {
            a[x] += v;
            x += lowbit(x);
        }
    }

    T query(int x) {
        T res = 0;
        while (x) {
            res += a[x];
            x -= lowbit(x);
        }
        return res;
    }
};

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    int sum = 0;

    vector<Fenwick<int>> fen(3, Fenwick<int>(n * 2 + 3));
    int offset = n + 1;
    fen[offset % 3].add(offset, 1);

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '-') {
            sum++;
        } else {
            sum--;
        }
        int tmp = (sum + offset) % 3;
        ans += fen[tmp].query(sum + offset);

        fen[(sum + offset) % 3].add(sum + offset, 1);
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
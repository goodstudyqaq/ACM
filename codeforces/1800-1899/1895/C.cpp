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

template <class T>
auto vect(const T& v, int n) { return vector<T>(n, v); }
template <class T, class... D>
auto vect(const T& v, int n, D... m) {
    return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}

template <typename T>
static constexpr T inf = numeric_limits<T>::max() / 2;
mt19937_64 mrand(random_device{}());
long long rnd(long long x) { return mrand() % x; }
int lg2(long long x) { return sizeof(long long) * 8 - 1 - __builtin_clzll(x); }

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef pair<int, int> pii;
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

void solve() {
    int n;
    cin >> n;
    vector<string> s(n);

    auto f = vect(0, 6, 46, 6, 46);

    for (int i = 0; i < n; i++) {
        cin >> s[i];
        int sum = 0;
        int sz = s[i].size();
        for (int j = 0; j < sz; j++) {
            sum += s[i][j] - '0';
        }

        int sum2 = 0;
        for (int j = 0; j < sz; j++) {
            f[sz][sum][j][sum2]++;
            sum2 += s[i][j] - '0';
        }
        f[sz][sum][sz][sum2]++;
    }

    long long ans = 0;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            if (i % 2 != j % 2) continue;
            if (i < j) {
                int l = (j + i) / 2 - i;
                for (int sum1 = 0; sum1 <= 45; sum1++) {
                    for (int sum2 = sum1; sum2 <= 45; sum2++) {
                        if (sum1 % 2 != sum2 % 2) continue;
                        int tmp = (sum1 + sum2) / 2 - sum1;
                        ans += 1LL * f[i][sum1][i][sum1] * f[j][sum2][l][tmp];
                    }
                }
            } else if (i == j) {
                for (int sum1 = 0; sum1 <= 45; sum1++) {
                    ans += 1LL * f[i][sum1][i][sum1] * f[i][sum1][i][sum1];
                }
            } else {
                int r = i - (j + i) / 2;
                for (int sum1 = 0; sum1 <= 45; sum1++) {
                    for (int sum2 = 0; sum2 <= sum1; sum2++) {
                        if (sum1 % 2 != sum2 % 2) continue;
                        int tmp = (sum1 + sum2) / 2;
                        ans += 1LL * f[i][sum1][(i + j) / 2][tmp] * f[j][sum2][j][sum2];
                    }
                }
            }
            debug(i, j, ans);
        }
    }
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
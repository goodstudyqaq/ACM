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

void solve() {
    int n, k;
    cin >> n >> k;
    k = min(k, n);

    vector<int> score(n + 1);
    vector<int> group(n + 1);
    int g = 1;

    auto work = [&](int l, int r) {
        int num = r - l + 1;
        int start = num / 2 + 1;
        int i = 0;
        for (i = 0; start + i <= num; i++) {
            score[l + i] = start + i + l - 1;
        }
        int tmp = l;
        for (; i < num; i++) {
            score[l + i] = tmp++;
        }
    };

    for (int i = 1; i <= n; i += k) {
        int r = min(i + k - 1, n);
        work(i, r);

        for (int j = i; j <= r; j++) {
            group[j] = g;
        }
        g++;
    }

    for (int i = 1; i <= n; i++) {
        cout << score[i] << ' ';
    }
    cout << endl;
    cout << g - 1 << endl;
    for (int i = 1; i <= n; i++) {
        cout << group[i] << ' ';
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
    return 0;
}
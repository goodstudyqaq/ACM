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
typedef array<int, 2> a2;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    vector<int> score(n), sum_score(n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (cnt[a[i]] == 1) {
            score[i] = 1;
        } else {
            score[i] = 0;
        }
        if (score[i]) {
            sum_score[i] = 1;

            if (i && score[i - 1] == 1) {
                sum_score[i] += sum_score[i - 1];
            }
        }
        ans = max(ans, sum_score[i]);
    }

    if (ans == 0) {
        cout << 0 << '\n';
        return;
    }
    for (int i = 0; i < n; i++) {
        if (ans == sum_score[i]) {
            int l = i - sum_score[i] + 1;

            cout << l + 1 << ' ' << i + 1 << '\n';

            return;
        }
    }
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
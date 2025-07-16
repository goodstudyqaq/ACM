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

void solve() {
    string s;
    cin >> s;
    int n = 10;
    vector<int> cnt(10);
    for (int i = 0; i < n; i++) {
        cnt[s[i] - '0']++;
    }

    for (int i = 0; i < 10; i++) {
        int mi = 10 - i - 1;

        for (int j = mi; j < 10; j++) {
            if (cnt[j]) {
                cout << j;
                cnt[j]--;
                break;
            }
        }
    }
    cout << '\n';
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
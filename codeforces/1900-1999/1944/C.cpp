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
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, int> M;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        M[a[i]]++;
    }
    int now_score = 1;
    int now = 0;

    while(M[now] > 1) {
        now++;
    }

    if (M[now] == 0) {
        cout << now << endl;
        return;
    }

    now++;
    while (M[now] > 1) {
        now++;
    }
    cout << now << endl;



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
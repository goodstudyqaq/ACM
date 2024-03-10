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
    set<int> S;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        S.insert(a[i]);
    }

    int choose;
    for (int i = 0; i <= n; i++) {
        if (S.count(i) == 0) {
            choose = i;
            break;
        }
    }

    if (choose == 0) {
        cout << 2 << endl;
        cout << 1 << ' ' << 1 << endl;
        cout << 2 << ' ' << n << endl;
        return;
    }


    set<int> tmp;
    for (int i = 0; i < n; i++) {
        if (a[i] < choose) {
            tmp.insert(a[i]);
        }
        if (tmp.size() == choose) {
            // 检查后面
            set<int> tmp2;
            for (int j = i + 1; j < n; j++) {
                if (a[j] < choose) {
                    tmp2.insert(a[j]);
                }
            }
            if (tmp2.size() == choose) {
                cout << 2 << endl;
                cout << 1 << ' ' << i + 1 << endl;
                cout << i + 2 << ' ' << n << endl;
                return;
            }
            break;
        }
    }

    cout << -1 << endl;

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
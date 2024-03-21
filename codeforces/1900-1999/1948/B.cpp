#include <bits/stdc++.h>

#include <vector>

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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    bool order = true;
    for (int i = 2; i <= n; i++) {
        if (a[i] < a[i - 1]) {
            order = false;
            break;
        }
    }
    if (order) {
        cout << "YES" << endl;
        return;
    }
    for (int i = 0; i <= n; i++) {
        vector<int> V;
        for (int j = 1; j <= i; j++) {
            int val = a[j];
            if (val == 0)
                V.push_back(0);
            else {
                vector<int> tmp;
                while (val) {
                    tmp.push_back(val % 10);
                    val /= 10;
                }
                reverse(tmp.begin(), tmp.end());
                for (auto it : tmp) {
                    V.push_back(it);
                }
            }
        }

        int sz = V.size();
        for (int i = 1; i < sz; i++) {
            if (V[i] < V[i - 1]) {
                cout << "NO" << endl;
                return;
            }
        }

        for (int j = i + 1; j <= n; j++) {
            V.push_back(a[j]);
        }

        sz = V.size();
        bool flag = true;
        for (int i = 1; i < sz; i++) {
            if (V[i] < V[i - 1]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            cout << "YES" << endl;
            return;
        }
    }
    cout << "NO" << endl;
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
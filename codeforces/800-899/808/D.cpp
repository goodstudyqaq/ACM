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

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int n;
    cin >> n;
    ll sum = 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    if (sum % 2) {
        cout << "NO" << endl;
        return 0;
    }
    ll half = sum / 2;

    auto work = [&]() {
        set<ll> S;
        ll now = 0;
        for (int i = 1; i <= n; i++) {
            now += a[i];
            if (now == half) {
                return true;
            } else if (now > half) {
                ll tmp = now - half;
                if (S.count(tmp)) {
                    return true;
                }
            }
            S.insert(a[i]);
        }
        return false;
    };

    if (work()) {
        cout << "YES" << endl;
    } else {
        for (int i = 1; i <= n / 2; i++) {
            swap(a[i], a[n - i + 1]);
        }
        if (work()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
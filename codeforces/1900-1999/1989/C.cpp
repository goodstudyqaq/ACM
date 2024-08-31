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
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    int x = 0, y = 0, suma = 0, sumb = 0;
    // x -1 的个数 y 1 的个数

    for (int i = 1; i <= n; i++) {
        if (a[i] == 1 && b[i] == 1) {
            y++;
        } else if (a[i] == -1 && b[i] == -1) {
            x++;
        } else {
            if (a[i] > b[i]) {
                suma += a[i];
            } else {
                sumb += b[i];
            }
        }
    }

    if (suma > sumb) {
        swap(suma, sumb);
    }

    // suma <= sumb

    int tmp = min(sumb - suma, y);
    suma += tmp;
    y -= tmp;
    suma += (y / 2);
    sumb += (y / 2);
    sumb += (y % 2);

    tmp = min(sumb - suma, x);
    sumb -= tmp;
    x -= tmp;
    suma -= (x / 2);
    sumb -= (x / 2);
    suma -= (x % 2);
    cout << suma << endl;




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
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
        // cin.tie(nullptr);
        // ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

void out(int ans) {
    cout << "! " << ans << endl;
    fflush(stdout);
}

bool query(int l, int r) {
    cout << "? " << l << ' ' << r << endl;
    fflush(stdout);
    int num = r - l + 1;
    set<int> S;
    for (int i = 1; i <= num; i++) {
        int a;
        cin >> a;
        S.insert(a);
    }

    int cnt = 0;
    for (int i = l; i <= r; i++) {
        if (S.count(i)) cnt++;
    }
    if (cnt % 2 == 0) {
        return false;
    }
    return true;
}

int main() {
    // #ifdef LOCAL
    //     freopen("./data.in", "r", stdin);
    // #endif

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;

        int L = 1, R = n;
        while (L <= R) {
            if (L == R) {
                out(L);
                break;
            }
            int mid = L + R >> 1;
            int num = (mid - L + 1);
            if (num % 2 == 0) {
                mid--;
            }
            bool ok = query(L, mid);
            if (ok) {
                R = mid;
            } else {
                L = mid + 1;
            }
        }
    }
}
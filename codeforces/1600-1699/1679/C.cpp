#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

#define lowbit(x) x & -x
const int maxn = 1e5 + 5;
int sum1[maxn], sum2[maxn];
void add(int x, int val, int *sum) {
    while (x < maxn) {
        sum[x] += val;
        x += lowbit(x);
    }
}
int query(int x, int *sum) {
    int res = 0;
    while (x) {
        res += sum[x];
        x -= lowbit(x);
    }
    return res;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n, q;
    cin >> n >> q;
    map<int, int> M1, M2;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            if (M1[x] == 0) {
                add(x, 1, sum1);
            }
            if (M2[y] == 0) {
                add(y, 1, sum2);
            }
            M1[x]++;
            M2[y]++;
        } else if (t == 2) {
            int x, y;
            cin >> x >> y;
            M1[x]--;
            M2[y]--;
            if (M1[x] == 0) {
                add(x, -1, sum1);
            }
            if (M2[y] == 0) {
                add(y, -1, sum2);
            }
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            bool flag = false;
            int tmp = query(x2, sum1) - query(x1 - 1, sum1);
            if (tmp == x2 - x1 + 1) {
                cout << "Yes" << endl;
                continue;
            }
            tmp = query(y2, sum2) - query(y1 - 1, sum2);
            if (tmp == y2 - y1 + 1) {
                cout << "Yes" << endl;
                continue;
            }
            cout << "No" << endl;
        }
    }
    return 0;
}
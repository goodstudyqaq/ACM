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
const int maxn = 1096 + 5;
ll c[maxn][maxn];
int n, m;
int lowbit(int x) { return x & -x; }
void modify(int x, int y, int z) {  //点(x,y)增加z
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= m; j += lowbit(j))
            c[i][j] += z;
}
ll getsum(int x, int y) {  //求左上角为(1,1)右下角为(x,y) 的矩阵和
    ll tot = 0;
    for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
            tot += c[i][j];
    return tot;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int q;
    cin >> n >> m >> q;
    vector<string> mp(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> mp[i];
        mp[i] = " " + mp[i];
    }
    int num = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j] == '*') {
                num++;
                modify(i, j, 1);
            }
        }
    }

    while (q--) {
        int x, y;

        cin >> x >> y;
        if (mp[x][y] == '*') {
            mp[x][y] = '.';
            modify(x, y, -1);
            num--;
        } else {
            mp[x][y] = '*';
            modify(x, y, 1);
            num++;
        }

        int cow = num / n;
        int tmp = getsum(n, cow);
        if (num % n) {
            int tmp2 = getsum(num % n, cow + 1) - getsum(num % n, cow);
            tmp += tmp2;
        }
        // debug(tmp);
        cout << num - tmp << endl;
    }
    return 0;
}
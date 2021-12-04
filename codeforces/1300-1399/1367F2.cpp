#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int a[maxn];
pair<int, int> x[maxn];
int xcnt;
int dp[maxn];
int main() {
    freopen("data.in", "r", stdin);
    int T;
    scanf("%d", &T);
    while (T--) {
        xcnt = 0;
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            x[++xcnt] = {a[i], i};
            // x[++xcnt] = a[i];
            dp[i] = 0;
        }
        sort(x + 1, x + 1 + xcnt);
        xcnt = unique(x + 1, x + 1 + xcnt) - x - 1;
        for (int i = 1; i <= n; i++) {
            a[i] = lower_bound(x + 1, x + 1 + xcnt, make_pair(a[i], i)) - x;
        }
        int mx = 0;
        for (int i = 1; i <= n; i++) {
            dp[a[i]] = dp[a[i] - 1] + 1;
            mx = max(mx, dp[a[i]]);
        }
        printf("%d\n", n - mx);
    }
    return 0;
}
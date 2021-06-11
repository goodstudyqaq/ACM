#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5;
int a[maxn];

#define lowbit(x) x & -x

int sum[maxn];
int n;
void add(int idx, int val) {
    while (idx < n + 5) {
        sum[idx] += val;
        idx += lowbit(idx);
    }
}

int query(int idx) {
    int res = 0;
    while (idx) {
        res += sum[idx];
        idx -= lowbit(idx);
    }
    return res;
}
int x[maxn], xcnt;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int l, r;
        scanf("%d %d %d", &n, &l, &r);

        for (int i = 1; i <= n + 5; i++) {
            sum[i] = 0;
        }
        xcnt = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            x[xcnt++] = a[i];
        }
        sort(x, x + xcnt);
        xcnt = unique(x, x + xcnt) - x;

        long long res = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] > r) {
                continue;
            }
            int sum1 = 0, sum2 = 0;
            if (a[i] >= l) {
                sum1 = 0;
            } else {
                int idx1 = lower_bound(x, x + xcnt, l - a[i]) - x;
                idx1--;
                if (idx1 >= 0) {
                    sum1 = query(idx1 + 1);
                }
            }

            int idx2 = upper_bound(x, x + xcnt, r - a[i]) - x;
            idx2--;
            sum2 = query(idx2 + 1);

            int idx = lower_bound(x, x + xcnt, a[i]) - x;
            add(idx + 1, 1);
            res += sum2 - sum1;
            // cout << res << endl;
        }
        printf("%lld\n", res);
    }
    return 0;
}
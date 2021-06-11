#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 5;
int a[maxn];

int n;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            sum += a[i];
        }
        if (sum % n) {
            puts("-1");
            continue;
        }

        sum /= n;
        int res = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] > sum) {
                res++;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
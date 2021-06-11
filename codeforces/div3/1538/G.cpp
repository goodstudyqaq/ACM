#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &y, &a, &b);

        long long res = 0;

        if (a > b) {
            swap(a, b);
        }
        if (x > y) {
            swap(x, y);
        }

        int cha = b - a;
        int tmp, tmp2, tmp3;
        if (cha) {
            tmp = (y - x) / cha;
            tmp2 = x / a;
            tmp3 = y / b;
            tmp = min({tmp, tmp2, tmp3});

            res += tmp;

            x = x - tmp * a;
            y = y - tmp * b;
        }

        tmp2 = x / (a + b);
        tmp3 = y / (a + b);
        tmp = min(tmp2, tmp3);
        res += 2 * tmp;

        x = x - tmp * (a + b);
        y = y - tmp * (a + b);

        if (x >= a && y >= b) {
            res++;
        }
        printf("%lld\n", res);
    }
    return 0;
}
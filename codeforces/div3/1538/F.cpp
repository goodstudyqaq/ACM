#include <bits/stdc++.h>

using namespace std;

int get_num(int val) {
    int res = 0;
    while (val) {
        val /= 10;
        res++;
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int l, r;
        scanf("%d %d", &l, &r);
        int num = get_num(r);
        long long ans = 0;
        while (num) {
            ans += r - l;
            l /= 10;
            r /= 10;
            num--;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
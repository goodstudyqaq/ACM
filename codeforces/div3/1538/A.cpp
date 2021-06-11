#include <bits/stdc++.h>

using namespace std;

const int maxn = 105;
int a[maxn];

int n;

int work2(int l, int r, int idx) {
    if (l <= idx && idx <= r)
        return min(idx - l + 1, r - idx + 1);
    return 0;
}

int work(pair< int, int > x, pair< int, int > y) {
    int l = 1, r = n;
    int nxtl = x.second + 1;
    int nxtr = x.second - 1;
    return min(nxtl - l + work2(nxtl, r, y.second), n - nxtr + work2(1, nxtr, y.second));
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        vector< pair< int, int > > v;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            v.push_back({a[i], i});
        }

        sort(v.begin(), v.end());
        printf("%d\n", min(work(v[0], v[v.size() - 1]), work(v[v.size() - 1], v[0])));
    }
    return 0;
}
#include <algorithm>
#include <cstdio>
using namespace std;
pair<int, int> p[400005];
struct query {
    int x;
    int l;
    int r;
    int d;
    query() {
    }
    query(int _x, int _l, int _r, int _d) {
        x = _x;
        l = _l;
        r = _r;
        d = _d;
    }
};
bool cmp(query a, query b) {
    return a.x < b.x;
}
query qu[800005];
int cnt;
int BIT[2000005];
int n, m, q, c, d, now;
int lowbit(int x) {
    return x & (-x);
}
void update(int x) {
    while (x <= 2 * n) {
        BIT[x]++;
        x += lowbit(x);
    }
}
int calc(int x) {
    int ret = 0;
    while (x) {
        ret += BIT[x];
        x -= lowbit(x);
    }
    return ret;
}
int ans[200005];
int solve(int l, int r) {
    return calc(r) - calc(l - 1);
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &p[i].first, &p[i].second);
    for (int i = m + 1; i <= 2 * m; i++) {
        p[i].first = p[i - m].second;
        p[i].second = p[i - m].first;
    }
    sort(p + 1, p + 2 * m + 1);
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d%d", &c, &d);
        qu[cnt++] = query(c - 1, d + 1, 2 * n, -i);
        qu[cnt++] = query(c - 1, 1, c - 1, -i);
        qu[cnt++] = query(d, d + 1, 2 * n, i);
        qu[cnt++] = query(d, 1, c - 1, i);
    }
    sort(qu, qu + cnt, cmp);
    now = 1;
    for (int i = 0; i < cnt; i++) {
        while (now <= 2 * m && p[now].first <= qu[i].x) {
            update(p[now].second);
            now++;
        }
        if (qu[i].d > 0)
            ans[qu[i].d] += solve(qu[i].l, qu[i].r);
        else
            ans[-qu[i].d] -= solve(qu[i].l, qu[i].r);
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);
    return 0;
}
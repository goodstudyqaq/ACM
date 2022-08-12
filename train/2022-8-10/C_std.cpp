#include <bits/stdc++.h>

using namespace std;

const int N = 143;
const int K = 5;
const int MOD = 998244353;

int add(int x, int y) {
    x += y;
    while (x >= MOD) x -= MOD;
    while (x < 0) x += MOD;
    return x;
}

int mul(int x, int y) {
    return (x * 1ll * y) % MOD;
}

int binpow(int x, int y) {
    int z = 1;
    while (y > 0) {
        if (y % 2 == 1) z = mul(z, x);
        x = mul(x, x);
        y /= 2;
    }
    return z;
}

int fact[N];
int rfact[N];

int A(int n, int k) {
    return mul(fact[n], rfact[n - k]);
}

int n;

vector<int> g[N];
int x[N];
int y[N];
int dist[N][N];
int color[N];
int dp[N][N];

int cc = 0;
set<int> pts;
vector<int> compsize;

void dfs1(int i) {
    //cerr << i << endl;
    if (pts.count(i) == 1) return;
    pts.insert(i);
    for (auto v : g[i]) {
        dfs1(v);
    }
}

void dfs2(int i, int c) {
    if (color[i] == c) return;
    color[i] = c;
    for (auto v : g[i])
        dfs2(v, c);
}

int main() {
    freopen("data.in", "r", stdin);
    fact[0] = 1;
    for (int i = 1; i < N; i++)
        fact[i] = mul(i, fact[i - 1]);
    for (int i = 0; i < N; i++)
        rfact[i] = binpow(fact[i], MOD - 2);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    for (int i = 0; i < n; i++) {
        dist[i][i] = int(1e9);
        for (int j = 0; j < n; j++)
            if (i != j)
                dist[i][j] = abs(x[i] - x[j]) + abs(y[i] - y[j]);
    }
    for (int i = 0; i < n; i++) {
        int d = *min_element(dist[i], dist[i] + n);
        for (int j = 0; j < n; j++)
            if (dist[i][j] == d) g[i].push_back(j);
    }

    for (int i = 0; i < n; i++) {
        if (color[i] != 0) continue;
        cc++;
        pts.clear();
        dfs1(i);
        //cerr << "!" << endl;
        int d = *min_element(dist[i], dist[i] + n);
        set<int> pts2 = pts;
        bool bad = false;
        for (auto x : pts)
            for (auto y : pts2)
                if (x != y && dist[x][y] != d)
                    bad = true;
        if (bad) {
            color[i] = cc;
            compsize.push_back(1);
        } else {
            dfs2(i, cc);

            if (pts.size() == 2) {
                for (auto it : pts) {
                    cout << it << ' ';
                }
                cout << endl;
            }

            compsize.push_back(pts.size());
        }
    }
    for (auto v : compsize) {
        cout << v << ' ';
    }
    cout << endl;

    dp[0][0] = 1;
    int m = compsize.size();
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (dp[i][j] == 0) continue;
            dp[i + 1][j + 1] = add(dp[i + 1][j + 1], dp[i][j]);
            if (compsize[i] != 1) {
                dp[i + 1][j + compsize[i]] = add(dp[i + 1][j + compsize[i]], dp[i][j]);
            }
        }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = add(ans, mul(dp[m][i], A(n, i)));
    cout << ans << endl;
}
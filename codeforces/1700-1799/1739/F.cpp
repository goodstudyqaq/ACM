#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct fast_ios {
    fast_ios() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
    };
} fast_ios_;

const int S = 12;
const int N = 5005;
int cnt = 1;
int trie[N][S], fail[N], val[N];

void add(auto a, int c) {
    int p = 1;
    for (auto x : a) {
        if (!trie[p][x]) {
            trie[p][x] = ++cnt;
        }
        p = trie[p][x];
    }
    val[p] += c;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    int n;
    cin >> n;
    fill(trie[0], trie[0] + S, 1);

    for (int i = 1; i <= n; i++) {
        int c;
        string s;
        cin >> c >> s;

        vector<vector<int>> V(S);
        vector<vector<bool>> vis(S, vector<bool>(S, 0));
        int sz = s.size();
        for (int i = 0; i < sz - 1; i++) {
            int u = s[i] - 'a', v = s[i + 1] - 'a';
            if (vis[u][v]) continue;
            vis[u][v] = vis[v][u] = 1;
            V[u].push_back(v);
            V[v].push_back(u);
        }

        bool good = true;
        int first = -1;
        for (int i = 0; i < S; i++) {
            if (V[i].size() > 2) {
                good = false;
                break;
            }

            if (V[i].size() == 1) {
                first = i;
            }
        }

        if (!good || first == -1) {
            continue;
        }

        vector<int> a;
        function<void(int, int)> dfs = [&](int u, int pre) {
            a.push_back(u);
            for (auto v : V[u]) {
                if (v == pre) continue;
                dfs(v, u);
            }
        };
        dfs(first, -1);
        debug(i, a);

        add(a, c);
        reverse(a.begin(), a.end());
        add(a, c);
    }

    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        val[x] += val[fail[x]];
        for (int i = 0; i < S; i++) {
            if (trie[x][i]) {
                fail[trie[x][i]] = trie[fail[x]][i];
                q.push(trie[x][i]);
            } else {
                trie[x][i] = trie[fail[x]][i];
            }
        }
    }
    int LIMIT = 1 << S;

    const int inf = numeric_limits<int>::max() / 2;
    vector dp = vector(LIMIT, vector(cnt + 1, -inf));

    dp[0][1] = 0;
    int ans = -inf;
    for (int i = 0; i < LIMIT; i++) {
        for (int j = 1; j <= cnt; j++) {
            if (dp[i][j] == -inf) continue;
            ans = max(ans, dp[i][j]);
            for (int k = 0; k < S; k++) {
                if ((i >> k) & 1) continue;
                int new_i = i + (1 << k);
                int new_j = trie[j][k];
                dp[new_i][new_j] = max(dp[new_i][new_j], dp[i][j] + val[new_j]);
            }
        }
    }

    string keybord;

    auto rec = [&](auto self, int mask, int p) {
        // debug(mask, p);
        if (mask == 0) return;
        bool flag = false;
        for (int i = 0; i < S && !flag; i++) {
            if ((mask >> i) & 1) {
                for (int j = 1; j <= cnt; j++) {
                    if (trie[j][i] == p && dp[mask - (1 << i)][j] == dp[mask][p] - val[p]) {
                        keybord.push_back('a' + i);
                        self(self, mask - (1 << i), j);
                        flag = true;
                        break;
                    }
                }
            }
        }
    };

    for (int j = 1; j <= cnt; j++) {
        if (dp[LIMIT - 1][j] == ans) {
            rec(rec, LIMIT - 1, j);
            break;
        }
    }
    cout << keybord << endl;
    return 0;
}
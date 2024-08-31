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

struct TrieNode {
    vector<int> nxt;
    int cnt;
    TrieNode(int char_size) {
        nxt.resize(char_size, -1);
        cnt = 0;
    }
};

struct Trie {
   public:
    vector<TrieNode> nodes;
    int root;
    int char_size;
    int margin;
    Trie(int char_size, int margin) : char_size(char_size), margin(margin) {
        root = new_node();
    }

    int new_node() {
        nodes.push_back(TrieNode(char_size));
        return nodes.size() - 1;
    }

    void add(const string &s) {
        int n = s.size();
        int now = root;
        nodes[now].cnt++;
        for (int i = 0; i < n; i++) {
            const int c = s[i] - margin;
            if (nodes[now].nxt[c] == -1) {
                nodes[now].nxt[c] = new_node();
            }
            now = nodes[now].nxt[c];
            nodes[now].cnt++;
        }
    }

    void remove(const string &s) {
        int n = s.size();
        int now = root;
        nodes[now].cnt--;
        for (int i = 0; i < n; i++) {
            const int c = s[i] - margin;
            now = nodes[now].nxt[c];
            nodes[now].cnt--;
        }
    }

    int work(const string &s) {
        int res = 0;
        int now = root;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            const int c = s[i] - margin;
            if (nodes[now].nxt[c ^ 1] != -1 && nodes[nodes[now].nxt[c ^ 1]].cnt > 0) {
                res += (1 << (31 - i));
                now = nodes[now].nxt[c ^ 1];
            } else {
                now = nodes[now].nxt[c];
            }
            if (now == -1) return 0;
        }
        return res;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> V(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        V[u].push_back({v, w});
        V[v].push_back({u, w});
    }

    vector<int> dp(n), dep(n);
    function<void(int, int, int)> dfs = [&](int u, int pre, int val) {
        if (pre != -1) dep[u] = dep[pre] + 1;
        dp[u] = val;
        for (auto &e : V[u]) {
            if (e.first == pre) continue;
            dfs(e.first, u, val ^ e.second);
        }
    };
    dfs(0, -1, 0);
    // debug(dp, dep);

    vector<Trie> tries(2, Trie(2, '0'));

    auto get_string = [&](int val) -> string {
        string s = "";
        for (int i = 31; i >= 0; i--) {
            s += ((val >> i) & 1) + '0';
        }
        // debug(s, val);
        return s;
    };
    vector<map<string, int>> times(2);

    for (int i = 0; i < n; i++) {
        auto s = get_string(dp[i]);
        tries[dep[i] % 2].add(s);
        times[dep[i] % 2][s]++;
    }

    int prey = 0;
    while (m--) {
        string op;
        cin >> op;
        if (op == "^") {
            int y;
            cin >> y;
            prey ^= y;
        } else {
            int v, x;
            cin >> v >> x;
            v--;
            int flag = dep[v] % 2;
            tries[flag].remove(get_string(dp[v]));
            auto s = get_string(x ^ dp[v]);
            int ans1 = tries[flag].work(s);
            int ans2 = tries[flag ^ 1].work(get_string(x ^ dp[v] ^ prey));
            cout << max(ans1, ans2) << ' ';
            tries[flag].add(get_string(dp[v]));
        }
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
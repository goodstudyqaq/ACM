#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "copypaste/debug.h"
#else
#define debug(...) 42
#endif

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

// struct TrieNode {
//     int cnt;
//     vector<int> nxt;
//     TrieNode() {}
//     TrieNode(int char_size) {
//         nxt.resize(char_size);
//         for (int i = 0; i < char_size; i++) {
//             nxt[i] = -1;
//         }
//         cnt = 0;
//     }
// };

const int M = 30;
const int N = 2e5;
int nxt[M * N + 1][2];
int idx[M * N + 1];
int nodes_cnt;

int n, k;
struct Trie {
   public:
    int root;
    int char_size;
    int margin;
    Trie(int char_size, int margin) : char_size(char_size), margin(margin) {
        root = new_node();
    }

    int new_node() {
        nxt[nodes_cnt][0] = nxt[nodes_cnt][1] = -1;
        idx[nodes_cnt] = -1;
        return nodes_cnt++;
    }

    void add(vector<int> &s, int _idx) {
        int n = s.size();
        int now = root;
        for (int i = 0; i < n; i++) {
            const int c = s[i] - margin;
            if (nxt[now][c] == -1) {
                nxt[now][c] = new_node();
            }
            now = nxt[now][c];
            idx[now] = _idx;
        }
    }

    int query(vector<int> &s) {
        int n = s.size();
        int now = root;
        int ans = -1;
        for (int i = 0; i < n; i++) {
            const int c = s[i] - margin;
            int kbit = (k >> (M - i - 1)) & 1;
            if (kbit == 0) {
                if (nxt[now][c ^ 1] != -1) {
                    ans = max(ans, idx[nxt[now][c ^ 1]]);
                }
            }
            if (nxt[now][c ^ kbit] == -1) {
                return ans;
            }
            now = nxt[now][c ^ kbit];
        }
        ans = max(ans, idx[now]);
        return ans;
    }
};

void solve() {
    cin >> n >> k;
    vector<vector<int>> av(n, vector<int>(M));
    Trie trie(2, 0);
    int ans = -1;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        for (int j = 0; j < M; j++) {
            av[i][j] = (a >> j) & 1;
        }
        reverse(av[i].begin(), av[i].end());
        trie.add(av[i], i);
        int res = trie.query(av[i]);
        if (res != -1) {
            if (ans == -1) {
                ans = i - res + 1;
            } else {
                ans = min(ans, i - res + 1);
            }
        }
    }
    cout << ans << '\n';
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
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

template <typename T>
struct RMQ {
    int n = 0, levels = 0;
    vector<T> values;
    vector<vector<int>> range_high;
    function<bool(T, T)> func;

    static int largest_bit(int x) {
        return 31 - __builtin_clz(x);
    }

    int max_index(int a, int b) const {
        return func(values[a], values[b]) ? a : b;
        // return values[a] > values[b] ? a : b;
    }

    void build(const vector<T>& _values, function<bool(T, T)> f) {
        func = f;
        values = _values;
        n = values.size();
        levels = largest_bit(n) + 1;
        range_high.resize(levels);

        for (int k = 0; k < levels; k++)
            range_high[k].resize(n - (1 << k) + 1);

        for (int i = 0; i < n; i++)
            range_high[0][i] = i;

        for (int k = 1; k < levels; k++)
            for (int i = 0; i <= n - (1 << k); i++)
                range_high[k][i] = max_index(range_high[k - 1][i], range_high[k - 1][i + (1 << (k - 1))]);
    }
    // [a, b)
    int rmq_index(int a, int b) const {
        assert(a < b);
        int level = largest_bit(b - a);
        return max_index(range_high[level][a], range_high[level][b - (1 << level)]);
    }

    T rmq_value(int a, int b) const {
        return values[rmq_index(a, b)];
    }
};

//SA[i]=a 排名为i的下标为a
//rank[a]=i 下标为a的排名为i
//height[i]=a 排名为i的和排名为i-1是最长公共前缀
//下标从1到N 千万不能搞错
struct SuffixArray {
    vector<int> SA, rank, height;
    int N;
    RMQ<int> rmq;
    SuffixArray(string& s) {
        vector<int> cntA, cntB, A, B, tsa, ch;
        N = s.size();
        int mx_element = *max_element(s.begin(), s.end());
        int M = max(N, mx_element);
        ch.resize(N + 1);
        cntA.resize(M + 1, 0);
        cntB.resize(N + 1, 0);
        SA.resize(N + 1);
        rank.resize(N + 1);
        A.resize(N + 1);
        B.resize(N + 1);
        tsa.resize(N + 1);
        height.resize(N + 1);

        for (int i = 1; i <= N; i++) {
            ch[i] = s[i - 1];
        }
        for (int i = 1; i <= N; i++) {
            cntA[ch[i]]++;
        }

        for (int i = 1; i <= mx_element; i++) {
            cntA[i] += cntA[i - 1];
        }

        for (int i = N; i >= 1; i--) {
            SA[cntA[ch[i]]--] = i;
        }
        rank[SA[1]] = 1;
        for (int i = 2; i <= N; i++) {
            rank[SA[i]] = rank[SA[i - 1]];
            if (ch[SA[i]] != ch[SA[i - 1]])
                rank[SA[i]]++;
        }
        // debug(SA);
        for (int step = 1; rank[SA[N]] < N; step <<= 1) {
            // debug(step, SA[N], rank[SA[N]]);
            for (int i = 1; i <= N; i++) cntA[i] = cntB[i] = 0;
            for (int i = 1; i <= N; i++) {
                cntA[A[i] = rank[i]]++;
                cntB[B[i] = (i + step <= N) ? rank[i + step] : 0]++;
            }
            for (int i = 1; i <= N; i++) cntA[i] += cntA[i - 1], cntB[i] += cntB[i - 1];
            for (int i = N; i >= 1; i--) tsa[cntB[B[i]]--] = i;
            for (int i = N; i >= 1; i--) SA[cntA[A[tsa[i]]]--] = tsa[i];
            rank[SA[1]] = 1;
            for (int i = 2; i <= N; i++) {
                rank[SA[i]] = rank[SA[i - 1]];
                if (A[SA[i]] != A[SA[i - 1]] || B[SA[i]] != B[SA[i - 1]])
                    rank[SA[i]]++;
            }
        }
        int i, j, k = 0;
        for (int i = 1; i <= N; i++) {
            if (k) k--;
            j = SA[rank[i] - 1];
            while (i + k <= N && j + k <= N && ch[i + k] == ch[j + k]) k++;
            height[rank[i]] = k;
        }
        rmq.build(height, [&](int a, int b) -> bool {
            return a < b;
        });
    }

    int get_length(int idx1, int idx2) {
        // s 的下标
        int rk_idx1 = rank[idx1 + 1], rk_idx2 = rank[idx2 + 1];
        if (rk_idx1 > rk_idx2) {
            swap(rk_idx1, rk_idx2);
        }
        return rmq.rmq_value(rk_idx1 + 1, rk_idx2 + 1);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    vector<int> pre_len(n + 1), suf_len(n + 1);

    int now = 0;
    for (int i = 0; i < n; i++) {
        if (now < m && s[i] == t[now]) {
            now++;
        }
        pre_len[i] = now;
    }

    now = m - 1;
    for (int i = n - 1; i >= 0; i--) {
        if (now >= 0 && s[i] == t[now]) {
            now--;
        }
        suf_len[i] = now;
    }

    if (pre_len[n - 1] != m) {
        cout << -1 << endl;
        return;
    }

    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    string rev_t = t;
    reverse(rev_t.begin(), rev_t.end());

    string s2 = rev_s + "$" + rev_t;
    SuffixArray sa = SuffixArray(s2);

    auto get_length = [&](int i, int j) {
        // s 下标为 i，t 下标为 j
        int idx1 = n - 1 - i;
        int idx2 = m - 1 - j + n + 1;
        return sa.get_length(idx1, idx2);
    };

    int pre_eq_len = 0;
    while (pre_eq_len < m && s[pre_eq_len] == t[pre_eq_len]) pre_eq_len++;

    auto get_suf_len = [&](int len) -> int {
        if (len == 0) return 0;
        int idx = n - len;
        int val = suf_len[idx];
        return m - 1 - val;
    };

    int ans = n;
    for (int i = 0; i < n; i++) {
        // 右边搞的长度为 i
        int res = i;
        // 右边能够最大匹配的长度
        int mx_len = get_suf_len(i);

        for (int j = 0; j <= mx_len; j++) {
            // 枚举右边匹配的长度
            int idx1 = n - i - 1;
            int idx2 = m - j - 1;
            int length = (idx2 >= 0 ? get_length(idx1, idx2) : 0);
            // if (length == 0) continue;

            int tmp_res;
            if (length == m - j && length == idx1 + 1) {
                // 不需要跳了
                tmp_res = i;
            } else {
                int have_len = m - (length + j);
                // i + length
                int s_idx = n - (i + length) - 1;
                if (s_idx >= 0 && pre_len[s_idx] >= have_len) {
                    int tmp = min(have_len, pre_eq_len);
                    tmp_res = i + 1 + s_idx + 1 + s_idx + 1 - have_len;
                } else {
                    tmp_res = 1e9;
                }
            }
            ans = min(ans, tmp_res);
        }
    }
    cout << ans << endl;
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
}
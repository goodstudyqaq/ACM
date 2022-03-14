#include <bits/stdc++.h>

using namespace std;

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string)s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template <size_t N>
string to_string(bitset<N> v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto& x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() {
    cerr << endl;
}

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

//SA[i]=a 排名为i的下标为a
//rank[a]=i 下标为a的排名为i
//height[i]=a 排名为i的和排名为i-1是最长公共前缀
//下标从1到N 千万不能搞错
#define rank rk
const int maxn = 2e5 + 5;
int ch[maxn];
int cntA[maxn], cntB[maxn], A[maxn], B[maxn], tsa[maxn], SA[maxn], rank[maxn], height[maxn];
int N;
void get_SA() {
    for (int i = 0; i <= 200; i++) cntA[i] = 0;
    for (int i = 1; i <= N; i++) cntA[ch[i]]++;
    for (int i = 1; i <= 200; i++) cntA[i] += cntA[i - 1];
    for (int i = N; i >= 1; i--) SA[cntA[ch[i]]--] = i;
    rank[SA[1]] = 1;
    for (int i = 2; i <= N; i++) {
        rank[SA[i]] = rank[SA[i - 1]];
        if (ch[SA[i]] != ch[SA[i - 1]])
            rank[SA[i]]++;
    }
    for (int step = 1; rank[SA[N]] < N; step <<= 1) {
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
}
void get_Height() {
    int i, j, k = 0;
    for (int i = 1; i <= N; i++) {
        if (k) k--;
        j = SA[rank[i] - 1];
        while (ch[i + k] == ch[j + k]) k++;
        height[rank[i]] = k;
    }
}

int minsum[maxn][20];

void RMQ(int num) {
    for (int j = 1; j < 20; j++)
        for (int i = 1; i <= num; i++)  //  注意i,j的顺序  先求小序列，再通过小序列求大序列.
            if (i + (1 << j) - 1 <= num) {
                minsum[i][j] = min(minsum[i][j - 1], minsum[i + (1 << (j - 1))][j - 1]);
            }
}

int qmin(int i, int j)  //查询
{
    int k = log2(j - i + 1);
    return min(minsum[i][k], minsum[j - (1 << k) + 1][k]);
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    string s, t;
    int x;
    cin >> n >> s >> m >> t >> x;
    string _s = s + "#" + t;
    for (int i = 0; i < _s.size(); i++) {
        ch[i + 1] = _s[i];
    }
    N = _s.size();
    debug(_s);
    get_SA();
    get_Height();
    for (int i = 1; i <= N; i++) {
        minsum[i][0] = height[i];
    }
    RMQ(N);

    vector<vector<int>> dp;
    dp.resize(n + 1, vector<int>(x + 1, -1));
    // dp[i][j] s 长度为 i 用了 j 次能匹配的最长长度
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= x; j++) {
            if (dp[i][j] >= 0) {
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                int mx_len = dp[i][j];
                if (mx_len < m && j < x) {
                    int idx1 = i + 1;
                    int idx2 = n + 1 + mx_len + 1;
                    int rk_idx1 = rank[idx1];
                    int rk_idx2 = rank[idx2];
                    int tmp1 = min(rk_idx1, rk_idx2);
                    int tmp2 = max(rk_idx1, rk_idx2);
                    int tmp = qmin(tmp1 + 1, tmp2);
                    dp[i + tmp][j + 1] = max(dp[i + tmp][j + 1], mx_len + tmp);
                }
            }
        }
    }
    debug(dp[10][2]);
    bool f = false;
    for (int i = 0; i <= x; i++) {
        if (dp[n][i] == m) {
            f = true;
        }
    }
    if (f) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
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

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> dp(n + 1, vector<int>(2));
    // dp[i][0] 处理完前 i 个数，将 i 加入递增序列后递减序列的最后一个值的最大值
    // dp[i][1] 处理完前 i 个数，将 i 加入递减序列后递增序列的最后一个值的最小值

    dp[1][0] = 1e9;
    dp[1][1] = -1e9;

    for (int i = 2; i <= n; i++) {
        dp[i][0] = -1e9;
        dp[i][1] = 1e9;
    }

    vector<vector<int>> pre(n + 1, vector<int>(2, -1));
    for (int i = 2; i <= n; i++) {
        bool f = false;
        if (a[i] > a[i - 1] && dp[i][0] < dp[i - 1][0]) {
            f = true;
            dp[i][0] = dp[i - 1][0];
            pre[i][0] = 0;
        }
        if (a[i] > dp[i - 1][1] && dp[i][0] < a[i - 1]) {
            f = true;
            dp[i][0] = a[i - 1];
            pre[i][0] = 1;
        }
        if (a[i] < a[i - 1] && dp[i][1] > dp[i - 1][1]) {
            f = true;
            dp[i][1] = dp[i - 1][1];
            pre[i][1] = 1;
        }
        if (a[i] < dp[i - 1][0] && dp[i][1] > a[i - 1]) {
            f = true;
            dp[i][1] = a[i - 1];
            pre[i][1] = 0;
        }
        if (!f) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    int now = n;
    int now_s = 0;
    if (pre[now][now_s] == -1) {
        now_s = 1;
    }
    vector<int> ans(n + 1);
    ans[now] = now_s;
    while (now != 1) {
        int lxt = pre[now][now_s];
        now--;
        ans[now] = lxt;
        now_s = lxt;
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
    return 0;
}
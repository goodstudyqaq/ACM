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

typedef pair<int, int> pii;
struct Node {
    int mi;
    vector<int> ans;
    int sum;
    Node() {}
    Node(string& s) {
        int n = s.size();
        mi = n + 1;
        int now = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                now++;
            } else {
                now--;
            }
            mi = min(mi, now);
        }
        sum = now;
        if (mi > 0) return;
        ans.resize(-mi + 1);
        vector<vector<int>> V;
        V.resize(-mi + 1);
        now = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(')
                now++;
            else {
                now--;
                if (now <= 0) {
                    int val = -now;
                    V[val].push_back(i);
                }
            }
        }

        int limit = n + 1;
        for (int i = -mi; i >= 0; i--) {
            int idx = upper_bound(V[i].begin(), V[i].end(), limit) - V[i].begin();
            ans[i] = idx;
            if (i > 0)
                limit = min(limit, V[i][0]);
        }
    }

    pii get_next(int val) {
        if (mi > 0) {
            return {0, 0};
        }
        bool f = 0;
        if (mi + val < 0) f = 1;
        if (mi + val > 0) return {0, f};
        return {ans[val], f};
    }

    int get_sum() {
        return sum;
    }
};
#define lowbit(x) x & -x

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<Node> nodes(n);
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        nodes[i - 1] = Node(s);
    }
    int LIMIT = 1 << n;
    vector<int> sum(LIMIT, 0);

    for (int i = 0; i < n; i++) {
        sum[1 << i] = nodes[i].get_sum();
    }

    for (int i = 1; i < LIMIT; i++) {
        int bi = lowbit(i);
        if (bi == i) continue;
        sum[i] = sum[i - bi] + sum[bi];
    }

    vector<int> dp(LIMIT, -1);
    dp[0] = 0;
    int res = 0;
    for (int i = 1; i < LIMIT; i++) {
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                int s = i - (1 << j);
                if (sum[s] >= 0 && dp[s] != -1) {
                    auto it = nodes[j].get_next(sum[s]);
                    res = max(res, dp[s] + it.first);
                    if (it.second == 0) {
                        dp[i] = max(dp[i], dp[s] + it.first);
                    }
                }
            }
        }
    }
    res = max(res, dp[LIMIT - 1]);
    cout << res << endl;
    return 0;
}
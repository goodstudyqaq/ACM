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
typedef array<int, 3> a3;
typedef array<int, 2> a2;
typedef pair<long long, a3> pa;
int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> v[4];
    for (int i = 1; i <= n; i++) {
        int w, c;
        cin >> w >> c;
        v[w].push_back(c);
    }

    for (int i = 1; i <= 3; i++) {
        sort(v[i].begin(), v[i].end());
        reverse(v[i].begin(), v[i].end());
    }

    vector<pa> dp;
    dp.resize(m + 1, {0, {0, 0, 0}});

    for (int i = 0; i <= m; i++) {
        if (i + 1 <= m) {
            int one_cnt = dp[i].second[0];
            if (one_cnt < v[1].size()) {
                if (dp[i + 1].first < dp[i].first + v[1][one_cnt]) {
                    dp[i + 1].first = dp[i].first + v[1][one_cnt];
                    dp[i + 1].second[0] = dp[i].second[0] + 1;
                    dp[i + 1].second[1] = dp[i].second[1];
                    dp[i + 1].second[2] = dp[i].second[2];
                }
            }
        }
        // if (i + 2 <= m) {
        //     int two_cnt = dp[i].second[1];
        //     if (two_cnt < v[2].size()) {
        //         if (dp[i + 2].first < dp[i].first + v[2][two_cnt]) {
        //             dp[i + 2].first = dp[i].first + v[2][two_cnt];
        //             dp[i + 2].second[0] = dp[i].second[0];
        //             dp[i + 2].second[1] = dp[i].second[1] + 1;
        //             dp[i + 2].second[2] = dp[i].second[2];
        //         }
        //     }
        // }
        if (i + 3 <= m) {
            int three_cnt = dp[i].second[2];
            if (three_cnt < v[3].size()) {
                if (dp[i + 3].first < dp[i].first + v[3][three_cnt]) {
                    dp[i + 3].first = dp[i].first + v[3][three_cnt];
                    dp[i + 3].second[0] = dp[i].second[0];
                    dp[i + 3].second[1] = dp[i].second[1];
                    dp[i + 3].second[2] = dp[i].second[2] + 1;
                }
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        debug(i, dp[i].first, dp[i].second);
        dp[i].first = max(dp[i].first, dp[i - 1].first);
    }

    // 枚举第二个
    int use_w = 0;
    long long use_ct = 0;
    long long res = 0;
    // 个数
    for (int i = 0; i <= v[2].size(); i++) {
        use_w = i * 2;
        if (use_w > m) break;
        if (i != 0)
            use_ct += v[2][i - 1];
        res = max(res, use_ct + dp[m - use_w].first);
    }

    // for (int i = 0; i <= m; i++) {
    //     res = max(res, dp[i].first);
    // }
    cout << res << endl;
    return 0;
}
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
int get_flag(string s) {
    if (s == "<=")
        return 1;
    else if (s == "<")
        return 2;
    else if (s == "=")
        return 3;
    else if (s == ">")
        return 4;
    else
        return 5;
}

typedef pair<int, int> pii;
vector<vector<pii>> V;

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    V.resize(n * 2 + 1);
    for (int i = 1; i <= k; i++) {
        int x, y;
        string s;
        cin >> x >> s >> y;
        int flag = get_flag(s);

        V[x].push_back({y, flag});
        V[y].push_back({x, 6 - flag});
    }

    vector<vector<long long>> dp;
    dp.resize(n * 2 + 1, vector<long long>(n * 2 + 1, 0));
    dp[0][0] = 1;
    // dp[i][j] 左边放 i 个 右边放 j 个的方案数

    auto ok = [&](int idx1, int idx2, int left, int right) {
        for (auto it : V[idx1]) {
            int tmp1 = it.first, tmp2 = it.second;
            if (tmp1 == idx1 || tmp1 == idx2) {
                if (tmp2 == 2 || tmp2 == 4)
                    return false;
                else
                    continue;
            }
            if (tmp2 == 5) {
                if (tmp1 >= left && tmp1 <= right) return false;
            } else if (tmp2 == 4) {
                if (tmp1 >= left && tmp1 <= right) return false;
            } else if (tmp2 == 3) {
                return false;
            } else if (tmp2 == 2) {
                if (tmp1 < left || tmp1 > right) return false;
            } else {
                if (tmp1 < left || tmp1 > right) return false;
            }
        }

        for (auto it : V[idx2]) {
            int tmp1 = it.first, tmp2 = it.second;
            if (tmp1 == idx1 || tmp1 == idx2) {
                if (tmp2 == 2 || tmp2 == 4)
                    return false;
                else
                    continue;
            }
            if (tmp2 == 5) {
                if (tmp1 >= left && tmp1 <= right) return false;
            } else if (tmp2 == 4) {
                if (tmp1 >= left && tmp1 <= right) return false;
            } else if (tmp2 == 3) {
                return false;
            } else if (tmp2 == 2) {
                if (tmp1 < left || tmp1 > right) return false;
            } else {
                if (tmp1 < left || tmp1 > right) return false;
            }
        }
        return true;
    };

    for (int i = 1; i <= n; i++) {
        int all = i * 2;
        for (int left = 0; left <= all; left++) {
            int right = all - left;
            if (left >= 2) {
                // dp[left - 2][right]
                // 放 left - 1, left 这两个位置, 左边占了 [1, left] 右边占了 [2 * n - right + 1, 2 * n]
                if (k == 0 || ok(left - 1, left, left + 1, 2 * n - right)) {
                    debug(i, left, right, 0);
                    dp[left][right] += dp[left - 2][right];
                }
            }
            if (left >= 1 && right >= 1) {
                // dp[left - 1][right - 1]
                if (k == 0 || ok(left, 2 * n - (right - 1), left + 1, 2 * n - right)) {
                    debug(i, left, right, 1);
                    dp[left][right] += dp[left - 1][right - 1];
                }
            }
            if (right >= 2) {
                if (k == 0 || ok(2 * n - (right - 2), 2 * n - (right - 1), left + 1, 2 * n - right)) {
                    debug(i, left, right, 2);
                    dp[left][right] += dp[left][right - 2];
                }
            }
        }
    }
    long long res = 0;
    for (int i = 0; i <= 2 * n; i++) {
        res += dp[i][2 * n - i];
    }
    debug(res);
    cout << res / 3 << endl;
    return 0;
}
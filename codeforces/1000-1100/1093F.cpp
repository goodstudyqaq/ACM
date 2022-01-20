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

const int mod = 998244353;
vector<int> a;

int n, k, len;
struct Node {
    vector<vector<int>> sum;
    // sum[i][j] 表示值为 i 长度为 j 的方案数
    // sum[i][0] = all_sum - sum2[i]

    int all_sum, zero_sum;
    // all_sum: sum2 的和
    // zero_sum: sum[i][0] 总和
    vector<int> sum2;
    // sum2[i] 为 sum[i][1] + sum[i][2] + ... + sum[i][len - 1]

    vector<int> offset;
    // 值为 i 的长度的偏移量

    void init(int val) {
        sum.resize(k + 1, vector<int>(n + 1, 0));
        all_sum = 0;
        zero_sum = 0;
        sum2.resize(k + 1, 0);
        if (val == -1) {
            offset.resize(k + 1, n - 1);
            all_sum = k;
            for (int i = 1; i <= k; i++) {
                sum[i][1 + offset[i]] = 1;
                sum[i][0 + offset[i]] = k - 1;
                (zero_sum += sum[i][0 + offset[i]]) %= mod;
                sum2[i] = 1;
            }
        } else {
            offset.resize(k + 1, n);
            offset[val]--;
            sum[val][1 + offset[val]] = 1;
            all_sum = 1;
            sum2[val] = 1;
            for (int i = 1; i <= k; i++) {
                if (i == val) continue;
                sum[i][0 + offset[i]] = 1;
                (zero_sum += sum[i][0 + offset[i]]) %= mod;
            }
            debug(sum, all_sum, zero_sum, sum2, offset);
        }
    }

    void work(int val) {
        if (val == -1) {
            int tmp = 0;
            for (int i = 1; i <= k; i++) {
                offset[i]--;
                sum[i][0 + offset[i]] = (((all_sum + zero_sum) % mod - sum2[i]) % mod - sum[i][1 + offset[i]]) % mod;
                if (len + offset[i] <= n) {
                    (tmp += sum[i][len + offset[i]]) %= mod;
                    (sum2[i] -= sum[i][len + offset[i]]) %= mod;
                }
            }

            for (int i = 1; i <= k; i++) {
                sum[i][0 + offset[i]] = (sum[i][0 + offset[i]] - tmp) % mod;
                if (len + offset[i] <= n) {
                    (sum[i][0 + offset[i]] += sum[i][len + offset[i]]) %= mod;
                    sum[i][len + offset[i]] = 0;
                }
            }

            (all_sum += zero_sum) %= mod;
            (all_sum -= tmp) %= mod;
            zero_sum = 0;
            for (int i = 1; i <= k; i++) {
                (zero_sum += sum[i][0 + offset[i]]) %= mod;
                (sum2[i] += sum[i][1 + offset[i]]) %= mod;
            }
        } else {
            offset[val]--;
            sum[val][0 + offset[val]] = 0;
            sum2[val] = all_sum;
            zero_sum = 0;

            if (len + offset[val] <= n) {
                (sum2[val] -= sum[val][len + offset[val]]) %= mod;
                (all_sum -= sum[val][len + offset[val]]) %= mod;
                sum[val][len + offset[val]] = 0;
            }

            // 更新其他值
            for (int i = 1; i <= k; i++) {
                if (i == val) continue;
                offset[i] = n;
                sum[i][0 + offset[i]] = all_sum;
                (zero_sum += sum[i][0 + offset[i]]) %= mod;
                sum2[i] = 0;
            }
        }

        debug(sum, all_sum, zero_sum, sum2, offset);
    }

    int output() {
        int res = 0;
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j <= len && j + offset[i] <= n; j++) {
                res = (res + sum[i][j + offset[i]]) % mod;
            }
        }
        res = (res + mod) % mod;
        return res;
    }
};

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k >> len;

    Node node;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (i == 1) {
            node.init(a[i]);
        } else {
            node.work(a[i]);
        }
    }
    if (len == 1) {
        cout << 0 << endl;
        return 0;
    }
    debug("zz");
    cout << node.output() << endl;
    return 0;
}
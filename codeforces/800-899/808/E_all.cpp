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

map<int, vector<int>> v;
map<int, vector<long long>> sum_v;
int a, b;

long long work2_two(int w, int two_num) {
    long long val1 = 0;
    if (two_num > 0) {
        val1 = sum_v[b][two_num - 1];
    }
    int left_w = w - two_num * b;
    int one_num = left_w / a;
    one_num = min(one_num, int(v[a].size()));
    long long val2 = 0;
    if (one_num > 0) {
        val2 = sum_v[a][one_num - 1];
    }
    // debug(one_num, two_num, val1 + val2);
    return val1 + val2;
}

long long work_force(int w) {
    long long res = 0;
    int l = 0, r = min(int(v[b].size()), w / b);
    for (int i = l; i <= r; i++) {
        // debug(i, work2_two(w, i));
        res = max(res, work2_two(w, i));
    }
    return res;
}

long long work_two(int w) {
    // 假算法
    int l = 0, r = min(int(v[b].size()), w / b);
    while (r - l > 4) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        long long v1 = work2_two(w, m1);
        long long v2 = work2_two(w, m2);
        if (v1 < v2) {
            l = m1;
        } else {
            r = m2;
        }
    }
    long long res = 0, chose_idx;
    for (int i = l; i <= r; i++) {
        long long val = work2_two(w, i);
        if (res < val) {
            res = val;
            chose_idx = i;
        }
    }
    // debug(l, r);
    // debug(res, chose_idx);
    return res;
}

long long work_dp(int w) {
    vector<pa> dp;
    dp.resize(w + 1);

    dp[0] = {0, {0, 0, 0}};
    for (int i = 0; i <= w; i++) {
        int one_num = dp[i].second[0];
        int two_num = dp[i].second[1];
        if (i + a <= w) {
            if (one_num < v[a].size()) {
                if (dp[i + a].first < dp[i].first + v[a][one_num]) {
                    dp[i + a].first = dp[i].first + v[a][one_num];
                    dp[i + a].second[0] = one_num + 1;
                    dp[i + a].second[1] = two_num;
                }
            }
        }
        if (i + b <= w) {
            if (two_num < v[b].size()) {
                if (dp[i + b].first < dp[i].first + v[b][two_num]) {
                    dp[i + b].first = dp[i].first + v[b][two_num];
                    dp[i + b].second[0] = one_num;
                    dp[i + b].second[1] = two_num + 1;
                }
            }
        }
    }
    long long res = 0;
    int chose_idx = -1;
    for (int i = 0; i <= w; i++) {
        if (res < dp[i].first) {
            res = dp[i].first;
            chose_idx = dp[i].second[1];
        }
        res = max(res, dp[i].first);
    }
    // debug(res, chose_idx);
    // debug(work2_two(w, chose_idx));

    return res;
}

int main() {
    // #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    // #endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int w, c;
        cin >> w >> c;
        v[w].push_back(c);
    }
    a = v.begin()->first;
    b = v.rbegin()->first;
    // debug(a, b);
    for (auto it : v) {
        sort(v[it.first].begin(), v[it.first].end());
        reverse(v[it.first].begin(), v[it.first].end());
    }

    for (auto it : v) {
        sum_v[it.first].resize(v[it.first].size());
        for (int j = 0; j < v[it.first].size(); j++) {
            if (j == 0) {
                sum_v[it.first][j] = v[it.first][j];
            } else {
                sum_v[it.first][j] = v[it.first][j] + sum_v[it.first][j - 1];
            }
        }
    }

    long long res = work_force(m);
    // long long res = work_two(m);
    // long long res = work_dp(m);
    cout << res << endl;
    // return 0;
}
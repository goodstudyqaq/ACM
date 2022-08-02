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

vector<int> a;

vector<vector<vector<int>>> dp;
int get_idx(int left, int right, int k) {
    int ans = -1;
    int l = left + k + 1;
    int r = right;
    while (l <= r) {
        int mid = l + r >> 1;
        if (dp[left][mid][k - 1] > a[right] - a[mid]) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int n, m;
void init() {
    dp.resize(n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1)));
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            for (int k = 0; k <= j - i - 1; k++) {
                if (k == 0) {
                    dp[i][j][k] = a[j] - a[i];
                    continue;
                }
                int idx = get_idx(i, j, k);
                dp[i][j][k] = max(dp[i][idx][k - 1], a[j] - a[idx]);
                if (idx - 1 >= i) {
                    idx--;
                    dp[i][j][k] = min(dp[i][j][k], max(dp[i][idx][k - 1], a[j] - a[idx]));
                }
                // debug(i, j, k, dp[i][j][k]);
            }
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#else
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    init();

    long long ans = 0;
    for (int i = 1; i <= m; i++) {
        int s, f, c, r;
        cin >> s >> f >> c >> r;
        r = min(r, f - s - 1);
        int tmp = dp[s][f][r];
        debug(i, tmp, s, f, r, tmp * c);
        ans = max(ans, 1LL * tmp * c);
    }
    cout << ans << endl;
    return 0;
}
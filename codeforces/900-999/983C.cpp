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

vector<int> a, b;

vector<map<int, vector<int>>> dp;

int n;

int get_status(vector<int> v, int val) {
    v.push_back(val);
    while (v.size() < 4) {
        v.push_back(0);
    }
    sort(v.begin(), v.end());
    int res = 0;
    for (int i = 0; i < 4; i++) {
        res = res * 10 + v[i];
    }
    return res;
}

int get_status2(vector<int> v, int idx) {
    int res = 0;
    for (int i = 0; i < v.size(); i++) {
        if (i == idx) continue;
        res = res * 10 + v[i];
    }
    return res;
}

int dfs(int floor, int status, int idx) {
    if (status == 0 && idx == n + 1) return 0;
    if (dp[floor].count(status) && dp[floor][status][idx] != -1) return dp[floor][status][idx];

    if (!dp[floor].count(status)) {
        dp[floor][status].resize(n + 2, -1);
    }

    vector<int> go;
    int s2 = status;
    while (s2) {
        if (s2 % 10)
            go.push_back(s2 % 10);
        s2 /= 10;
    }

    sort(go.begin(), go.end());
    int num = go.size();

    int res = 1e9;
    if (num < 4 && idx <= n) {
        // 可以搞 idx
        int tmp1 = a[idx], tmp2 = b[idx];
        int val = abs(floor - tmp1) + 1;
        int new_status = get_status(go, tmp2);
        res = min(res, val + dfs(tmp1, new_status, idx + 1));
    }

    for (int i = 0; i < num; i++) {
        int new_status = get_status2(go, i);
        int val = abs(floor - go[i]) + 1;
        res = min(res, val + dfs(go[i], new_status, idx));
    }
    return dp[floor][status][idx] = res;
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    a.resize(n + 1);
    b.resize(n + 1);
    dp.resize(10);
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }
    cout << dfs(1, 0, 1) << endl;
    return 0;
}
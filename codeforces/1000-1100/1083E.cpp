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

struct Node {
    long long x, y, a;
    bool operator<(const Node& a) const {
        return x < a.x;
    }
};

vector<Node> V;

vector<long long> dp;
long long getk(int idx) {
    return V[idx].y;
}

long long getup(int idx1, int idx2) {
    return dp[idx2] - dp[idx1];
}

long long getdown(int idx1, int idx2) {
    return V[idx2].x - V[idx1].x;
}

double getslope(int idx1, int idx2) {
    return 1.0 * getup(idx1, idx2) / (1.0 * getdown(idx1, idx2));
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;

    V.resize(n + 1);
    dp.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        long long x, y, a;
        cin >> x >> y >> a;
        V[i] = (Node){x, y, a};
    }
    V[0] = (Node){0, 0, 0};
    sort(V.begin(), V.begin() + 1 + n);

    vector<int> Q(n + 1);
    int first = 0, tail = 0;  // 左闭右闭
    Q[tail] = 0;
    dp[0] = 0;
    long long res = dp[0];
    for (int i = 1; i <= n; i++) {
        while (first < tail && getslope(Q[first], Q[first + 1]) >= getk(i)) {
            first++;
        }
        dp[i] = dp[Q[first]] + 1LL * (V[i].x - V[Q[first]].x) * V[i].y - V[i].a;
        while (first < tail && getslope(Q[tail], i) >= getslope(Q[tail - 1], Q[tail])) {
            tail--;
        }
        Q[++tail] = i;
        res = max(res, dp[i]);
    }
    cout << res << endl;
    return 0;
}
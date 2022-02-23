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

#define lowbit(x) x & -x
const int maxn = 1e6 + 5;
long long sum[maxn];
void add(int idx, long long val) {
    while (idx < maxn) {
        sum[idx] += val;
        idx += lowbit(idx);
    }
}

long long query(int idx) {
    long long res = 0;
    while (idx) {
        res += sum[idx];
        idx -= lowbit(idx);
    }
    return res;
}

struct Node {
    int l, r, color;
    bool operator<(const Node& b) const {
        return l < b.l;
    }
};
set<Node> S;
vector<long long> colorSum;
const int inf = 1e9;

void Cut(int idx) {
    auto it = S.upper_bound((Node){idx, inf, 0});
    it--;
    // it 包含 l
    int l = it->l, r = it->r, c = it->color;
    S.erase(it);
    if (l < idx) {
        S.insert((Node){l, idx - 1, c});
    }
    S.insert((Node){idx, r, c});
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    colorSum.resize(n + 1, 0);
    S.insert((Node){1, n + 1, 1});
    while (q--) {
        string s;
        cin >> s;
        if (s[0] == 'C') {
            int l, r, color;
            cin >> l >> r >> color;
            Cut(l);
            Cut(r + 1);
            Node node = (Node){l, r, color};
            auto it = S.upper_bound(node);
            it--;
            while (it->r <= r) {
                int c = it->color;
                add(it->l, colorSum[c]);
                add(it->r + 1, -colorSum[c]);
                S.erase(it);
                it = S.upper_bound(node);
            }
            add(l, -colorSum[color]);
            add(r + 1, colorSum[color]);
            S.insert(node);
        } else if (s[0] == 'A') {
            int c, x;
            cin >> c >> x;
            colorSum[c] += x;
        } else {
            int idx;
            cin >> idx;
            auto it = S.upper_bound((Node){idx, inf, 0});
            it--;
            cout << colorSum[it->color] + query(idx) << '\n';
        }
    }
    return 0;
}
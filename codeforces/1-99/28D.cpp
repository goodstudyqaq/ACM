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
    int v, c, l, r;
};

int main() {
#ifdef LOCAL
    freopen("./data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<Node> nodes;
    nodes.resize(n + 1);

    vector<int> f;
    f.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> nodes[i].v >> nodes[i].c >> nodes[i].l >> nodes[i].r;
        f[i] = i;
    }

    auto get_val = [&](int idx) {
        return nodes[idx].c + nodes[idx].l + nodes[idx].r;
    };

    auto cmp = [&](int a, int b) {
        int tmp1 = get_val(a);
        int tmp2 = get_val(b);
        if (tmp1 != tmp2) {
            return tmp1 < tmp2;
        }
        return a < b;
    };
    sort(f.begin() + 1, f.begin() + 1 + n, cmp);
    int now = 1;
    vector<int> dp, path;
    dp.resize(n + 1);
    path.resize(n + 1);
    int res = -1;
    while (now <= n) {
        int go = now;
        while (go <= n && get_val(f[go]) == get_val(f[now])) {
            go++;
        }

        map<int, int> M;
        for (int i = go - 1; i >= now; i--) {
            int idx = f[i];
            int tmp = nodes[idx].c + nodes[idx].l;
            if (M.count(tmp)) {
                int idx2 = M[tmp];
                dp[idx] = dp[idx2] + nodes[idx].v;
                path[idx] = idx2;
            } else {
                if (nodes[idx].r == 0) {
                    dp[idx] = nodes[idx].v;
                } else {
                    dp[idx] = 0;
                }
            }
            tmp = nodes[idx].l;
            if (M.count(tmp)) {
                if (dp[idx] > dp[M[tmp]]) {
                    M[tmp] = idx;
                }
            } else {
                if (dp[idx]) {
                    M[tmp] = idx;
                }
            }

            if (nodes[idx].l == 0 && dp[idx] > 0) {
                if (res == -1 || dp[res] < dp[idx]) {
                    res = idx;
                }
            }
        }
        now = go;
    }

    if (res == -1) {
        cout << 0 << endl;
        return 0;
    }

    now = res;
    vector<int> ans;
    while (now) {
        ans.push_back(now);
        now = path[now];
    }
    cout << ans.size() << endl;
    for (auto it : ans) {
        cout << it << ' ';
    }
    cout << endl;
    return 0;
}
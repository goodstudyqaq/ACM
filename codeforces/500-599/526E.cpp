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

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> a(n * 2);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }

    vector<int> go(n);
    while (q--) {
        long long b;
        cin >> b;

        long long now_val = 0, now_idx = 0;
        for (int i = 0; i < n; i++) {
            while (now_idx < n * 2 && now_val + a[now_idx] <= b) {
                now_val += a[now_idx];
                now_idx++;
            }
            go[i] = now_idx;
            now_val -= a[i];
        }

        int chose_idx = 0;
        for (int i = 0; i < n; i++) {
            if (go[i] - i < go[chose_idx] - chose_idx) {
                chose_idx = i;
            }
        }
        debug(chose_idx, go[chose_idx]);

        int res = n + 1;
        for (int i = chose_idx; i <= go[chose_idx]; i++) {
            int tmp = 0;
            int begin = i % n;
            int now_idx = begin;
            bool f = false;
            while (now_idx < begin + n) {
                int nxt_go = go[now_idx % n];
                if (nxt_go >= n) {
                    f = true;
                }
                if (nxt_go < n && f) {
                    nxt_go += n;
                }
                now_idx = nxt_go;
                tmp++;
            }
            res = min(res, tmp);
        }
        cout << res << '\n';
    }
    return 0;
}

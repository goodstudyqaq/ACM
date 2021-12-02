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

const int mod = 1e9 + 7;
vector<int> a;
const int MAXL = 20, L = 19;
const int maxn = 1e5 + 1;

struct LinearBasis {
    int a[MAXL];
    int cnt;
    LinearBasis() {
        fill(a, a + MAXL, 0);
        cnt = 0;
    }

    void insert(int t) {
        for (int j = L; j >= 0; j--) {
            if (!t) return;
            if (!(t & (1 << j))) continue;
            if (a[j])
                t ^= a[j];
            else {
                for (int k = 0; k < j; k++)
                    if (t & (1 << k)) t ^= a[k];
                for (int k = j + 1; k < MAXL; k++)
                    if (a[k] & (1 << j)) a[k] ^= t;
                a[j] = t;
                cnt++;
                return;
            }
        }
    }

    bool query(int t) {
        for (int j = L; j >= 0; j--) {
            if (!(t & (1 << j))) continue;
            if (a[j] == 0) return false;
            t ^= a[j];
        }
        return true;
    }
} lb[maxn];

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        lb[i] = lb[i - 1];
        lb[i].insert(a[i]);
    }
    int two = 1;
    vector<int> t;
    t.resize(n + 1);
    for (int i = 0; i <= n; i++) {
        t[i] = two;
        two = 1LL * two * 2 % mod;
    }

    for (int i = 1; i <= q; i++) {
        int l, x;
        cin >> l >> x;
        if (lb[l].query(x)) {
            cout << t[l - lb[l].cnt] << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
    return 0;
}
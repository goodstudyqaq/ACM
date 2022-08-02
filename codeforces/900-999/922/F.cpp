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
    int n, k;
    cin >> n >> k;

    int m = -1;
    int cnt = 0;
    vector<int> num(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = i + i; j <= n; j += i) {
            num[j]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        cnt += num[i];
        if (cnt >= k) {
            m = i;
            break;
        }
    }
    if (m == -1) {
        cout << "No" << endl;
        return 0;
    }

    vector<int> f(m + 1);
    for (int i = 1; i <= m; i++) {
        f[i] = i;
    }
    auto cmp = [&](int a, int b) {
        return num[a] > num[b];
    };
    sort(f.begin() + 1, f.begin() + 1 + m, cmp);
    vector<int> vis(m + 1, 1);
    int ans_num = m;

    debug(m, cnt);
    for (int i = 1; i <= m; i++) {
        int idx = f[i];
        if (idx > m / 2 && cnt - num[idx] >= k) {
            debug(idx);
            vis[idx] = 0;
            ans_num--;
            cnt -= num[idx];
        }
        if (cnt == k) break;
    }
    cout << "Yes" << endl;
    cout << ans_num << endl;
    for (int i = 1; i <= m; i++) {
        if (vis[i]) {
            cout << i << ' ';
        }
    }
    cout << endl;
    return 0;
}
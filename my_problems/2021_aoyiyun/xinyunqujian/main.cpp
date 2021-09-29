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

// 复杂度 O(n * log(1e14)) ~= O(46n)
const int maxn = 1e5 + 1;

int main() {
#ifdef LOCAL
    freopen("data1.in", "r", stdin);
    freopen("data1.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    // 挑出所有不是 1 的点
    vector<int> no_one_idx;
    vector<long long> sum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] != 1) {
            no_one_idx.push_back(i);
        }
        sum[i] = sum[i - 1] + a[i];
    }
    no_one_idx.push_back(n + 1);
    int the_no_one_idx = 0;

    int res = n;
    for (int i = 1; i <= n; i++) {
        long long now_sum = a[i];
        long long now_mul = a[i];
        if (a[i] != 1) {
            the_no_one_idx++;
            if (the_no_one_idx >= no_one_idx.size() - 1) break;
        }
        int now = the_no_one_idx;
        while (now < no_one_idx.size() - 1) {
            int the_idx = no_one_idx[now];
            now_sum = sum[the_idx] - sum[i - 1];
            now_mul = now_mul * a[the_idx];
            if (now_mul > sum[n]) break;

            if (now_mul == now_sum) {
                res++;
            } else if (now_mul > now_sum) {
                int nxt_idx = now + 1;
                nxt_idx = no_one_idx[nxt_idx] - 1;
                long long tmp = sum[nxt_idx] - sum[i - 1];
                if (tmp >= now_mul) {
                    res++;
                }
            }
            now++;
        }
    }
    cout << res << endl;
    return 0;
}
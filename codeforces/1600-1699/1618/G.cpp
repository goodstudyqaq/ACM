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

vector<multiset<int>> A, B;
typedef pair<int, int> pii;
vector<pii> V;

struct Event {
    bool flag;
    int t, idx;
    bool operator<(const Event& e) const {
        if (t != e.t) {
            return t < e.t;
        }
        return flag < e.flag;
    }
};
long long sum;
vector<int> f;
int find(int u) {
    return u == f[u] ? u : f[u] = find(f[u]);
}

void work(int idx) {
    int fu = find(idx);
    int fv = find(idx + 1);

    if (A[fu].size() + B[fu].size() > A[fv].size() + B[fv].size()) {
        swap(fu, fv);
    }
    // 把 fu 的数据迁到 fv
    for (auto it : A[fu]) {
        A[fv].insert(it);
    }
    for (auto it : B[fu]) {
        B[fv].insert(it);
    }
    while (A[fv].size() && B[fv].size() && *A[fv].begin() < *B[fv].rbegin()) {
        sum += *B[fv].rbegin() - *A[fv].begin();
        A[fv].insert(*B[fv].rbegin());
        B[fv].insert(*A[fv].begin());
        A[fv].erase(A[fv].begin());
        B[fv].erase(prev(B[fv].end()));
    }
    A[fu].clear();
    B[fu].clear();
    f[fu] = fv;
}

int main() {
#ifdef LOCAL
    freopen("data.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        V.push_back({a, 1});
        sum += a;
    }
    for (int i = 1; i <= m; i++) {
        int b;
        cin >> b;
        V.push_back({b, 0});
    }
    sort(V.begin(), V.end());
    A.resize(V.size());
    B.resize(V.size());

    f.resize(V.size());
    for (int i = 0; i < V.size(); i++) {
        f[i] = i;
    }

    vector<Event> event;
    for (int i = 0; i < V.size(); i++) {
        if (V[i].second == 1) {
            A[i].insert(V[i].first);
        } else {
            B[i].insert(V[i].first);
        }
        if (i + 1 < V.size())
            event.push_back((Event){0, V[i + 1].first - V[i].first, i});
    }

    for (int i = 1; i <= q; i++) {
        int k;
        cin >> k;
        event.push_back((Event){1, k, i});
    }

    sort(event.begin(), event.end());
    vector<long long> ans(q + 1);

    for (int i = 0; i < event.size(); i++) {
        if (event[i].flag == 0) {
            work(event[i].idx);
        } else {
            ans[event[i].idx] = sum;
        }
    }

    for (int i = 1; i <= q; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}
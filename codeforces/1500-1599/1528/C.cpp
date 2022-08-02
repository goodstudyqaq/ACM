#include <bits/stdc++.h>

using namespace std;

template < typename A, typename B >
string to_string(pair< A, B > p);

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p);

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p);

string to_string(const string& s) {
	return '"' + s + '"';
}

string to_string(const char* s) {
	return to_string(( string )s);
}

string to_string(bool b) {
	return (b ? "true" : "false");
}

string to_string(vector< bool > v) {
	bool first = true;
	string res = "{";
	for (int i = 0; i < static_cast< int >(v.size()); i++) {
		if (!first) {
			res += ", ";
		}
		first = false;
		res += to_string(v[i]);
	}
	res += "}";
	return res;
}

template < size_t N >
string to_string(bitset< N > v) {
	string res = "";
	for (size_t i = 0; i < N; i++) {
		res += static_cast< char >('0' + v[i]);
	}
	return res;
}

template < typename A >
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

template < typename A, typename B >
string to_string(pair< A, B > p) {
	return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template < typename A, typename B, typename C >
string to_string(tuple< A, B, C > p) {
	return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ")";
}

template < typename A, typename B, typename C, typename D >
string to_string(tuple< A, B, C, D > p) {
	return "(" + to_string(get< 0 >(p)) + ", " + to_string(get< 1 >(p)) + ", " + to_string(get< 2 >(p)) + ", " + to_string(get< 3 >(p)) + ")";
}

void debug_out() {
	cerr << endl;
}

template < typename Head, typename... Tail >
void debug_out(Head H, Tail... T) {
	cerr << " " << to_string(H);
	debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

vector< vector< int > > g1, g2;

int idx;
vector< int > L, R;
void dfs2(int u) {
	L[u] = ++idx;
	for (auto it : g2[u]) {
		dfs2(it);
	}
	R[u] = idx;
}
int ans, now;

typedef pair< int, int > pii;
set< pii > S;

bool check(int idx1, int idx2) {
	// 判断 idx2 是否是 idx1 的孩子
	return L[idx1] <= L[idx2] && R[idx1] >= R[idx2];
}

void add(int idx) {
	if (S.empty()) {
		now++;
	} else {
		auto it = S.lower_bound({ L[idx], 0 });
		if (it == S.begin()) {
			if (!check(idx, it->second)) {
				now++;
			}
		} else if (it == S.end()) {
			it--;
			if (!check(it->second, idx)) {
				now++;
			}
		} else {
			auto it2 = it;
			it2--;
			bool f1 = check(it2->second, idx);
			bool f2 = check(idx, it->second);
			bool f3 = check(it2->second, it->second);

			if (!f1 && !f2) {
				now++;
			} else if (f1 && !f2) {
				if (f3) now++;
			}
		}
	}
	S.insert({ L[idx], idx });
}

void del(int idx) {
	S.erase({ L[idx], idx });
}

void dfs1(int u) {
	int tmp = now;
	add(u);
	ans = max(ans, now);
	for (auto it : g1[u]) {
		dfs1(it);
	}
	del(u);
	now = tmp;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		S.clear();
		L.resize(n + 1);
		R.resize(n + 1);
		g1.resize(n + 1);
		g2.resize(n + 1);
		for (int i = 1; i <= n; i++) {
			g1[i].clear();
			g2[i].clear();
		}
		idx = 0;
		for (int i = 2; i <= n; i++) {
			int a;
			cin >> a;
			g1[a].push_back(i);
		}
		for (int i = 2; i <= n; i++) {
			int a;
			cin >> a;
			g2[a].push_back(i);
		}
		dfs2(1);
		ans = 0, now = 0;
		dfs1(1);
		cout << ans << '\n';
	}
	return 0;
}
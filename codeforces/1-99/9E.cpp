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

typedef pair< int, int > pii;
vector< vector< pii > > V;
vector< int > vis;

int rt;
vector< int > f;
void dfs(int u, int e_idx) {
	vis[u] = 1;
	f[u] = rt;
	for (auto e : V[u]) {
		if (e.second == e_idx) continue;
		dfs(e.first, e.second);
	}
}
int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	V.resize(n + 1);
	vis.resize(n + 1, 0);
	f.resize(n + 1);
	bool self_circle = false;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		if (u == v) {
			self_circle = true;
		}
		V[u].push_back({ v, i });
		V[v].push_back({ u, i });
	}

	if (self_circle) {
		if (n > 1) {
			cout << "NO" << endl;
			return 0;
		}
		if (m > 1) {
			cout << "NO" << endl;
			return 0;
		}
		cout << "YES" << endl;
		cout << 0 << endl;
		return 0;
	}

	for (int i = 1; i <= n; i++) {
		if (V[i].size() > 2) {
			cout << "NO" << endl;
			return 0;
		}
	}

	for (int i = 1; i <= n; i++) {
		if (!vis[i] && V[i].size() <= 1) {
			rt = i;
			dfs(i, 0);
		}
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			cnt++;
		}
	}

	if (cnt == n) {
		cout << "YES" << endl;
		cout << 0 << endl;
		return 0;
	} else if (cnt > 0) {
		cout << "NO" << endl;
		return 0;
	}

	priority_queue< pii, vector< pii >, greater< pii > > Q;
	for (int i = 1; i <= n; i++) {
		if ((V[i].size() == 1 && f[i] != i) || V[i].size() == 0) {
			int u = f[i], v = i;
			if (u > v) swap(u, v);
			Q.push({ u, v });
		}
	}

	vector< pii > ans;
	while (Q.size() > 1) {
		auto it1 = Q.top();
		Q.pop();
		auto it2 = Q.top();
		Q.pop();

		ans.push_back({ it1.first, it2.first });
		pii it3 = { it1.second, it2.second };
		if (it3.first > it3.second) {
			swap(it3.first, it3.second);
		}
		Q.push(it3);
	}

	auto it = Q.top();
	ans.push_back(it);

	cout << "YES" << endl;
	cout << ans.size() << endl;
	for (auto it : ans) {
		cout << it.first << ' ' << it.second << '\n';
	}
	return 0;
}
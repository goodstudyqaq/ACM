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
vector< pii > edges;

vector< int > f;

int find(int u) {
	return u == f[u] ? u : f[u] = find(f[u]);
}

int s, t, ds, dt;
bool check(int u) {
	if (s == u) return false;
	if (t == u) return false;
	return true;
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	edges.resize(m + 1);
	f.resize(n + 1);
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		if (u > v) swap(u, v);	// u < v
		edges[i] = { u, v };
	}
	cin >> s >> t >> ds >> dt;
	if (s > t) {
		swap(s, t);
		swap(ds, dt);
	}
	// s < t

	vector< pii > ans;
	vector< bool > vis(m + 1, false);
	// 先处理没有 s t 的边
	for (int i = 1; i <= n; i++) {
		f[i] = i;
	}

	for (int i = 1; i <= m; i++) {
		if (check(edges[i].first) && check(edges[i].second)) {
			int u = edges[i].first, v = edges[i].second;
			int fu = find(u), fv = find(v);
			if (fu != fv) {
				ans.push_back(edges[i]);
				vis[i] = true;
				f[fu] = fv;
			}
		}
	}

	vector< vector< int > > v2;
	v2.resize(n + 1, vector< int >(2, -1));

	int have = -1;
	unordered_set< int > node_idx;
	for (int i = 1; i <= m; i++) {
		if (check(edges[i].first) && check(edges[i].second)) continue;
		if (edges[i].first == s && edges[i].second == t) {
			have = i;
			continue;
		}

		if (edges[i].first == s || edges[i].first == t) {
			int fv = find(edges[i].second);
			if (edges[i].first == s) {
				v2[fv][0] = i;
			} else {
				v2[fv][1] = i;
			}
			node_idx.insert(fv);
		} else if (edges[i].second == s || edges[i].second == t) {
			int fu = find(edges[i].first);
			if (edges[i].second == s) {
				v2[fu][0] = i;
			} else {
				v2[fu][1] = i;
			}
			node_idx.insert(fu);
		}
	}
	debug(node_idx.size());
	for (auto it : node_idx) {
		int num = 0;
		if (v2[it][0] != -1) num++;
		if (v2[it][1] != -1) num++;
		debug(it, num);
		if (num == 1) {
			int chose = -1;
			if (v2[it][0] != -1) {
				chose = v2[it][0];
				ans.push_back(edges[chose]);
				vis[chose] = true;
				ds--;
				if (ds < 0) {
					cout << "No" << endl;
					return 0;
				}
			} else {
				chose = v2[it][1];
				ans.push_back(edges[chose]);
				vis[chose] = true;
				dt--;
				if (dt < 0) {
					cout << "No" << endl;
					return 0;
				}
			}
		}
	}
	debug(ds, dt);
	// debug("zz");
	for (auto it : node_idx) {
		int num = 0;
		if (v2[it][0] != -1) num++;
		if (v2[it][1] != -1) num++;
		if (num == 2) {
			if (ds > dt) {
				ds--;
				int chose = v2[it][0];
				ans.push_back(edges[chose]);
				vis[chose] = true;
				if (ds < 0) {
					cout << "No" << endl;
					return 0;
				}
			} else {
				dt--;
				int chose = v2[it][1];
				ans.push_back(edges[chose]);
				vis[chose] = true;
				if (dt < 0) {
					cout << "No" << endl;
					return 0;
				}
			}
		}
	}

	auto out = [&]() {
		cout << "Yes" << '\n';
		for (auto it : ans) {
			cout << it.first << ' ' << it.second << '\n';
		}
	};

	debug(ds, dt);
	debug(have);
	// 还要选一条边
	if (have != -1 && ds > 0 && dt > 0) {
		ans.push_back(edges[have]);
		vis[have] = true;
		out();
		return 0;
	}
	if (ds > 0) {
		bool f = false;
		for (auto it : node_idx) {
			int num = 0;
			if (v2[it][0] != -1) num++;
			if (v2[it][1] != -1) num++;
			if (num == 2 && vis[v2[it][0]] == 0) {
				ans.push_back(edges[v2[it][0]]);
				f = true;
				break;
			}
		}
		if (f) {
			out();
			return 0;
		}
	}

	if (dt > 0) {
		bool f = false;
		for (auto it : node_idx) {
			int num = 0;
			if (v2[it][0] != -1) num++;
			if (v2[it][1] != -1) num++;
			if (num == 2 && vis[v2[it][1]] == 0) {
				ans.push_back(edges[v2[it][1]]);
				f = true;
				break;
			}
		}
		if (f) {
			out();
			return 0;
		}
	}
	cout << "No" << endl;
	return 0;
}
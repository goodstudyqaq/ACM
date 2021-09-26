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

int n, m, k;
string convert(string& s) {
	string res = "";
	for (int i = s.size() - 1; i >= 0; i--) {
		res += s[i];
	}
	return res;
}

vector< int > f, sz;
int find(int u) {
	return u == f[u] ? u : f[u] = find(f[u]);
}
vector< string > s;

int check(int a, int b) {
	int cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < m; i++) {
		if (s[a][i] == s[b][i]) cnt1++;
		if (s[a][i] == s[b + n][i]) cnt2++;
	}
	int f1 = cnt1 >= k;
	int f2 = cnt2 >= k;
	return f1 * 2 + f2;
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
		cin >> n >> m >> k;
		s.resize(n * 2 + 1);
		f.resize(n * 2 + 1);
		sz.resize(n * 2 + 1);
		for (int i = 1; i <= n; i++) {
			cin >> s[i];
			s[i + n] = convert(s[i]);
		}

		for (int i = 1; i <= 2 * n; i++) {
			f[i] = i;
			sz[i] = (i > n);
		}

		bool can = true;
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				int flag = check(i, j);
				if (flag == 0) {
					// debug(i, j);
					can = false;
					i = n + 1;
					break;
				} else if (flag == 1) {
					int f1 = find(i), f2 = find(j + n);
					if (f1 != f2) {
						f[f1] = f2;
						sz[f2] += sz[f1];
					}
					f1 = find(i + n), f2 = find(j);
					if (f1 != f2) {
						f[f1] = f2;
						sz[f2] += sz[f1];
					}
				} else if (flag == 2) {
					int f1 = find(i), f2 = find(j);
					if (f1 != f2) {
						f[f1] = f2;
						sz[f2] += sz[f1];
					}
					f1 = find(i + n);
					f2 = find(j + n);
					if (f1 != f2) {
						f[f1] = f2;
						sz[f2] += sz[f1];
					}
				} else {
					continue;
				}
			}
		}
		if (!can) {
			cout << -1 << endl;
			continue;
		}

		vector< int > vis(n * 2 + 1, 0);
		vector< int > ans;
		for (int i = 1; i <= n; i++) {
			int f1 = find(i);
			int f2 = find(i + n);
			if (f1 == f2) {
				can = false;
				break;
			}
			if (vis[f1]) {
				continue;
			}
			if (vis[f2]) {
				ans.push_back(i);
				continue;
			}
			if (sz[f1] < sz[f2]) {
				vis[f1] = true;
			} else {
				vis[f2] = true;
				ans.push_back(i);
			}
		}
		if (!can) {
			cout << -1 << endl;
		} else {
			cout << ans.size() << endl;
			for (int i = 0; i < ans.size(); i++) {
				cout << ans[i] << ' ';
			}
			cout << endl;
		}
	}
	return 0;
}
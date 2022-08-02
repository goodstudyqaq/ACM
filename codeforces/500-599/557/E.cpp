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

string work(string s, int idx) {
	int n = s.size();
	for (int i = idx; i < n; i += 2) {
		s[i] = 'c';
	}
	return s;
}
vector< string > V;
// 长度为 i j 时的最长公共后缀
vector< vector< vector< short > > > dp;
int n;

void work2(int a, int b) {
	int idx = a * 2 + (b - 2);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (V[a][i - 1] == V[b][j - 1]) {
				dp[idx][i][j] = dp[idx][i - 1][j - 1] + 1;
			} else {
				dp[idx][i][j] = 0;
			}
		}
	}
}

struct node {
	int nxt[2];
	int number;
	int cnt;
};
int root;
vector< node > nodes;

int new_node() {
	node tmp;
	tmp.nxt[0] = tmp.nxt[1] = -1;
	tmp.number = 0;
	tmp.cnt = 0;
	nodes.push_back(tmp);
	return nodes.size() - 1;
}

string s;

void dfs(int u) {
	nodes[u].cnt = nodes[u].number;
	for (int i = 0; i < 2; i++) {
		if (nodes[u].nxt[i] != -1) {
			int go = nodes[u].nxt[i];
			dfs(go);
			nodes[u].cnt += nodes[go].cnt;
		}
	}
}

void dfs2(int u, int num, string& res) {
	debug(u, num, res);
	if (nodes[u].number >= num || (nodes[u].nxt[0] == -1 && nodes[u].nxt[1] == -1)) {
		cout << res << endl;
		exit(0);
	}
	num -= nodes[u].number;
	for (int i = 0; i < 2; i++) {
		if (nodes[u].nxt[i] != -1) {
			int go = nodes[u].nxt[i];
			if (nodes[go].cnt >= num) {
				res = res + ( char )('a' + i);
				dfs2(go, num, res);
			} else {
				num -= nodes[go].cnt;
			}
		}
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> s;
	n = s.size();
	string s2 = s;
	reverse(s2.begin(), s2.end());
	V.push_back(work(s, 0));
	V.push_back(work(s, 1));
	V.push_back(work(s2, 0));
	V.push_back(work(s2, 1));
	dp.resize(4, vector< vector< short > >(n + 1, vector< short >(n + 1, 0)));
	root = new_node();
	for (int i = 0; i < 2; i++) {
		for (int j = 2; j < 4; j++) {
			work2(i, j);
		}
	}

	vector< vector< bool > > valid(n, vector< bool >(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			int a, b;
			if (i % 2 == 0) {
				a = 1;
			} else {
				a = 0;
			}
			if ((n - 1 - j) % 2 == 0) {
				b = 3;
			} else {
				b = 2;
			}
			int len = j - i + 1;
			int a_beg = i;
			int b_beg = n - 1 - j;
			int half_len = (len + 1) / 2;
			a_beg = a_beg + half_len - 1;
			b_beg = b_beg + half_len - 1;
			int idx = a * 2 + (b - 2);
			int val = dp[idx][a_beg + 1][b_beg + 1];

			if (val >= half_len) {
				valid[i][j] = true;
			}
		}
	}
	dp.clear();
	debug(root);
	for (int i = 0; i < n; i++) {
		int now = root;
		for (int j = i; j < n; j++) {
			int go = s[j] - 'a';
			if (nodes[now].nxt[go] == -1) {
				int tmp = new_node();
				nodes[now].nxt[go] = tmp;
			}
			now = nodes[now].nxt[go];
			// debug(now);
			if (valid[i][j]) {
				nodes[now].number++;
			}
		}
	}
	int k;
	cin >> k;
	dfs(root);
	string res = "";
	dfs2(root, k, res);
	return 0;
}
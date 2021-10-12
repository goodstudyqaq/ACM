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

const int maxn = 1e4 + 1;
struct Node {
	bool is_leaf;
	int val;
	int son[2];
};
Node nodes[maxn];
int ncnt;

int new_node() {
	nodes[ncnt].is_leaf = false;
	nodes[ncnt].son[0] = nodes[ncnt].son[1] = -1;
	return ncnt++;
}
int dp[maxn][101][2];
int flag;
int sz[maxn];
void dfs1(int u) {
	// debug(u);
	if (nodes[u].is_leaf) {
		return;
	}
	sz[u] = 1;
	dfs1(nodes[u].son[0]);
	dfs1(nodes[u].son[1]);
	sz[u] += sz[nodes[u].son[0]];
	sz[u] += sz[nodes[u].son[1]];
}

int cal(int v1, int v2, int h) {
	if (h == 1) {
		return v1 + flag * v2;
	} else {
		return v1 - flag * v2;
	}
}

int dfs(int u, int have, int need) {
	if (dp[u][have][need] != -1e9 - 1) return dp[u][have][need];
	int left_son = nodes[u].son[0];
	int right_son = nodes[u].son[1];
	// debug(u, have, need, left_son, right_son);
	if (sz[u] == 1) {
		// 下面都是叶子
		int left_val = nodes[left_son].val;
		int right_val = nodes[right_son].val;
		return cal(left_val, right_val, have);
	}
	if (sz[u] == 0) {
		return nodes[u].val;
	}

	if (need == 0) {
		// 求最大值
		int mx = -1e9;

		// 用一个 flag
		if (have > 0) {
			// 遍历左边有的 have
			int left_sz = sz[left_son];
			int right_sz = sz[right_son];

			for (int i = max(0, have - 1 - right_sz); i <= min(have - 1, left_sz); i++) {
				int tmp = dfs(left_son, i, 0);
				int tmp2;
				if (flag == -1) {
					tmp2 = dfs(right_son, have - 1 - i, 1);
				} else {
					tmp2 = dfs(right_son, have - 1 - i, 0);
				}
				int tmp3 = cal(tmp, tmp2, 1);
				mx = max(mx, tmp3);
			}
		}
		// 用另一个
		if (sz[u] - have > 0) {
			int left_sz = sz[left_son];
			int right_sz = sz[right_son];

			for (int i = max(0, have - right_sz); i <= min(have, left_sz); i++) {
				int tmp = dfs(left_son, i, 0);
				int tmp2;
				if (flag == 1) {
					tmp2 = dfs(right_son, have - i, 1);
				} else {
					tmp2 = dfs(right_son, have - i, 0);
				}
				int tmp3 = cal(tmp, tmp2, 0);
				mx = max(mx, tmp3);
			}
		}
		return dp[u][have][need] = mx;
	} else {
		// 求最小值
		int mi = 1e9;
		if (have > 0) {
			int left_sz = sz[left_son];
			int right_sz = sz[right_son];
			for (int i = max(0, have - 1 - right_sz); i <= min(have - 1, left_sz); i++) {
				int tmp = dfs(left_son, i, 1);
				int tmp2;
				if (flag == -1) {
					tmp2 = dfs(right_son, have - 1 - i, 0);
				} else {
					tmp2 = dfs(right_son, have - 1 - i, 1);
				}
				int tmp3 = cal(tmp, tmp2, 1);
				mi = min(mi, tmp3);
			}
		}

		if (sz[u] - have > 0) {
			int left_sz = sz[left_son];
			int right_sz = sz[right_son];

			for (int i = max(0, have - right_sz); i <= min(have, left_sz); i++) {
				int tmp = dfs(left_son, i, 1);
				int tmp2;
				if (flag == 1) {
					tmp2 = dfs(right_son, have - i, 0);
				} else {
					tmp2 = dfs(right_son, have - i, 1);
				}
				int tmp3 = cal(tmp, tmp2, 0);
				mi = min(mi, tmp3);
			}
		}
		return dp[u][have][need] = mi;
	}
}

int main() {
#ifdef LOCAL
	freopen("data.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	string E;
	cin >> E;
	int P, M;
	cin >> P >> M;
	stack< int > S;
	if (P == 0 && M == 0) {
		cout << E << endl;
		return 0;
	}

	for (int i = 0; i < E.size(); i++) {
		if (E[i] == '(') {
			int now = new_node();
			if (S.size() > 0) {
				int idx = S.top();
				Node& it = nodes[idx];
				if (it.son[0] == -1) {
					it.son[0] = now;
				} else {
					it.son[1] = now;
				}
			}
			S.push(now);
		} else if (E[i] == ')') {
			S.pop();
		} else if (E[i] != '?') {
			int now = new_node();
			nodes[now].is_leaf = true;
			nodes[now].val = E[i] - '0';
			int idx = S.top();
			Node& it = nodes[idx];
			if (it.son[0] == -1) {
				it.son[0] = now;
			} else {
				it.son[1] = now;
			}
		}
	}

	debug(ncnt);
	for (int i = 0; i < ncnt; i++) {
		debug(i, nodes[i].son[0], nodes[i].son[1]);
	}

	int mi = min(P, M);
	if (mi == P) {
		flag = 1;
	} else {
		flag = -1;
	}
	dfs1(0);

	for (int i = 0; i < maxn; i++) {
		for (int j = 0; j <= 100; j++) {
			dp[i][j][0] = dp[i][j][1] = -1e9 - 1;
		}
	}
	cout << dfs(0, mi, 0) << endl;
	return 0;
}
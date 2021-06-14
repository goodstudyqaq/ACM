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

const int maxn = 1005;
const int maxm = 1e5 + 2000;
struct node {
	vector< bool > v;
	int sum;
} nodes[maxm];
int ncnt;

struct root {
	int child[maxn];
} rt[maxm];
int rcnt;

int n, m, q;

int newroot(int oldroot) {
	rcnt++;
	for (int i = 1; i <= n; i++) {
		rt[rcnt].child[i] = rt[oldroot].child[i];
	}
	return rcnt;
}

int newnode(int oldnode) {
	ncnt++;
	nodes[ncnt].v = nodes[oldnode].v;
	nodes[ncnt].sum = nodes[oldnode].sum;
	return ncnt;
}

int idx_to_root[maxm];

int main() {
	// freopen("data.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &q);
	vector< bool > empty(m + 5, 0);
	idx_to_root[0] = newroot(0);
	for (int i = 1; i <= n; i++) {
		int tmp = newnode(0);
		nodes[tmp].v = empty;
		rt[idx_to_root[0]].child[i] = tmp;
		// debug(nodes[idx_to_root[0]].v);
	}

	for (int i = 1; i <= q; i++) {
		int opt;
		scanf("%d", &opt);
		if (opt == 1 || opt == 2) {
			int a, b;
			scanf("%d %d", &a, &b);
			idx_to_root[i] = newroot(idx_to_root[i - 1]);
			// debug(nodes[rt[idx_to_root[i]].child[a]].v);
			int tmpnode = newnode(rt[idx_to_root[i]].child[a]);
			// debug(nodes[tmpnode].v);

			int before_val = nodes[tmpnode].v[b];

			if (opt == 1) {
				nodes[tmpnode].v[b] = 1;
			} else {
				nodes[tmpnode].v[b] = 0;
			}
			rt[idx_to_root[i]].child[a] = tmpnode;
			if (nodes[tmpnode].v[b] == 1 && before_val == 0) {
				nodes[tmpnode].sum++;
			} else if (nodes[tmpnode].v[b] == 0 && before_val == 1) {
				nodes[tmpnode].sum--;
			}
		} else {
			int a;
			scanf("%d", &a);
			if (opt == 3) {
				idx_to_root[i] = newroot(idx_to_root[i - 1]);
				int tmpnode = newnode(rt[idx_to_root[i]].child[a]);
				int thesum = 0;
				for (int i = 1; i <= m; i++) {
					nodes[tmpnode].v[i] = nodes[tmpnode].v[i] ^ 1;
					if (nodes[tmpnode].v[i] == 1) {
						thesum++;
					}
				}
				rt[idx_to_root[i]].child[a] = tmpnode;
				nodes[tmpnode].sum = thesum;
			} else {
				idx_to_root[i] = idx_to_root[a];
			}
		}

		int theroot = idx_to_root[i];
		int res = 0;
		for (int i = 1; i <= n; i++) {
			res += nodes[rt[theroot].child[i]].sum;
		}
		printf("%d\n", res);
	}
	return 0;
}